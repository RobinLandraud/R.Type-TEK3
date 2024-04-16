#include <string>

#include "ProtocolParser.hpp"

#pragma once

#define MAX_STR_LENGTH 1024

/**
 * \fn std::string convertToString(const char* array)
 * \brief Converts a char array to a string
 * \param array The char array to convert
 * \return The converted string
 */
std::string convertToString(const char* array);

/**
 * \fn ParsedPacket getHeader(unsigned const char data[sizeof(u_int64_t) + MAX_STR_LENGTH])
 * \brief Gets the header of a packet
 * \param data The data to get the header from
 * \return The header of the packet
 */
ParsedPacket getHeader(
    unsigned const char data[sizeof(u_int64_t) + MAX_STR_LENGTH]);