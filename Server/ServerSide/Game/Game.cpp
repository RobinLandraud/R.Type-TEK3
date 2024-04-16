#include "Game.hpp"

#include <math.h>
#include <sys/types.h>

#include <cstddef>
#include <ostream>
#include <vector>

#include "DataComponent.hpp"
#include "ExecComponent.hpp"
#include "Protocol/ProtocolParser.hpp"
#include "Registry.hpp"
#include "TransformComponent.hpp"
#include "User.hpp"
#include "system.hpp"
#include "utils.hpp"

/**
 * \fn Game::Game(ASocket& paramsSocket): socket(paramsSocket)
 * \brief Constructor of the Game class
 * \param paramsSocket The socket to use
 */
Game::Game(ASocket& paramsSocket)
    : socket(paramsSocket)
{
    auto const& mainScene = _registry.spawn_entity();
    mainEntityIndex = mainScene.id;
    auto& sceneManager = _registry.add_component(mainScene, SceneManager());
    _registry.add_component(mainScene, DataComponent());
    sceneManager->setUpdate(true);
    _registry.add_system(gameSystem);
};

/**
 * \fn Game::addPlayer(const User& user)
 * \brief Add a player to the game
 * \param user The user to add
 */
void Game::addPlayer(
    const User& user, Position3D_t pos, const std::vector<User>& allUser)
{
    auto& ent = _registry.spawn_entity();
    _registry.add_component(ent, ServerUser(user));
    _registry.add_component(ent, TransformComponent(pos));
    _registry.add_component(ent, DataComponent());
    sendStringPacket(_registry,
        socket,
        ENTITY_SPAWN,
        static_cast<int>(ent.id),
        ENTITY_PLAYER,
        static_cast<int>(pos.x),
        static_cast<int>(pos.y),
        user.name,
        user);
    for (const auto& tempUser : allUser) {
        if (tempUser != user) {
            sendStringPacket(_registry,
                socket,
                ENTITY_SPAWN,
                static_cast<int>(ent.id),
                ENTITY_FAKE_PLAYER,
                static_cast<int>(pos.x),
                static_cast<int>(pos.y),
                user.name,
                tempUser);
        }
    }
}

/**
 * \fn Game::loop()
 * \brief The main loop of the game
 */
void Game::loop()
{
    if (running) {
        _registry.run_systems(socket);
    }
}

/**
 * \fn size_t Game::registerNameUser(User user)
 * \brief Register a user in the game
 * \param user The user to register
 * \return The id of the user
 */
size_t Game::registerNameUser(User user)
{
    auto& player_array = _registry.get_components<ServerUser>();
    for (int i = 0; i < player_array.size(); i++) {
        auto& player = player_array[i];
        if (player && player.value().getUser().port == user.port
            && player.value().getUser().name == user.name) {
            auto& ent_player = _registry.getEntities()[i];
            auto& ent = _registry.spawn_entity();
            auto& data = _registry.add_component(ent, DataComponent());
            data->addValue("pseudo", user.name);
            auto& data_player =
                _registry.add_component(ent_player.value(), DataComponent());
            data_player->addValue("textId", ent.id);
            return ent.id;
        }
    }
    return -1;
}

/**
 * \fn void Game::start(const std::vector<User>& users)
 * \brief Start the game
 * \param users The users to start the game with
 */
void Game::start(const std::vector<User>& users)
{
    int count = 0;
    auto& data_arry = _registry.get_components<DataComponent>();
    auto& data = data_arry[mainEntityIndex];
    data->addValue("listUser", users);
    for (const auto& user : users) {
        auto yPos = static_cast<float>(300 + 100 * count);
        addPlayer(user, {200, yPos, 3}, users);
        count++;
    }
    _registry.add_system(progressSystem);
    _registry.add_system(execSystem);
    running = true;
}

/**
 * \fn int Game::getNBPlayer()
 * \brief Get the number of player in the game
 * \return The number of player
 */
int Game::getNBPlayer()
{
    auto& player_array = _registry.get_components<ServerUser>();
    return player_array.size();
}

/**
 * \fn void Game::moveEntity(int entityId, int x, int y)
 * \brief Move an entity
 * \param entityId The id of the entity to move
 * \param x The x position
 * \param y The y position
 */
