#include <cstddef>
#include <memory>
#include <vector>

#include "ASocket.hpp"
#include "ClocksComponent.hpp"
#include "CollideComponent.hpp"
#include "ExecComponent.hpp"
#include "LifeComponent.hpp"
#include "OwnerComponent.hpp"
#include "Protocol/ProtocolBuilder.hpp"
#include "Protocol/ProtocolParser.hpp"
#include "Registry.hpp"
#include "SceneManager.hpp"
#include "ServerUser.hpp"
#include "TransformComponent.hpp"
#include "User.hpp"
#include "VelocityComponent.hpp"
#include "system.hpp"

#define MAX_STR_LENGTH 1024

#pragma once

/**
 * \class Game
 * \brief Game class
 */
class Game
{
  public:
    /**
     * \enum FireType
     * \brief Type of fire
     */
    enum FireType { BASIC_FIRE, UNKNOWN_FIRE };

    /**
     * \fn explicit Game(ASocket& paramsSocket);
     * \brief Constructor
     * \param paramsSocket Socket to communicate with the client
     */
    explicit Game(ASocket& paramsSocket);
    ~Game() = default; /*!< Default Destructor */

    Game(Game const&) = default;     /*!< Default copy constructor */
    Game(Game&&) noexcept = default; /*!< Default move constructor */
    Game& operator=(
        Game const&) = default; /*!< Default copy assignment operator */
    Game& operator=(
        Game&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn [[nodiscard]] bool isRunnning() const
     * \brief Check if the game is running
     * \return true if the game is running, false otherwise
     */
    [[nodiscard]] bool isRunnning() const
    {
        return running;
    };

    /**
     * \fn void addPlayer(const User& user)
     * \brief Add a player to the game
     * \param user User to add
     * \param pos Init pos of player
     * \param allUser List of all user
     */
    void addPlayer(const User& user, Position3D_t pos, const std::vector<User>& allUser);

    /**
     * \fn void loop()
     * \brief Game loop
     */
    void loop();

    /**
     * \fn int getNBPlayer()
     * \brief Get the number of player in the game
     */
    int getNBPlayer();

    /**
     * \fn void moveEntity(int entityId, int x, int y)
     * \brief Move an entity
     * \param entityId Id of the entity to move
     * \param x X position
     * \param y Y position
     */
    void moveEntity(int entityId, int x, int y);

    /**
     * \fn void playerFire(const User& sender, FireType type)
     * \brief Make the player fire
     * \param sender User who fire
     * \param type Type of fire
     */
    void playerFire(const User& sender, FireType type);

    /**
     * \fn void createBullet(Position3D_t pos, int owner)
     * \brief Create a bullet
     * \param pos Position of the bullet
     * \param owner Owner of the bullet
     */
    void createBullet(Position3D_t pos, int owner);

    /**
     * \fn void playerLeave(const User& sender)
     * \brief Make the player leave the game
     * \param sender User who leave
     */
    void playerLeave(const User& sender);

    /**
     * \fn static void sendToEveryPlayer(registry& reg, ASocket& socket,
     * Protocol type, int args1, int args2, int args3, int args4) \brief Send a
     * message to every player \param reg Registry \param socket Socket to
     * communicate with the client \param type Type of message \param args1
     * First argument \param args2 Second argument \param args3 Third argument
     * \param args4 Fourth argument
     */
    static void sendToEveryPlayer(registry& reg,
        ASocket& socket,
        Protocol type,
        int args1,
        int args2,
        int args3,
        int args4,
        size_t mainIndex);

    /**
     * \fn size_t registerNameUser(User user)
     * \brief Register the name of a user
     * \param user User to register
     * \return Id of the user
     */
    size_t registerNameUser(User user);

    /**
     * \fn void start(const std::vector<User>& users);
     * \brief Start the game
     * @param users List of user
     */
    void start(const std::vector<User>& users);

    /**
     * \fn static void sendStringPacket(registry& reg, ASocket& socket, Protocol type,
        int args1, int args2, int args3, int args4, const std::string& buff, const User& receiver)
     * \brief Send a string packet
     * \param reg Registry
     * \param socket Socket to communicate with the client
     * \param type Type of message
     * \param args1 First argument
     * \param args2 Second argument
     * \param args3 Third argument
     * \param args4 Fourth argument
     * \param buff String to send
     * \param receiver User who receive the message
     */
    static void sendStringPacket(registry& reg,
        ASocket& socket,
        Protocol type,
        int args1,
        int args2,
        int args3,
        int args4,
        const std::string& buff,
        const User& receiver);

    /**
     * \fn static void sendToEveryPlayerWithString(registry& reg, ASocket& socket, Protocol type,
        int args1, int args2, int args3, int args4, const std::string& buff)
     * \brief Send a string packet to every player
     * \param reg Registry
     * \param socket Socket to communicate with the client
     * \param type Type of message
     * \param args1 First argument
     * \param args2 Second argument
     * \param args3 Third argument
     * \param args4 Fourth argument
     * \param buff String to send
     */
    static void sendToEveryPlayerWithString(registry& reg,
        ASocket& socket,
        Protocol type,
        int args1,
        int args2,
        int args3,
        int args4,
        const std::string& buff);

  private:
    ASocket& socket;            /*!< Socket to communicate with the client */
    registry _registry;         /*!< Registry */
    size_t mainEntityIndex = 0; /*!< Index of the main entity */
    std::vector<Entity> entityList = {}; /*!< List of entity */
    bool running = false;                /*!< Is the game running */
};