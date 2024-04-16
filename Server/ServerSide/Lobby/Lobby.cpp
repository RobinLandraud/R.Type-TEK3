#include "Lobby.hpp"

#include <libintl.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstddef>
#include <iterator>
#include <ostream>
#include <thread>
#include <chrono>
#include <utility>
#include <vector>

#include "ASocket.hpp"
#include "ProtocolParser.hpp"
#include "User.hpp"
#include "utils.hpp"

/**
 * \fn Lobby::Lobby(int mainPort, User owner, std::string name, int hubID): game(*socket), name(std::move(name)), owner(std::move(owner))
 * \brief Constructor of the Lobby class
 * \param mainPort The port of the server
 * \param owner The owner of the lobby
 * \param name The name of the lobby
 * \param hubID The ID of the hub
 */
Lobby::Lobby(int mainPort, User owner, std::string name, int hubID)
    : game(*socket)
    , name(std::move(name))
    , owner(std::move(owner))
{
    users.emplace_back(std::pair<User, bool>{owner, false});
    socket->setBlocking(false);
    if (socket->bind(0) == ASocket::SUCCES) {
        std::cout << "["<< this->name << "] " << "New lobby created on port: " << socket->getPort()
                  << std::endl;
        int up = floor(socket->getPort() / 1000);
        int down = socket->getPort() % 1000;
        u_int64_t newHeader = ProtocolBuilder::createPacket(
            HUB_SERVER_CREATE, up, down, hubID, 0);
        char rData[sizeof(newHeader)];
        memcpy(rData, &newHeader, sizeof(newHeader));
        socket->send(
            rData, sizeof(rData), SFMLIpAddress::getLocalAdress(), mainPort);
        ParsedPacket dumb = ParsedPacket{ElementType::UNKNOWN, 0, {}};
        sendSuccesCreateToOwner();
    }
    // TODO(bilj): else send failed to create
}

/**
 * \fn bool sendWithoutString(ASocket& socket, uint64_t header, const std::string& adress, int remotePort)
 * \brief Send a packet without a string
 * \param socket The socket to send the packet
 * \param header The header of the packet
 * \param adress The adress of the remote
 * \param remotePort The port of the remote
 * \return true if the packet was sent, false otherwise
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
 * \fn bool sendWithString(ASocket& socket, uint64_t header, const std::string& buffer, const std::string& adress, int remotePort)
 * \brief Send a packet with a string
 * \param socket The socket to send the packet
 * \param header The header of the packet
 * \param buffer The string to send
 * \param adress The adress of the remote
 * \param remotePort The port of the remote
 * \return true if the packet was sent, false otherwise
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
        std::cout  << "Send error" << std::endl;
        return false;
    }
    return true;
}

/**
 * \fn void Lobby::sendSuccesCreateToOwner()
 * \brief Send a succes create packet to the owner of the lobby
 */
void Lobby::sendSuccesCreateToOwner() {
    int up = floor(socket->getPort() / 1000);
    int down = socket->getPort() % 1000;
    u_int64_t newHeader = ProtocolBuilder::createPacket(HUB_SUCCESFULLY_CREATE, up, down, 0, 0);
    sendWithoutString(*socket, newHeader, owner.ip, owner.port);
}

/**
 * \fn void Lobby::handlePacket()
 * \brief Handle the packet received by the socket
 */
