#include <sys/types.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <ostream>
#include <string>
#include <vector>

#include "ASocket.hpp"
#include "DataComponent.hpp"
#include "DrawableComponent.hpp"
#include "ProtocolParser.hpp"
#include "Registry.hpp"
#include "SceneManager.hpp"
#include "ServerPropertiesComponent.hpp"
#include "TransformComponent.hpp"
#include "button.hpp"
#include "gameEntity.hpp"
#include "move.hpp"
#include "system.hpp"
#include "utils.hpp"

/**
 * \fn bool sendWithoutString(ASocket& socket, uint64_t header, const
 * std::string& adress, int remotePort) \brief Send a packet without string
 * \param socket The socket
 * \param header The header of the packet
 * \param adress The adress of the remote
 * \param remotePort The port of the remote
 * \return true if the packet has been sent, false otherwise
 */
bool sendWithoutString(
    ASocket& socket, uint64_t header, const std::string& adress, int remotePort)
{
    char data[sizeof(header)];
    memcpy(data, &header, sizeof(header));
    if (socket.send(data, sizeof(data), adress, remotePort)
        != ASocket::SUCCES) {
        std::cout << "Send error" << std::endl;
        return false;
    }
    return true;
}

/**
 * \fn bool sendWithInt(ASocket& socket, uint64_t header, const std::string&
 * buffer, const std::string& adress, int remotePort) \brief Send a packet with
 * an int \param socket The socket \param header The header of the packet \param
 * buffer The buffer to send \param adress The adress of the remote \param
 * remotePort The port of the remote \return true if the packet has been sent,
 * false otherwise
 */
bool sendWithString(ASocket& socket,
    uint64_t header,
    const std::string& buffer,
    const std::string& adress,
    int remotePort)
{
    char data[sizeof(header) + MAX_STR_LENGTH];
    memcpy(data, &header, sizeof(header));
    memcpy(data + sizeof(header), buffer.c_str(), buffer.length() + 1);
    if (socket.send(data, sizeof(data), adress, remotePort)
        != ASocket::SUCCES) {
        std::cout << "Send error" << std::endl;
        return false;
    }
    return true;
}

/**
 * \fn void killEntity(registry& reg, int entityId)
 * \brief Kill an entity
 * \param reg The registry
 * \param entityId The id of the entity
 */
void killEntity(registry& reg, int entityId)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            size_t mainEntityIndex = sceneManager->getEntityPos();
            for (auto& entity : reg.getEntities()) {
                if (entity && entity->id != mainEntityIndex
                    && entity->id == entityId) {
                    reg.kill_entity(entity.value());
                    break;
                }
            }
        }
    }
}

/**
 * \fn void updateLifeEntity(registry& reg, int entityId, int newLife)
 * \brief Update the life of an entity
 * \param reg The registry
 * \param entityId The id of the entity
 * \param newLife The new life of the entity
 */
void updateLifeEntity(registry& reg, int entityId, int newLife)
{
    auto& dataList = reg.get_components<DataComponent>();
    auto& data = dataList[entityId];
    if (data) {
        data->setValue("life", newLife);
    }
}

/**
 * \fn void entityMount(registry& reg, int entityId, int mountedID)
 * \brief Mount an entity
 * \param reg The registry
 * \param entityId The id of the entity
 * \param mountedID The id of the entity mounted
 */
void entityMount(registry& reg, int entityId, int mountedID)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            size_t mainEntityIndex = sceneManager->getEntityPos();
            for (auto& entity : reg.getEntities()) {
                if (entity && entity->id != mainEntityIndex
                    && entity->id == entityId) {
                    reg.add_component(
                        entity.value(), MountedComponent(mountedID));
                    break;
                }
            }
        }
    }
}

/**
 * \fn void entityMove(registry& reg, int entityId, Position3D_t pos)
 * \brief Move an entity
 * \param reg The registry
 * \param entityId The id of the entity
 * \param pos The new position of the entity
 */
void entityMove(registry& reg, int entityId, Position3D_t pos)
{
    auto &transform_array = reg.get_components<TransformComponent>();
    auto &serverProperties_array = reg.get_components<ServerPropertiesComponent>();
    for (int i =0; i < serverProperties_array.size(); i++) {
        auto &serverProperties = serverProperties_array[i];
        if (serverProperties && serverProperties->getId() == entityId) {
            auto &transform = transform_array[i];
            if (transform)
                transform.value().setPosition(pos.x, pos.y, pos.z);
        }
    }
}

/**
 * \fn void entityFire(registry& reg, AEngine& engine, ServerToken& token, int
 * entityId) \brief Fire an entity \param reg The registry \param engine The
 * engine \param token The token \param entityId The id of the entity
 */
void entityFire(
    registry& reg, AEngine& engine, ServerToken& token, int entityId)
{
    PlayerFire(entityId, reg, engine, token);
}

