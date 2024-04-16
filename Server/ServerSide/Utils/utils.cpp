#include "utils.hpp"

#include <ostream>

/**
 * \fn std::string convertToString(const char* array)
 * \brief Convert a char array to a string
 * \param array The char array to convert
 * \return The string
 */
std::string convertToString(const char* array)
{
    std::string str = array;
    return str;
}

/**
 * \fn ParsedPacket getHeader(unsigned const char data[sizeof(u_int64_t) + MAX_STR_LENGTH])
 * \brief Get the header of a packet
 * \param data The data of the packet
 * \return The header of the packet
 */
ParsedPacket getHeader(
    unsigned const char data[sizeof(u_int64_t) + MAX_STR_LENGTH])
{
    uint64_t head = static_cast<uint64_t>(data[0])
                    | static_cast<uint64_t>(data[1]) << 8
                    | static_cast<uint64_t>(data[2]) << 16
                    | static_cast<uint64_t>(data[3]) << 24
                    | static_cast<uint64_t>(data[4]) << 32
                    | static_cast<uint64_t>(data[5]) << 40
                    | static_cast<uint64_t>(data[6]) << 48
                    | static_cast<uint64_t>(data[7]) << 56;
    ParsedPacket header = ProtocolParser::getPacket(head);
    return header;
}