void Lobby::handlePacket()
{
    while (!hasToStop) {
        std::string rIP;
        unsigned short port = 0;
        std::size_t received = 0;
        unsigned char data[sizeof(u_int64_t) + MAX_STR_LENGTH];
        if (socket->receive(&data, sizeof(data), received, rIP, port)
            == ASocket::SUCCES) {
            bool find = false;
            User sender;
            for (auto& user : users) {
                if (user.first.port == port) {
                    sender = user.first;
                    find = true;
                    break;
                }
            }
            ParsedPacket header = getHeader(data);
            unsigned short protocolId =
                ProtocolParser::getProtocol(header.element, header.MethodID);
            if (find) {
                auto funcIt =
                    functionList.find(static_cast<Protocol>(protocolId));
                std::string strArgs;
                if (funcIt == functionList.end()) {
                    std::cout << "["<< name << "] "
                        << "Invalid method reférence, or not yet implemented: "
                        << protocolId << std::endl;
                } else {
                    if (received > sizeof(u_int64_t))
                        strArgs = convertToString(
                            reinterpret_cast<char*>(data + sizeof(u_int64_t)));
                    auto func = funcIt->second;
                    func(*this, sender, header, strArgs);
                }
            } else {
                if (protocolId == CONNECT)
                    handleConnect(port, rIP, data);
                else if (protocolId == HUB_STATUS) {
                    std::string strArgs;
                    if (received > sizeof(u_int64_t))
                        strArgs = convertToString(
                            reinterpret_cast<char*>(data + sizeof(u_int64_t)));
                    handleStatus({"uncknow", rIP, port}, header, strArgs);
                }
            }
        }
        game.loop();
    }
}

/**
 * \fn void Lobby::sendAllPlayerName(User receiver)
 * \brief Send all the player name to the receiver
 * \param receiver The receiver of the packet
 */
void Lobby::sendAllPlayerName(User receiver) {
    int count = 0;
    for (const auto& user: users) {
        size_t id = game.registerNameUser(user.first);
        u_int64_t header = ProtocolBuilder::createPacket(ENTITY_SPAWN, id, TEXT_ENTITY, 400, 500 + count * 20);
        sendWithString(*socket, header, user.first.name, receiver.ip, receiver.port);
    }
}

/**
 * \fn void Lobby::handleConnect(unsigned short port, sf::IpAddress rIP, unsigned char data[sizeof(u_int64_t) + MAX_STR_LENGTH])
 * \brief Handle the connect packet
 * \param port The port of the sender
 * \param rIP The ip of the sender
 * \param data The data of the packet
 */
void Lobby::handleConnect(unsigned short port,
    std::string rIP,
    unsigned char data[sizeof(u_int64_t) + MAX_STR_LENGTH])
{
    std::string pseudo =
        convertToString(reinterpret_cast<char*>(data + sizeof(u_int64_t)));
    // TODO(bilj): check status server + place restante, si pas bon return pas
    // bon
    User newU;
    newU.name = pseudo;
    newU.ip = rIP;
    newU.port = port;
    this->users.emplace_back(std::pair<User, bool>{newU, false});
    std::cout << "[" << this->name << "]"
              << " New User connected:" << pseudo << std::endl;
    u_int64_t newHeader = ProtocolBuilder::createPacket(HUB_CONNECT_SUCCES, 0, 0, 0, 0);
    sendWithoutString(*socket, newHeader, rIP, port);
    // répondre au client inscrit avec un entity spawn text nom des joueurs
}

/**
 * \fn void Lobby::handleStatus(const User& sender, ParsedPacket& packet, const std::string& str)
 * \brief Handle the status packet
 * \param sender The sender of the packet
 * \param packet The packet
 * \param str The string of the packet
 */
void Lobby::handleStatus(
    const User& sender, ParsedPacket& packet, const std::string& str)
{
    std::cout << "["<< name << "] " << "Lobby, handle status" << std::endl;
    u_int64_t newHeader = 0;
    int nbPlayer = static_cast<int>(users.size());
    if (game.isRunnning() || nbPlayer >= MAX_PLAYER)
        newHeader =
            ProtocolBuilder::createPacket(HUB_STATUS, nbPlayer, 0, 0, 0);
    else
        newHeader =
            ProtocolBuilder::createPacket(HUB_STATUS, nbPlayer, 1, 0, 0);
    char rData[sizeof(newHeader) + MAX_STR_LENGTH];
    memcpy(rData, &newHeader, sizeof(newHeader));
    memcpy(rData + sizeof(newHeader), name.c_str(), name.length() + 1);
    std::cout << "["<< name << "] << " "Lobby adress: " << sender.ip << " port: " << sender.port
              << std::endl;
    if (socket->send(rData, sizeof(rData), sender.ip, sender.port)
        != ASocket::SUCCES) {
        std::cout << "["<< name << "] " << "Error when responding status in lobby" << std::endl;
    }
}

