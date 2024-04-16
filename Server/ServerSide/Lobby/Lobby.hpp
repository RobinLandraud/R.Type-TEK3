#include <sys/types.h>

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Game.hpp"
#include "ProtocolBuilder.hpp"
#include "ProtocolParser.hpp"
#include "SFMLIpAddress.hpp"
#include "SFMLSocket.hpp"
#include "User.hpp"
#include "utils.hpp"

#pragma once

#define MAX_PLAYER 4 /*!< Max number of player in a game */

/**
 * \class Lobby
 * \brief Lobby class
 */
class Lobby
{
  public:
    /**
     * \fn Lobby(int port, User owner, std::string name, int hubID)
     * \brief Constructor
     * \param port Port of the lobby
     * \param owner Owner of the lobby
     * \param name Name of the lobby
     * \param hubID ID of the hub
     */
    Lobby(int port, User owner, std::string name, int hubID);
    ~Lobby() = default; /*!< Default Destructor */
    void handlePacket(); /*!< Handle the packets */

  private:
    bool hasToStop = false; /*!< Boolean to know if the lobby has to stop */
    std::unique_ptr<ASocket> socket = std::make_unique<SFMLSocket>(); /*!< Socket of the lobby */
    std::string name; /*!< Name of the lobby */
    User owner; /*!< Owner of the lobby */
    std::vector<std::pair<User, bool>> users; /*!< Users in the lobby */
    Game game; /*!< Game of the lobby */

    /**
     * \fn void handleConnect(unsigned short port, sf::IpAddress rIP, unsigned char data[sizeof(u_int64_t) + MAX_STR_LENGTH])
     * \brief Handle the connection of a user
     * \param port Port of the user
     * \param rIP IP of the user
     * \param data Data of the packet
     */
    void handleConnect(unsigned short port,
        std::string rIP,
        unsigned char data[sizeof(u_int64_t) + MAX_STR_LENGTH]);

    /**
     * \fn void handleStatus(const User& sender, ParsedPacket&, const std::string& str)
     * \brief Handle the status of a user
     * \param sender User who sent the packet
     * \param packet Packet received
     * \param str String of the packet
     */
    void handleStatus(
        const User& sender, ParsedPacket&, const std::string& str);

    /**
     * \fn void handleEntityMove(const User& sender, ParsedPacket&, const std::string& str)
     * \brief Handle the movement of an entity
     * \param sender User who sent the packet
     * \param packet Packet received
     * \param str String of the packet
     */
    void handleEntityMove(
        const User& sender, ParsedPacket&, const std::string& str);

    /**
     * \fn void handlePlayerFire(const User& sender, ParsedPacket&, const std::string& str)
     * \brief Handle the fire of a player
     * \param sender User who sent the packet
     * \param packet Packet received
     * \param str String of the packet
     */
    void handlePlayerFire(
        const User& sender, ParsedPacket&, const std::string& str);

    /**
     * \fn void handlePlayerLeave(const User& sender, ParsedPacket&, const std::string& str)
     * \brief Handle the leave of a player
     * \param sender User who sent the packet
     * \param packet Packet received
     * \param str String of the packet
     */
    void handlePlayerLeave(
        const User& sender, ParsedPacket&, const std::string& str);

    /**
     * \fn void handlePlayerReady(const User& sender, ParsedPacket&, const std::string& str)
     * \brief Handle the ready of a player
     * \param sender User who sent the packet
     * \param packet Packet received
     * \param str String of the packet
     */
    void handlePlayerReady(
        const User& sender, ParsedPacket&, const std::string& str);
    
    /**
     * \fn void handlePlayerPause(const User& sender, ParsedPacket&, const std::string& str)
     * \brief Handle the pause of a player
     * \param sender User who sent the packet
     * \param packet Packet received
     * \param str String of the packet
     */
    void handlePlayerPause(
        const User& sender, ParsedPacket&, const std::string& str);

    /**
     * \fn void handlePlayerSendMessage(const User& sender, ParsedPacket&, const std::string& str)
     * \brief Handle the send message of a player
     * \param sender User who sent the packet
     * \param packet Packet received
     * \param str String of the packet
     */
    void handlePlayerSendMessage(
        const User& sender, ParsedPacket&, const std::string& str);
    
    /**
     * \fn void handlePlayerSwitchSkin(const User& sender, ParsedPacket&, const std::string& str)
     * \brief Handle the switch skin of a player
     * \param sender User who sent the packet
     * \param packet Packet received
     * \param str String of the packet
     */
    void handlePlayerSwitchSkin(
        const User& sender, ParsedPacket&, const std::string& str);

    /**
     * \fn void sendSuccesCreateToOwner()
     * \brief Send the succes create packet to the owner
     */
    void sendSuccesCreateToOwner();

    /**
     * \fn void sendAllPlayerName(User receiver)
     * \brief Send all the player name to a user
     * \param receiver User who will receive the packet
     */
    void sendAllPlayerName(User receiver);

    /**
     * \fn void startGame();
     * \brief Start the game
     */
    void startGame();

    std::map<Protocol,
        std::function<void(Lobby&,
            const User& sender,
            ParsedPacket& packet,
            const std::string& str)>>
        functionList = {{HUB_STATUS,
                            [this](Lobby& lobby,
                                const User& sender,
                                ParsedPacket& packet,
                                const std::string& str) {
                                lobby.handleStatus(sender, packet, str);
                            }},
            {ENTITY_MOVE,
                [this](Lobby& lobby,
                    const User& sender,
                    ParsedPacket& packet,
                    const std::string& str) {
                    lobby.handleEntityMove(sender, packet, str);
                }},
            {PLAYER_FIRE,
                [this](Lobby& lobby,
                    const User& sender,
                    ParsedPacket& packet,
                    const std::string& str) {
                    lobby.handlePlayerFire(sender, packet, str);
                }},
            {PLAYER_LEAVE,
                [this](Lobby& lobby,
                    const User& sender,
                    ParsedPacket& packet,
                    const std::string& str) {
                    lobby.handlePlayerLeave(sender, packet, str);
                }},
            {PLAYER_READY,
                [this](Lobby& lobby,
                    const User& sender,
                    ParsedPacket& packet,
                    const std::string& str) {
                    lobby.handlePlayerReady(sender, packet, str);
                }},
            {PLAYER_PAUSE,
                [this](Lobby& lobby,
                    const User& sender,
                    ParsedPacket& packet,
                    const std::string& str) {
                    lobby.handlePlayerPause(sender, packet, str);
                }}}; /*!< List of function to handle the packet */
};