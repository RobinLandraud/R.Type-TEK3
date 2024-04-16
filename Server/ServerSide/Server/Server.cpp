/*
** EPITECH PROJECT, 2022
** B-CPP-500-BDX-5-1-rtype-nicolas.lavigne
** File description:
** Server
*/

#include "Server.hpp"

#include <ostream>

#include "ProtocolParser.hpp"

/**
 * \fn Server::Server()
 * \brief Constructor of the server class
 */
Server::Server()
{
    std::string ipLocal = SFMLIpAddress::getLocalAdress();
    std::cout << "Server Etablished on: " << ipLocal << std::endl;
}

/**
 * \fn int Server::getUnusedID()
 * \brief get an unused ID
 * \return value of an id unused
 */
int Server::getUnusedID()
{
    int max = 0;
    for (auto& it : lobbyList) {
        if (it.first > max)
            max = it.first;
    }
    return max + 1;
}

/**
 * \fn void Server::createNewLobby(const User& owner, const std::string& lobbyName, int mainPort, int hubID)
 * \brief create a new lobby
 * \param owner the owner of the new lobby
 * \param lobbyName the name of the lobby
 * \param mainPort the mainport
 * \param hubID id of the hub
 */
void Server::createNewLobby(
    const User& owner, const std::string& lobbyName, int mainPort, int hubID)
{
    Lobby newLobby(mainPort, owner, lobbyName, hubID);
    newLobby.handlePacket();
}

/**
 * \fn void Server::addNewLobby(const User& owner, const std::string& lobbyName)
 * \brief Add a new lobby
 * \param owner the owner of the new lobby
 * \param lobbyName the name of the lobby
 */
void Server::addNewLobby(const User& owner, const std::string& lobbyName)
{
    int newId = getUnusedID();
    if (newId == -1)
        return;
    std::thread newThread(
        Server::createNewLobby, owner, lobbyName, originPort, newId);
    newThread.detach();
    this->lobbyList.emplace(std::pair<int, Hub>(newId, Hub{newId, newThread}));
    std::cout << "New Hub \"" << lobbyName
              << "\" request to be created by:" << owner.name << std::endl;
}

/**
 * \fn void Server::handleUser()
 * \brief Handle the user
 */
void Server::handleUser()
{
    std::unique_ptr<ASocket> socket = std::make_unique<SFMLSocket>();
    socket->bind(0);
    originPort = socket->getPort();
    std::cout << "Port used: " << originPort << std::endl;
    while (true) {
        std::string rIP;
        unsigned short port = 0;
        std::size_t received = 0;
        unsigned char data[sizeof(u_int64_t) + MAX_STR_LENGTH];
        if (socket->receive(data, sizeof(data), received, rIP, port)
            == ASocket::SUCCES) {
            ParsedPacket header = getHeader(data);
            unsigned short protocolId =
                ProtocolParser::getProtocol(header.element, header.MethodID);
            std::string strArgs;
            if (received > sizeof(u_int64_t))
                strArgs = convertToString(
                    reinterpret_cast<char*>(data + sizeof(u_int64_t)));
            switch (protocolId) {
                case CREATE: {
                    User tempUser;
                    tempUser.name = strArgs.substr(strArgs.find('\n') + 1);
                    tempUser.ip = rIP;
                    tempUser.port = port;
                    tempUser.isActive = true;
                    addNewLobby(
                        tempUser, strArgs.substr(0, strArgs.find('\n')));
                    break;
                }
                case HUB_SERVER_CREATE: {
                    int hubPort =
                        header.arguments[0] * 1000 + header.arguments[1];
                    int hubId = header.arguments[2];
                    auto tempHubIt = lobbyList.find(hubId);
                    tempHubIt->second.port = hubPort;
                    std::cout << "Hub succefully create:" << hubPort
                              << std::endl;
                    std::cout << "Hub id: " << hubId << std::endl;
                    break;
                }
                case GET_HUB_LIST: {
                    for (auto& it : lobbyList) {
                        if (it.second.port == -1)
                            continue;
                        int up = floor(it.second.port / 1000);
                        int down = it.second.port % 1000;
                        u_int64_t newHeader = ProtocolBuilder::createPacket(
                            HUB_LIST, up, down, 0, 0);
                        char rData[sizeof(newHeader)];
                        std::memcpy(rData, &newHeader, sizeof(newHeader));
                        if (socket->send(rData, sizeof(newHeader), rIP, port)
                            != ASocket::SUCCES)
                            std::cout << "error will sending";
                        std::this_thread::sleep_for(
                            std::chrono::milliseconds(1));
                    }
                    u_int64_t newHeader =
                        ProtocolBuilder::createPacket(No_HUB_EXIST, 0, 0, 0, 0);
                    char rData[sizeof(newHeader)];
                    std::memcpy(rData, &newHeader, sizeof(newHeader));
                    socket->send(rData, sizeof(rData), rIP, port);
                    break;
                }
                default:
                    std::cout
                        << "Invalid method reférence, or not yet implemented: "
                        << protocolId << std::endl;
                    break;
            }
        }
    }
}