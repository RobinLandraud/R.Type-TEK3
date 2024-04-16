#include <SFML/Network/UdpSocket.hpp>

#include "ASocket.hpp"

#pragma once

/**
 * \class SFMLSocket
 * \brief A class that handle the socket.
 * Used to handle the socket
 */
class SFMLSocket : public ASocket
{
  public:
    SFMLSocket() = default; /*!< Default constructor */
    SFMLSocket(SFMLSocket&&) = default; /*!< Default move constructor */
    SFMLSocket(const SFMLSocket&) = default;  /*!< Default copy constructor */
    SFMLSocket& operator=(SFMLSocket&&) = default;  /*!< Default move assignment operator */
    SFMLSocket& operator=(const SFMLSocket&) = default; /*!< Default copy assignment operator */
    ~SFMLSocket() override = default; /*!< Default destructor */

    /**
     * \fn SocketStatus bind(int port) override;
     * \brief Bind the socket to a port
     * \param port The port to bind
     * \return The status of the socket
     */
    SocketStatus bind(int port) override;

    /**
     * \fn void unbind() override;
     * \brief Unbind the socket
     */
    void unbind() override;

    /**
     * \fn SocketStatus send(const void* data, std::size_t size, const IpAddress& remoteAddress, unsigned short remotePort) override;
     * \brief Send data to a remote address
     * \param data The data to send
     * \param size The size of the data
     * \param remoteAddress The address of the remote
     * \param remotePort The port of the remote
     * \return The status of the socket
     */
    SocketStatus send(const void* data,
        std::size_t size,
        const std::string& remoteAddress,
        unsigned short remotePort) override;

    /**
     * \fn SocketStatus receive(void* data, std::size_t size, std::size_t& received, std::string& remoteAddress, unsigned short& remotePort) override;
     * \brief Receive data from a remote address
     * \param data The data to receive
     * \param size The size of the data
     * \param received The size of the data received
     * \param remoteAddress The address of the remote
     * \param remotePort The port of the remote
     * \return The status of the socket
     */
    SocketStatus receive(void* data,
        std::size_t size,
        std::size_t& received,
        std::string& remoteAddress,
        unsigned short& remotePort) override;

    /**
     * \fn void setBlocking(bool blocking) override;
     * \brief Set the socket to blocking or not
     * \param blocking The blocking state
     */
    void setBlocking(bool blocking) override;

  private:
    sf::UdpSocket socket; /*!< The socket */
};