#include <SFML/Network/IpAddress.hpp>

#pragma once

/**
 * \class SFMLIpAddress
 * \brief A SFML IpAddress class
 */

class SFMLIpAddress
{
  public:
    SFMLIpAddress() = default; /*!< Default constructor */
    SFMLIpAddress(SFMLIpAddress&&) = default; /*!< Move constructor */
    SFMLIpAddress(const SFMLIpAddress&) = default; /*!< Copy constructor */
    SFMLIpAddress& operator=(SFMLIpAddress&&) = default; /*!< Move assignment operator */
    SFMLIpAddress& operator=(const SFMLIpAddress&) = default; /*!< Copy assignment operator */
    ~SFMLIpAddress() = default; /*!< Default Destructor */

    /**
     * \fn static std::string getLocalAdress();
     * \brief Get the local IpAddress
     * \return the local address of the server
     */
    static std::string getLocalAdress();

  private:
};