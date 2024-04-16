#include <cmath>
#include <cstdint>
#include <cstring>

#include "ProtocolParser.hpp"

/**
 * \class ProtocolBuilder
 * \brief A class that handle the protocol
 */
class ProtocolBuilder
{
  public:
    ProtocolBuilder() = default;    /*!< Default constructor */
    ~ProtocolBuilder() = default;   /*!< Default destructor */

    /**
     * \fn static std::uint64_t createPacket(Protocol protocol, int arg1, int arg2, int arg3, int arg4)
     * \brief Create a packet
     * \param protocol The protocol
     * \param arg1 The first argument
     * \param arg2 The second argument
     * \param arg3 The third argument
     * \param arg4 The fourth argument
     * \return std::uint64_t The packet
     */
    static std::uint64_t createPacket(
        Protocol protocol, int arg1, int arg2, int arg3, int arg4)
    {
        if (arg1 > 9999 || arg2 > 9999 || arg3 > 9999 || arg4 > 9999)
            return 0;
        return ((static_cast<int>(protocol) * 10000000000000000)
                + (static_cast<std::uint64_t>(arg1) * 1000000000000)
                + (static_cast<std::uint64_t>(arg2) * 100000000)
                + (static_cast<std::uint64_t>(arg3) * 10000)
                + (static_cast<std::uint64_t>(arg4)));
    }

    /**
     * \fn static std::uint64_t createPacket(ElementType type, int method, int arg1, int arg2, int arg3, int arg4)
     * \brief Create a packet
     * \param type The type of the element
     * \param method The method of the element
     * \param arg1 The first argument
     * \param arg2 The second argument
     * \param arg3 The third argument
     * \param arg4 The fourth argument
     * \return The packet
     */
    static std::uint64_t createPacket(
        ElementType type, int method, int arg1, int arg2, int arg3, int arg4)
    {
        if (arg1 > 9999 || arg2 > 9999 || arg3 > 9999 || arg4 > 9999
            || method > 99)
            return 0;
        return ((static_cast<int>(type) * 1000000000000000000)
                + (method * 10000000000000000)
                + (static_cast<std::uint64_t>(arg1) * 1000000000000)
                + (static_cast<std::uint64_t>(arg2) * 100000000)
                + (static_cast<std::uint64_t>(arg3) * 10000)
                + (static_cast<std::uint64_t>(arg4)));
    }

    /**
     * \fn static int BoolToInt(bool arg)
     * \brief Convert a bool to an int
     * \param arg The bool
     * \return The int
     */
    static int BoolToInt(bool arg)
    {
        if (arg)
            return 1;
        return 0;
    }

    /**
     * \fn static int FloatToInt(float arg)
     * \brief Convert a float to an int
     * \param arg The float
     * \return The int
     */
    static int FloatToInt(float arg)
    {
        return std::floor(arg + 0.5);
    }

    /**
     * \fn static void buildPacket(char* data, std::uint64_t packet)
     * \brief Build a packet
     * \param data The data
     * \param packet The packet
     */
    static void buildPacket(char* data, std::uint64_t packet)
    {
        std::memcpy(data, &packet, sizeof(std::uint64_t));
    }

    /**
     * \fn static void buildPacket(char* data, std::uint64_t packet, std::string str)
     * \brief Build a packet
     * \param data The data
     * \param packet The packet
     * \param str The string
     */
    static void buildPacket(char* data, std::uint64_t packet, std::string str)
    {
        std::memcpy(data, &packet, sizeof(std::uint64_t));
        std::memcpy(data + sizeof(std::uint64_t), str.c_str(), str.size() + 1);
    }
};