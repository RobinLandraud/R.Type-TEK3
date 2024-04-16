#include <cmath>
#include <cstdint>

#include "ProtocolParser.hpp"

#pragma once

/**
 * \class ProtocolBuilder
 * \brief Class to build a protocol message
 */
class ProtocolBuilder
{
  public:
    ProtocolBuilder() = default; /*!< Default constructor */
    ~ProtocolBuilder() = default; /*!< Default destructor */

    /**
     * \fn static std::uint64_t createPacket(Protocol protocol, int arg1, int arg2, int arg3, int arg4)
     * \brief Create a packet
     * \param protocol Protocol to use
     * \param arg1 First argument
     * \param arg2 Second argument
     * \param arg3 Third argument
     * \param arg4 Fourth argument
     * \return Packet
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
     * \fn static std::uint64_t createPacket(ElementType type, int method, int arg1, int arg2, int arg3)
     * \brief Create a packet
     * \param type Type of the element
     * \param method Method to use
     * \param arg1 First argument
     * \param arg2 Second argument
     * \param arg3 Third argument
     * \return Packet
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
     * \brief Convert a boolean to an integer
     * \param arg Boolean to convert
     * \return Integer
     */
    static int BoolToInt(bool arg)
    {
        if (arg)
            return 1;
        return 0;
    }

    /**
     * \fn static int FloatToInt(float arg)
     * \brief Convert a float to an integer
     * \param arg Float to convert
     * \return Integer
     */
    static int FloatToInt(float arg)
    {
        return std::floor(arg + 0.5);
    }
};