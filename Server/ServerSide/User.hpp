#include <stdio.h>
#include <string.h>

#include <cstdio>
#include <iostream>

#pragma once

/**
 * \struct User
 * \brief The user
 */
struct User {
    std::string name;   /*!< The name of the user */
    std::string ip;    /*!< The ip of the user */
    unsigned short port;    /*!< The port of the user */

    bool isActive = false;  /*!< Is the user active */

    /**
     * \fn bool operator<(const User& o) const
     * \brief Operator < overload
     * \param o The user to compare
     * \return true if the user is less than the other user, false otherwise
     */
    bool operator<(const User& o) const
    {
        return name == o.name && ip == o.ip && port == o.port
               && isActive == o.isActive;
    }

    /**
     * \fn bool operator==(const User& lhs) const
     * \brief Operator == overload
     * \param lhs The user to compare
     * \return true if the user is equal to the other user, false otherwise
     */
    bool operator==(const User& lhs) const
    { 
        return lhs.ip == ip && lhs.name == name && port == lhs.port;
    }

    /**
     * \fn bool operator!=(const User& lhs) const
     * \brief Operator != overload
     * \param lhs The user to compare
     * \return true if the user is not equal to the other user, false otherwise
     */
    bool operator!=(const User& lhs) const
    {
        return !(lhs == *this);
    }
};