void Game::moveEntity(int entityId, int x, int y)
{
    auto& transform_array = _registry.get_components<TransformComponent>();
    auto& player_array = _registry.get_components<ServerUser>();
    auto& transform = transform_array[entityId];
    auto& player = player_array[entityId];
    if (player && transform) {
        transform->setPosition(x, y, transform->getPosition().z);
    }
    sendToEveryPlayer(_registry, socket, ENTITY_MOVE, entityId, x, y, 0, mainEntityIndex);
}

/**
 * \fn void Game::playerFire(const User& sender, FireType type)
 * \brief A player fire
 * \param sender The user who fire
 * \param type The type of the fire
 */
void Game::playerFire(const User& sender, FireType type)
{
    auto& player_array = _registry.get_components<ServerUser>();
    int ownerId = -1;
    for (int i = 0; i < player_array.size(); i++) {
        if (player_array[i]) {
            if (player_array[i]->getUser().ip == sender.ip
                && player_array[i]->getUser().port == sender.port)
                ownerId = i;
        }
    }
    if (ownerId == -1) {
        std::cout << "Sender is not an active player, can't fire" << std::endl;
        return;
    }
    auto& transform_array = _registry.get_components<TransformComponent>();
    auto& transform = transform_array[ownerId];
    if (!transform) {
        std::cout << "Sender is register, but don't have init pos, can't fire"
                  << std::endl;
        return;
    }
    switch (type) {
        case BASIC_FIRE: createBullet(transform->getPosition(), ownerId); break;
        default: std::cout << "This fire don't exist" << std::endl; break;
    }
}

/**
 * \fn void destroyOutsideEntity(size_t index, registry& reg, ASocket& socket)
 * \brief Destroy an entity if it's outside the map
 * \param index The index of the entity
 * \param reg The registry
 * \param socket The socket
 */
void destroyOutsideEntity(size_t index, registry& reg, ASocket& socket)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& collision_array = reg.get_components<CollideComponent>();
    if (transform_array.size() <= 0)
        return;
    auto& transform = transform_array[index];
    if (collision_array.size() > 0) {
        auto& collision = collision_array[index];
        if (transform && collision) {
            if (transform.value().getPosition().x
                        + collision.value().getCollideBox().width
                    < 0
                || transform.value().getPosition().x > 1920
                || transform.value().getPosition().y
                           + collision.value().getCollideBox().height
                       < 0
                || transform.value().getPosition().y > 1080) {
                auto ent = reg.entity_from_index(index);
                if (ent) {
                    int entityId = ent.value().id;
                    reg.kill_entity(ent.value());
                    Game::sendToEveryPlayer(
                        reg, socket, ENTITY_DEATH, entityId, 0, 0, 0, 0);
                }
            }
            return;
        }
    }
    if (transform.value().getPosition().x < 0
        || transform.value().getPosition().x > 1920
        || transform.value().getPosition().y < 0
        || transform.value().getPosition().y > 1080) {
        auto ent = reg.entity_from_index(index);
        if (ent) {
            int entityId = ent.value().id;
            reg.kill_entity(ent.value());
            Game::sendToEveryPlayer(
                reg, socket, ENTITY_DEATH, entityId, 0, 0, 0, 0);
        }
    }
}

/**
 * \fn void Game::createBullet(Position3D_t pos, int owner)
 * \brief Create a bullet
 * \param pos The position of the bullet
 * \param owner The owner of the bullet
 */
void Game::createBullet(Position3D_t pos, int owner)
{
    const auto& entity = _registry.spawn_entity();
    _registry.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    _registry.add_component(entity, VelocityComponent(12));
    _registry.add_component(entity, ClocksComponent(0.017));
    _registry.add_component(entity, OwnerComponent(owner));
    sparse_array<ExecComponent>::reference_type exec =
        _registry.add_component(entity, ExecComponent());
    if (exec) {
        exec.value().addFunction(moveRight);
        exec.value().addFunction(destroyOutsideEntity);
    }
    sendToEveryPlayer(
        _registry, socket, ENTITY_SPAWN, entity.id, BASIC_BULLET, pos.x, pos.y, mainEntityIndex);
}

/**
 * \fn void Game::playerLeave(const User& sender)
 * \brief Make a player leave the game
 * \param sender The user who leave
 */
