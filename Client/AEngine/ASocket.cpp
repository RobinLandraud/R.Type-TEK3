#include "ASocket.hpp"

/**
 * \fn int ASocket::getPort()
 * \brief Get the port
 * \return The port
 */
int ASocket::getPort()
{
    return this->port;
}

/**
 * \fn ASocket::setBlocking()
 * \brief Set the socket to blocking
 * \param newBlocking The new blocking state
 */
void ASocket::setBlocking(bool newBlocking)
{
    blocking = newBlocking;
}

/**
 * \fn bool ASocket::isBlocking() 
 * \brief Check if the socket is blocking
 * \return True if the socket is blocking
 */
bool ASocket::isBlocking() const
{
    return blocking;
}