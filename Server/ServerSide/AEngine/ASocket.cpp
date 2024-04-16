#include "ASocket.hpp"

/**
 * \fn ASocket::getPort()
 * \brief Get the port number of the socket
 * \return int
 */
int ASocket::getPort()
{
    return this->port;
}

/**
 * \fn void ASocket::setBlocking(bool newBlocking)
 * \brief Set the blocking mode of the socket
 */
void ASocket::setBlocking(bool newBlocking)
{
    blocking = newBlocking;
}

/**
 * \fn bool ASocket::isBlocking()
 * \brief Get the blocking mode of the socket
 * \return bool
 */
bool ASocket::isBlocking() const
{
    return blocking;
}