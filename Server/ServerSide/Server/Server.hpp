/*
** EPITECH PROJECT, 2022
** B-CPP-500-BDX-5-1-rtype-nicolas.lavigne
** File description:
** Server
*/

#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <thread>
#include <vector>

#include "Lobby.hpp"
#include "SFMLIpAddress.hpp"
#include "User.hpp"

/**
 * \struct Hub
 * \brief A Hub struct
 */
struct Hub {
    int port; /*!< Port of the Hub */
    std::thread& thread; /*!< Thread of the Hub */
};

/**
 * \class Server
 * \brief A Server class
 */

class Server
{
  public:
    Server(); /*!< Default constructor */
    Server(Server const&) = default; /*!< Default copy constructor */
    Server(Server&&) noexcept = default; /*!< Default move constructor */
    Server& operator=(Server const&) = default; /*!< Default copy assignment operator */
    Server& operator=(Server&&) noexcept = default; /*!< Default move assignment operator */
    ~Server() = default; /*!< Default Destructor */

    /**
     * \fn void handleUser();
     * \brief Handle the user
     */
    void handleUser();

    /**
     * \fn void addNewLobby(const User&, const std::string&);
     * \brief Add a new lobby
     * \param owner the owner of the new lobby
     * \param lobbyName the name of the lobby
     */
    void addNewLobby(const User& owner, const std::string& lobbyName);

  private:
    int originPort = 2312; /*!< The origin port */

    /**
     * \fn static void createNewLobby(const User& owner, const std::string& lobbyName, int mainPort, int hubID);
     * \brief create a new lobby
     * \param owner the owner of the new lobby
     * \param lobbyName the name of the lobby
     * \param mainPort the mainport
     * \param hubID id of the hub
     */
    static void createNewLobby(const User& owner, const std::string& lobbyName, int mainPort, int hubID);

    /**
     * \fn int getUnusedID();
     * \brief get an unused ID
     * \return value of an id unused
     */
    int getUnusedID();
    std::map<int, Hub> lobbyList; /*!< a list of each hub with their port */
};
