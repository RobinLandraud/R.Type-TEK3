#include "SFMLIpAddress.hpp"

/**
 * \fn std::string SFMLIpAddress::getLocalAdress()
 * \brief Get the local IpAddress
 * \return the local address of the server
 */
std::string SFMLIpAddress::getLocalAdress()
{
    sf::IpAddress ipLocal = sf::IpAddress::getLocalAddress();
    return ipLocal.toString();
}