/**
 * \fn void listHub(registry& reg, int hubPort, size_t mainEntityIndex,
 * ServerToken serverToken) \brief List the hub \param reg The registry \param
 * hubPort The port of the hub \param mainEntityIndex The index of the main
 * entity \param serverToken The server token
 */
void listHub(
    registry& reg, int hubPort, size_t mainEntityIndex, ServerToken serverToken)
{
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[mainEntityIndex];
    if (data) {
        auto portList = data->getValue<std::vector<int>>("lobbyPort");
        for (int tempPort : portList) {
            if (tempPort == hubPort)
                return;
        }
        portList.push_back(hubPort);
        data->addValue("lobbyPort", portList);
        uint64_t header = ProtocolBuilder::createPacket(HUB_STATUS, 0, 0, 0, 0);
        char data[sizeof(header)];
        memcpy(data, &header, sizeof(header));
        if (serverToken.socket.send(
                data, sizeof(data), serverToken.adress, hubPort)
            != ASocket::SUCCES) {
            std::cout << "Send error" << std::endl;
        }
    }
}

/**
 * \fn void addLobbyToList(registry& reg, int nbPlayer, bool available,  const
 * std::string& name, int senderPort, AEngine& engine) \brief Add a lobby to the
 * list \param reg The registry \param nbPlayer The number of player \param
 * available If the lobby is available \param name The name of the lobby \param
 * senderPort The port of the sender \param engine The engine
 */
void addLobbyToList(registry& reg,
    int nbPlayer,
    bool available,
    const std::string& name,
    int senderPort,
    AEngine& engine)
{
    auto& data_array = reg.get_components<DataComponent>();
    for (int index = 0; index < data_array.size(); index++) {
        auto& data = data_array[index];
        if (data && data.value().hasValue<std::vector<size_t>>("idLobbyList")) {
            auto& newLobby = reg.spawn_entity();
            auto idLobbyIdList =
                data->getValue<std::vector<size_t>>("idLobbyList");
            idLobbyIdList.push_back(newLobby.id);
            size_t lobbyListSize = idLobbyIdList.size();
            data->addValue("idLobbyList", idLobbyIdList);

            engine.getGraphics().createText(name + std::to_string(newLobby.id),
                name + " (" + std::to_string(nbPlayer) + "/4)",
                "beautiful",
                18);
            reg.add_component(newLobby,
                DrawableComponent(name + std::to_string(newLobby.id), TEXT));
            reg.add_component(newLobby,
                TransformComponent(
                    {200, static_cast<float>(600 + 20 * lobbyListSize), 2}));
            reg.add_component(newLobby, CollideComponent(100, 100));
            auto& newLobbyData = reg.add_component(newLobby, DataComponent());
            newLobbyData->addValue("port", senderPort);
            auto& button = reg.add_component(newLobby, MouseEventComponent());
            button->setOnClick(buttonClick);
            if (available)
                button->setOnRelease(joinLobby);
            else
                button->setOnRelease(buttonDeny);
        }
    }
}

/**
 * \fn void confirmLobbyCreate(registry& reg, int senderPort, size_t
 * mainEntityIndex) \brief Confirm the creation of a lobby \param reg The
 * registry \param senderPort The port of the sender \param mainEntityIndex The
 * index of the main entity
 */
void confirmLobbyCreate(registry& reg, int senderPort, size_t mainEntityIndex)
{
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[mainEntityIndex];
    if (data) {
        data.value().addValue("connectPort", senderPort);
    }
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        sceneManager->changeScene(WAIT_IN_LOBBY);
    }
}

/**
 * \fn void confirmConnectLobby(registry& reg, int senderPort, size_t
 * mainEntityIndex) \brief Confirm the connection to a lobby \param reg The
 * registry \param senderPort The port of the sender \param mainEntityIndex The
 * index of the main entity
 */
void confirmConnectLobby(registry& reg, int senderPort, size_t mainEntityIndex)
{
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[mainEntityIndex];
    if (data) {
        data.value().addValue("connectPort", senderPort);
    }
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            sceneManager->changeScene(WAIT_IN_LOBBY);
            return;
        }
    }
}

/**
 * \fn void startGame(registry& reg)
 * \brief Start the game
 * \param reg The registry
 */
void startGame(registry& reg)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            sceneManager->changeScene(MULTIPLAYER);
            return;
        }
    }
}

/**
 * \fn void handleRequest(registry& reg, const ParsedPacket& header, const
 std::string& buff, size_t mainEntityIndex, const ServerToken& serverToken, int
 senderPort, AEngine& engine)
 * \brief Handle the request
 * \param reg The registry
 * \param header The header of the packet
 * \param buff The buffer
 * \param mainEntityIndex The index of the main entity
 * \param serverToken The server token
 * \param senderPort The port of the sender
 * \param engine The engine
 */
