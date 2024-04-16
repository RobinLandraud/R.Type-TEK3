#include <sys/types.h>

#include <cstdint>
#include <iostream>
#include <vector>

#pragma once

/**
 * \enum Protocol
 * \brief All protocol responses
 */
enum Protocol {
    NONE = 0,
    CREATE = 100,
    CONNECT = 101,
    STAGE_CLEAR = 102,
    SERVER_CLOSE = 103,
    GAME_START = 104,
    GAME_END = 105,
    GET_HUB_LIST = 106,
    HUB_LIST = 107,
    HUB_STATUS = 108,
    HUB_SERVER_CREATE = 109,
    HUB_SUCCESFULLY_CREATE = 110,
    HUB_CONNECT_SUCCES = 111,
    ENTITY_SPAWN = 200,
    ENTITY_DEATH = 201,
    ENTITY_LIFE_UPDATE = 202,
    ENTITY_MOUNT_ENTITY = 203,
    ENTITY_MOVE = 204,
    PLAYER_FIRE = 300,
    PLAYER_LEAVE = 301,
    PLAYER_READY = 302,
    PLAYER_PAUSE = 303,
    PLAYER_SEND_MSG = 304,
    PLAYER_SWITCH_SKIN = 305,
    No_HUB_EXIST = 400
};

/**
 * \enum EntityType
 * \brief All entity types
 */
enum EntityType {
    GHOST,
    ENTITY_PLAYER,
    ENTITY_FAKE_PLAYER,
    BASIC_ENEMY,
    BASIC_BULLET,
    BASIC_WALL,
    TEXT_ENTITY
};

/**
 * \enum ElementType
 * \brief All element types
 */
enum ElementType { UNKNOWN = 0, SERVER = 1, ENTITY = 2, PLAYER = 3, ERROR = 4 };

/**
 * \struct ParsedPacket
 * \brief Parsed packet structure
 */
struct ParsedPacket {
    ElementType element;
    short MethodID;
    std::vector<int> arguments;
};

/**
 * \class ProtocolParser
 * \brief Protocol parser class
 */
class ProtocolParser
{
  public:
    ProtocolParser() = default; /*!< Default constructor */
    ~ProtocolParser() = default; /*!< Default destructor */

    /**
     * \fn static ParsedPacket getPacket(u_int64_t packet)
     * \brief Get packet from a u_int64_t
     * \param packet Packet to parse
     * \return Parsed packet
     */
    static ParsedPacket getPacket(u_int64_t packet)
    {
        if (isPackageOk(packet)) {
            return {getElementType(packet),
                getMethodID(packet),
                getArguments(packet)};
        }
        return {UNKNOWN, 0, {0, 0, 0, 0}};
    }

    /**
     * \fn static Protocol getProtocol(ElementType type, int method)
     * \brief Get protocol from a type and a method
     * \param type Type of the packet
     * \param method Method of the packet
     * \return Protocol
     */
    static Protocol getProtocol(ElementType type, int method)
    {
        if (method < 0 || method > 99) {
            return NONE;
        }
        int res = (static_cast<int>(type) * 100) + method;
        if (res > 99 && res < 1000)
            return (static_cast<Protocol>(res));
        return NONE;
    }

  private:
    /**
     * \fn static bool isPackageOk(u_int64_t packet)
     * \brief Check if a packet is valid
     * \param packet Packet to check
     * \return True if the packet is valid, false otherwise
     */
    static bool isPackageOk(u_int64_t packet)
    {
        int len = 1;
        while (packet >= 10) {
            packet /= 10;
            len++;
        }
        return (len == 19);
    }

    /**
     * \fn static ElementType getElementType(u_int64_t packet)
     * \brief Get the element type from a packet
     * \param packet Packet to parse
     * \return Element type
     */
    static ElementType getElementType(u_int64_t packet)
    {
        while (packet >= 10)
            packet = packet / 10;
        if (packet < SERVER || packet > ERROR)
            return UNKNOWN;
        return static_cast<ElementType>(packet);
    }

    /**
     * \fn static int getMethodID(u_int64_t packet)
     * \brief Get the method ID from a packet
     * \param packet Packet to parse
     * \return Method ID
     */
    static short getMethodID(u_int64_t packet)
    {
        for (int i = 0; i < 16; i++) {
            packet = packet / 10;
        }
        return static_cast<short>(packet % 100);
    }

    /**
     * \fn static std::vector<int> getArguments(u_int64_t packet)
     * \brief Get the arguments from a packet
     * \param packet Packet to parse
     * \return Arguments
     */
    static std::vector<int> getArguments(u_int64_t packet)
    {
        std::vector<int> res = {};
        for (int i = 0; i < 4; i++) {
            res.insert(res.begin(), static_cast<int>(packet % 10000));
            packet = packet / 10000;
        }
        return res;
    }
};