void Game::playerLeave(const User& sender)
{
    auto& player_array = _registry.get_components<ServerUser>();
    int ownerId = -1;
    for (int i = 0; i < player_array.size(); i++) {
        if (player_array[i]) {
            if (player_array[i]->getUser().ip == sender.ip
                || player_array[i]->getUser().port == sender.port)
                ownerId = i;
        }
    }
    if (ownerId == -1) {
        std::cout << "Sender is not an active player, can't fire" << std::endl;
        return;
    }
    std::optional<Entity>& ent = _registry.getEntities()[ownerId];
    if (ent) {
        int entId = ent.value().id;
        _registry.kill_entity(ent.value());
        sendToEveryPlayer(_registry, socket, ENTITY_DEATH, entId, 0, 0, 0, mainEntityIndex);
    }
}

/**
 * \fn void Game::sendToEveryPlayer(registry& reg, ASocket& socket, Protocol
 * type, int args1, int args2, int args3, int args4) \brief Send a message to
 * every player \param reg The registry \param socket The socket \param type The
 * type of the message \param args1 The first argument \param args2 The second
 * argument \param args3 The third argument \param args4 The fourth argument
 */
void Game::sendToEveryPlayer(registry& reg,
    ASocket& socket,
    Protocol type,
    int args1,
    int args2,
    int args3,
    int args4,
    size_t mainIndex)
{
    auto& data_arry = reg.get_components<DataComponent>();
    if (data_arry.size() < mainIndex)
        return;
    auto& data = data_arry[mainIndex];
    if (!data)
        return;
    auto userList = data->getValue<std::vector<User>>("listUser");
    auto& player_array = reg.get_components<ServerUser>();
    for (auto& player : userList) {
        u_int64_t header =
            ProtocolBuilder::createPacket(type, args1, args2, args3, args4);
        char rData[sizeof(header)];
        memcpy(rData, &header, sizeof(header));
        if (socket.send(rData, sizeof(header), player.ip, player.port)
            != ASocket::SUCCES)
            std::cout << "error will sending to " << player.name << std::endl;
    }
}

/**
 * \fn void Game::sendStringPacket(registry& reg, ASocket& socket, Protocol type,
    int args1, int args2, int args3, int args4, const std::string& buff, const User& receiver)
 * \brief Send a string packet to a player
 * \param reg The registry
 * \param socket The socket
 * \param type The type of the message
 * \param args1 The first argument
 * \param args2 The second argument
 * \param args3 The third argument
 * \param args4 The fourth argument
 * \param buff The string to send
 * \param receiver The receiver of the message
 */

void Game::sendStringPacket(registry& reg,
    ASocket& socket,
    Protocol type,
    int args1,
    int args2,
    int args3,
    int args4,
    const std::string& buff,
    const User& receiver)
{
    u_int64_t header =
        ProtocolBuilder::createPacket(type, args1, args2, args3, args4);
    char rData[sizeof(header) + MAX_STR_LENGTH];
    memcpy(rData, &header, sizeof(header));
    memcpy(rData + sizeof(header), buff.c_str(), buff.length() + 1);
    if (socket.send(rData, sizeof(header), receiver.ip, receiver.port)
        != ASocket::SUCCES)
        std::cout << "error will sending to " << receiver.name << std::endl;
}

/**
 * \fn void Game::sendToEveryPlayerWithString(registry& reg, ASocket& socket, Protocol type,
    int args1, int args2, int args3, int args4, const std::string& buff)
 * \brief Send a string packet to every player
 * \param reg The registry
 * \param socket The socket
 * \param type The type of the message
 * \param args1 The first argument
 * \param args2 The second argument
 * \param args3 The third argument
 * \param args4 The fourth argument
 * \param buff The string to send
 */
void Game::sendToEveryPlayerWithString(registry& reg,
    ASocket& socket,
    Protocol type,
    int args1,
    int args2,
    int args3,
    int args4,
    const std::string& buff)
{
    auto& player_array = reg.get_components<ServerUser>();
    for (auto& player : player_array) {
        if (player) {
            sendStringPacket(reg,
                socket,
                type,
                args1,
                args2,
                args3,
                args4,
                buff,
                player.value().getUser());
        }
    }
}