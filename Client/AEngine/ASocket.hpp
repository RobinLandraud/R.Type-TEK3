#include <iostream>
#pragma once

/**
 * \class ASocket
 * \brief Abstract class for socket.
 * Used to send and receive data
 */
class ASocket
{
  public:
    /**
     * \enum SocketStatus
     * \brief Enum for socket status.
     * used to know the status of the socket
     */
    enum SocketStatus { SUCCES, ERROR, PENDING };

    ASocket() = default;                          /*!< Default constructor */
    ASocket(ASocket&&) = default;                 /*!< Default move constructor */
    ASocket(const ASocket&) = default;            /*!< Default copy constructor */
    ASocket& operator=(ASocket&&) = default;      /*!< Default move assignment operator */
    ASocket& operator=(const ASocket&) = default; /*!< Default copy assignment operator */
    virtual ~ASocket() = default;                 /*!< Default destructor */

    /**
     * \fn virtual SocketStatus bind(int port) = 0;
     * \brief Bind the socket to a port
     * \param port Port to bind
     * \return Socket status
     */
    virtual SocketStatus bind(int port) = 0;

    /**
     * \fn virtual void unbind() = 0;
     * \brief Unbind the socket
     */
    virtual void unbind() = 0;

    /**
     * \fn virtual SocketStatus send(const void* data, std::size_t size, const std::string& remoteAddress, unsigned short remotePort) = 0;
     * \brief Send data to a remote address
     * \param data Data to send
     * \param size Size of the data
     * \param remoteAddress Remote address
     * \param remotePort Remote port
     * \return Socket status
     */
    virtual SocketStatus send(const void* data,
        std::size_t size,
        const std::string& remoteAddress,
        unsigned short remotePort) = 0;

    /**
     * \fn virtual SocketStatus receive(void* data, std::size_t size, std::size_t& received, std::string& remoteAddress, unsigned short& remotePort) = 0;
     * \brief Receive data from a remote address
     * \param data Data to receive
     * \param size Size of the data
     * \param received Size of the received data
     * \param remoteAddress Remote address
     * \param remotePort Remote port
     * \return Socket status
     */
    virtual SocketStatus receive(void* data,
        std::size_t size,
        std::size_t& received,
        std::string& remoteAddress,
        unsigned short& remotePort) = 0;

    /**
     * \fn virtual void setBlocking(bool blocking);
     * \brief Set the socket to blocking
     * \param blocking The new blocking state
     */
    virtual void setBlocking(bool blocking);

    /**
     * \fn [[nodiscard]] bool isBlocking() const;
     * \brief Check if the socket is blocking
     * \return True if the socket is blocking
     */
    [[nodiscard]] bool isBlocking() const;

    /**
     * \fn int getPort();
     * \brief Get the port
     * \return The port
     */
    int getPort();

  protected:
    int port = 0;           /*!< Port */
    bool blocking = false;  /*!< Blocking state */
};

/**
 * \struct ServerToken
 * \brief Struct for server token.
 * Used to send and receive data
 */
struct ServerToken {
    ASocket& socket;    /*!< Socket */
    std::string adress; /*!< Adress */
    int port;           /*!< Port */
};