/**
 * \fn void Lobby::handleEntityMove(const User& sender, ParsedPacket& packet, const std::string& str)
 * \brief Handle the entity move packet
 * \param sender The sender of the packet
 * \param packet The packet
 * \param str The string of the packet
 */
void Lobby::handleEntityMove(
    const User& sender, ParsedPacket& packet, const std::string& str)
{
    game.moveEntity(
        packet.arguments[0], packet.arguments[1], packet.arguments[2]);
}

/**
 * \fn void Lobby::handlePlayerFire(const User& sender, ParsedPacket& packet, const std::string& str)
 * \brief Handle the player fire packet
 * \param sender The sender of the packet
 * \param packet The packet
 * \param str The string of the packet
 */
void Lobby::handlePlayerFire(
    const User& sender, ParsedPacket& packet, const std::string& str)
{
    game.playerFire(sender, static_cast<Game::FireType>(packet.arguments[0]));
}

/**
 * \fn void Lobby::handlePlayerLeave(const User& sender, ParsedPacket& packet, const std::string& str)
 * \brief Handle the player leave packet
 * \param sender The sender of the packet
 * \param packet The packet
 * \param str The string of the packet
 */
void Lobby::handlePlayerLeave(
    const User& sender, ParsedPacket& packet, const std::string& str)
{
    game.playerLeave(sender);
    for (int i = 0; i < users.size(); i++) {
        auto it = users.begin();
        std::advance(it, i);
        auto user = it->first;
        if (user.port == sender.port && user.ip == sender.ip) {
            users.erase(it);
            return;
        }
    }
}

/**
 * \fn void Lobby::startGame()
 * \brief Start the game
 */
void Lobby::startGame() {
    for (auto &user: users) {
        if (!user.second)
            return;
    }
    u_int64_t newHeader = ProtocolBuilder::createPacket(GAME_START, 0, 0, 0, 0);
    std::vector<User> userList {};
    for (auto &user: users) {
        userList.push_back(user.first);
        sendWithoutString(*socket, newHeader, user.first.ip, user.first.port);
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    game.start(userList);
}

/**
 * \fn void Lobby::handlePlayerReady(const User& sender, ParsedPacket& packet, const std::string& str)
 * \brief Handle the player ready packet
 * \param sender The sender of the packet
 * \param packet The packet
 * \param str The string of the packet
 */
void Lobby::handlePlayerReady(
    const User& sender, ParsedPacket& packet, const std::string& str)
{
    for (auto& user : users) {
        if (user.first.port == sender.port) {
            std::cout << "["<< name << "] " << sender.name << " ready status change" << std::endl;
            user.second = !user.second;
            startGame();
            return;
        }
    }
}

/**
 * \fn void Lobby::handlePlayerPause(const User& sender, ParsedPacket& packet, const std::string& str)
 * \brief Handle the player pause packet
 * \param sender The sender of the packet
 * \param packet The packet
 * \param str The string of the packet
 */
void Lobby::handlePlayerPause(
    const User& sender, ParsedPacket& packet, const std::string& str)
{
}

/**
 * \fn void Lobby::handlePlayerSendMessage(const User& sender, ParsedPacket& packet, const std::string& str)
 * \brief Handle the player send message packet
 * \param sender The sender of the packet
 * \param packet The packet
 * \param str The string of the packet
 */
void Lobby::handlePlayerSendMessage(
    const User& sender, ParsedPacket& packet, const std::string& str)
{
}

/**
 * \fn void Lobby::handlePlayerSwitchSkin(const User& sender, ParsedPacket& packet, const std::string& str)
 * \brief Handle the player switch skin packet
 * \param sender The sender of the packet
 * \param packet The packet
 * \param str The string of the packet
 */
void Lobby::handlePlayerSwitchSkin(
    const User& sender, ParsedPacket& packet, const std::string& str)
{
}