void handleRequest(registry& reg,
    const ParsedPacket& header,
    const std::string& buff,
    size_t mainEntityIndex,
    const ServerToken& serverToken,
    int senderPort,
    AEngine& engine)
{
    unsigned short protocolId =
        ProtocolParser::getProtocol(header.element, header.MethodID);
    switch (protocolId) {
        case GAME_START: startGame(reg); break;
        case HUB_SUCCESFULLY_CREATE:
            confirmLobbyCreate(reg, senderPort, mainEntityIndex);
            break;
        case HUB_CONNECT_SUCCES:
            confirmConnectLobby(reg, senderPort, mainEntityIndex);
            break;
        case HUB_STATUS:
            addLobbyToList(reg,
                header.arguments[0],
                header.arguments[1] != 0,
                buff,
                senderPort,
                engine);
            break;
        case HUB_LIST: {
            int hubPort = header.arguments[0] * 1000 + header.arguments[1];
            listHub(reg, hubPort, mainEntityIndex, serverToken);
            break;
        }
        case ENTITY_SPAWN:
            createEntity(reg,
                static_cast<EntityType>(header.arguments[1]),
                Position3D_t{static_cast<float>(header.arguments[2]),
                    static_cast<float>(header.arguments[3]),
                    0},
                header.arguments[0],
                buff, "");
            break;
        case ENTITY_DEATH: killEntity(reg, header.arguments[0]); break;
        case ENTITY_LIFE_UPDATE:
            updateLifeEntity(reg, header.arguments[0], header.arguments[1]);
            break;
        case ENTITY_MOUNT_ENTITY:
            entityMount(reg, header.arguments[0], header.arguments[1]);
            break;
        case ENTITY_MOVE:
            entityMove(reg,
                header.arguments[0],
                Position3D_t{static_cast<float>(header.arguments[1]),
                    static_cast<float>(header.arguments[2]),
                    3});
        default:
            std::cout << "Unknown protocol ID, (not normal)" << std::endl;
            break;
    }
}

/**
 * void listen(registry& reg, AEngine& engine, ServerToken& serverToken,
 * std::vector<Request>& requestList) \brief Listen to the server \param reg The
 * registry \param engine The engine \param serverToken The server token \param
 * requestList The list of request
 */
void listen(registry& reg,
    AEngine& engine,
    ServerToken& serverToken,
    std::vector<Request>& requestList)
{
    serverToken.socket.setBlocking(false);
    auto scene_array = reg.get_components<SceneManager>();
    for (auto sceneManager : scene_array) {
        if (!sceneManager)
            continue;
        while (sceneManager->getCurrentScene() != END && engine.isRunning()) {
            std::string rIP;
            unsigned short port = 0;
            std::size_t received = 0;
            unsigned char data[sizeof(u_int64_t) + MAX_STR_LENGTH];
            if (serverToken.socket.receive(
                    &data, sizeof(data), received, rIP, port)
                == ASocket::SUCCES) {
                std::cout << "receive something, rip = " << rIP
                          << " serverAdress = " << serverToken.adress
                          << std::endl;
                if (rIP != serverToken.adress && rIP != "127.0.0.1") {
                    std::cout << "I don't know the sender, go back... Monkey!"
                              << std::endl;
                    continue;
                }
                ParsedPacket header = getHeader(data);
                unsigned short protocolId = ProtocolParser::getProtocol(
                    header.element, header.MethodID);
                std::string strArgs;
                if (received > 8)
                    strArgs = convertToString(
                        reinterpret_cast<char*>(data + sizeof(u_int64_t)));
                requestList.push_back(Request{header, strArgs, port, rIP});
            }
        }
    }
}

/**
 * \fn void ServerSystem(registry& reg, AEngine& engine, ServerToken&
 * serverToken) \brief The server system \param reg The registry \param engine
 * The engine \param serverToken The server token
 */
void ServerSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& serverPropertiesList =
        reg.get_components<ServerPropertiesComponent>();
    int portUsed = serverToken.port;
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            if (sceneManager->getCurrentScene() == MULTIPLAYER) {
                auto& data_array = reg.get_components<DataComponent>();
                auto& dataP = data_array[sceneManager->getEntityPos()];
                if (dataP) {
                    portUsed = dataP.value().getValue<int>("connectPort");
                }
            }
        }
    }
    for (auto &property : serverPropertiesList) {
        if (property && property->isUpdate()) {
            for (const auto& methode : property->getMethodList()) {
                if (methode.buffer.empty())
                    sendWithoutString(serverToken.socket,
                        methode.header,
                        serverToken.adress,
                        portUsed);
                else {
                    sendWithString(serverToken.socket,
                        methode.header,
                        methode.buffer,
                        serverToken.adress,
                        portUsed);
                }
            }
            property->clearMethod();
        }
    }
}