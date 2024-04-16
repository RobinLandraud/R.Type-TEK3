#include "SFMLSocket.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Socket.hpp>
#include <algorithm>

/**
 * \fn ASocket::SocketStatus SFMLSocket::bind(int port)
 * \brief Bind the socket to a port
 * \param port The port to bind
 * \return The status of the socket
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
 * \brief Unbind the socket
 */
void SFMLSocket::unbind()
{
    socket.unbind();
}

/**
 * \fn ASocket::SocketStatus SFMLSocket::send(const void* data, std::size_t size, const IpAddress& remoteAddress, unsigned short remotePort)
 * \brief Send data to a remote address
 * \param data The data to send
 * \param size The size of the data
 * \param remoteAddress The address of the remote
 * \param remotePort The port of the remote
 * \return The status of the socket
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
 * \brief Receive data from a remote address
 * \param data The data to receive
 * \param size The size of the data
 * \param received The size of the data received
 * \param remoteAddress The address of the remote
 * \param remotePort The port of the remote
 * \return The status of the socket
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
 * \brief Set the socket to blocking or not
 * \param blocking The blocking state
 */
void SFMLSocket::setBlocking(bool blocking)
{
    this->blocking = blocking;
    socket.setBlocking(blocking);
}