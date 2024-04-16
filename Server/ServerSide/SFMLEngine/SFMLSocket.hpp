#include <SFML/Network/UdpSocket.hpp>

#include "ASocket.hpp"

#pragma once

/**
 * \class SFMLSocket
 * \brief A SFML socket class
 */

class SFMLSocket : public ASocket
{
  public:
    SFMLSocket() = default; /*!< Default constructor */
    SFMLSocket(SFMLSocket&&) = default; /*!< Move constructor */
    SFMLSocket(const SFMLSocket&) = default; /*!< Copy constructor */
    SFMLSocket& operator=(SFMLSocket&&) = default; /*!< Move assignment operator */
    SFMLSocket& operator=(const SFMLSocket&) = default; /*!< Copy assignment operator */
    ~SFMLSocket() override = default; /*!< Default Destructor */

    /**
     * \fn SocketStatus bind(int port) override;
     * \brief Bind a socket on a port
     * \param port the port you want the socket get bind on
     * \return the status of the socket you tried to bind
     */
    SocketStatus bind(int port) override;
  
    /**
     * \fn void unbind() override;
     * \brief Unbind a socket
     */
    void unbind() override;

    /**
     * \fn SocketStatus send(const void* data, std::size_t size, const std::string& remoteAddress, unsigned short remotePort) override;
     * \brief Send data to another socket
     * \param data the data you want to send
     * \param size the size of the data you want to send
     * \param remoteAddress the address of the socket that you want to send data
     * \param remotePort the port of the socket you want to send data
     * \return the status of the socket after you tried to send data
     */
    SocketStatus send(const void* data,
        std::size_t size,
        const std::string& remoteAddress,
        unsigned short remotePort) override;

    /**
     * \fn SocketStatus receive(void* data, std::size_t size, std::size_t& received, std::string& remoteAddress, unsigned short& remotePort) override;
     * \brief Recieve data from another socket
     * \param data the data you will receive
     * \param size the size of the data you will receive
     * \param remoteAddress the address of the socket that want to send you data
     * \param remotePort the port of the socket that want to send you data
     * \return the status of the socket after you receive data
     */
    SocketStatus receive(void* data,
        std::size_t size,
        std::size_t& received,
        std::string& remoteAddress,
        unsigned short& remotePort) override;

    /**
     * \fn void setBlocking(bool blocking) override;
     * \brief Change the blocking state of the socket
     * \param blocking the statement you want to put on the socket
     */
    void setBlocking(bool blocking) override;

  private:
    sf::UdpSocket socket; /*!< Socket to communicate with the client */
};