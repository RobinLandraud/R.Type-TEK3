#include <iostream>
#pragma once

/**
* \class ASocket
* \brief Abstract class for socket
*/
class ASocket
{
  public:
    /**
     * \enum SocketType
     * \brief Socket status
     */
    enum SocketStatus { SUCCES, ERROR, PENDING };

    ASocket() = default; /*!< Default constructor */
    ASocket(ASocket&&) = default; /*!< Move constructor */
    ASocket(const ASocket&) = default; /*!< Copy constructor */
    ASocket& operator=(ASocket&&) = default; /*!< Move operator */
    ASocket& operator=(const ASocket&) = default; /*!< Copy operator */
    virtual ~ASocket() = default; /*!< Default destructor */

    /**
     * \fn virtual SocketStatus bind() = 0
     * \brief Bind the socket
     * \return SocketStatus
     */
    virtual SocketStatus bind(int port) = 0;

    /**
     * \fn virtual void unbind() = 0
     * \brief Unbind the socket
     */
    virtual void unbind() = 0;

    /**
     * \fn virtual SocketStatus send() = 0
     * \brief Send data
     * \return SocketStatus
     */
    virtual SocketStatus send(const void* data,
        std::size_t size,
        const std::string& remoteAddress,
        unsigned short remotePort) = 0;
    
    /**
     * \fn virtual SocketStatus receive() = 0
     * \brief Receive data
     * \return SocketStatus
     */
    virtual SocketStatus receive(void* data,
        std::size_t size,
        std::size_t& received,
        std::string& remoteAddress,
        unsigned short& remotePort) = 0;

    /**
     * \fn virtual void receive() = 0
     * \brief Close the socket
     */
    virtual void setBlocking(bool blocking);

    /**
     * \fn [[nodiscard]] virtual bool isBlocking() const
     * \brief Check if the socket is blocking
     * \return bool
     */
    [[nodiscard]] bool isBlocking() const;

    /**
     * \fn int getPort()
     * \brief Get the port
     * \return int
     */
    int getPort();

  protected:
    int port = 0; /*!< Port */
    bool blocking = false; /*!< Blocking */
};