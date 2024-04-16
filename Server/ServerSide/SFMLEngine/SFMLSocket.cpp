#include "SFMLSocket.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Socket.hpp>
#include <algorithm>

/**
 * \fn ASocket:SocketStatus SFMLSocket::bind(int port)
 * \brief Bind a socket on a port
 * \param port the port you want the socket get bind on
 * \return the status of the socket you tried to bind
 */
ASocket::SocketStatus SFMLSocket::bind(int port)
{
    this->port = port;
    if (socket.bind(port) == sf::Socket::Done) {
        this->port = socket.getLocalPort();
        return ASocket::SUCCES;
    }
    return ASocket::ERROR;
}

/**
 * \fn void SFMLSocket::unbind()
 * \brief Unbind a socket
 */
void SFMLSocket::unbind()
{
    socket.unbind();
}

/**
 * \fn ASocket::SocketStatus SFMLSocket::send(const void* data, std::size_t size, const std::string& remoteAddress, unsigned short remotePort)
 * \brief Send data to another socket
 * \param data the data you want to send
 * \param size the size of the data you want to send
 * \param remoteAddress the address of the socket that you want to send data
 * \param remotePort the port of the socket you want to send data
 * \return the status of the socket after you tried to send data
 */
ASocket::SocketStatus SFMLSocket::send(const void* data,
    std::size_t size,
    const std::string& remoteAddress,
    unsigned short remotePort)
{
    sf::IpAddress address(remoteAddress);
    if (socket.send(data, size, address, remotePort) == sf::Socket::Done)
        return ASocket::SUCCES;
    return ASocket::ERROR;
}

/**
 * \fn ASocket::SocketStatus SFMLSocket::receive(void* data, std::size_t size, std::size_t& received, std::string& remoteAddress, unsigned short& remotePort)
 * \brief Recieve data from another socket
 * \param data the data you will receive
 * \param size the size of the data you will receive
 * \param remoteAddress the address of the socket that want to send you data
 * \param remotePort the port of the socket that want to send you data
 * \return the status of the socket after you receive data
 */
ASocket::SocketStatus SFMLSocket::receive(void* data,
    std::size_t size,
    std::size_t& received,
    std::string& remoteAddress,
    unsigned short& remotePort)
{
    sf::IpAddress address(remoteAddress);
    if (socket.receive(data, size, received, address, remotePort)
        == sf::Socket::Done) {
        remoteAddress = address.toString();
        return ASocket::SUCCES;
    }
    return ASocket::ERROR;
}

/**
 * \fn void SFMLSocket::setBlocking(bool blocking)
 * \brief Change the blocking state of the socket
 * \param blocking the statement you want to put on the socket
 */
void SFMLSocket::setBlocking(bool blocking)
{
    this->blocking = blocking;
    socket.setBlocking(blocking);
}