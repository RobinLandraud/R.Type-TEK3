#include <sys/types.h>

#include <cstdint>
#include <iostream>
#include <vector>

#pragma once

/**
 * \enum Protocol
 * \brief The protocol
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
 * \brief The type of the entity
 */
enum EntityType {
    GHOST,
    ENTITY_PLAYER,
    ENTITY_FAKE_PLAYER,
    BASIC_ENEMY,
    BASIC_BULLET,
    BASIC_WALL,
    TEXT_ENTITY,
    ENEMY_BULLET
};

/**
 * \enum ElementType
 * \brief The type of the element
 */
enum ElementType { UNKNOWN = 0, SERVER = 1, ENTITY = 2, PLAYER = 3, ERROR = 4 };

/**
 * \struct ParsedPacket
 * \brief A struct that handle the parsed packet
 */
struct ParsedPacket {
    ElementType element;
    short MethodID;
    std::vector<int> arguments;
};

/**
 * \struct Request
 * \brief A struct that handle the request
 */
struct Request {
  ParsedPacket header;
  std::string strArgs;
  int senderPort;
  std::string senderIp;
};

/**
 * \class ProtocolParser
 * \brief A class that handle the protocol
 */
class ProtocolParser
{
  public:
    ProtocolParser() = default;     /*!< Default constructor */
    ~ProtocolParser() = default;    /*!< Default destructor */

    /**
     * \fn static ParsedPacket getPacket(u_int64_t packet)
     * \brief Get the packet
     * \param packet The packet
     * \return The parsed packet
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
     * \brief Get the protocol
     * \param type The type of the element
     * \param method The method id
     * \return The protocol
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
     * \brief Check if the packet is ok
     * \param packet The packet
     * \return true if the packet is ok, false otherwise
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
     * \brief Get the element type
     * \param packet The packet
     * \return The element type
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
     * \fn static short getMethodID(u_int64_t packet)
     * \brief Get the method id
     * \param packet The packet
     * \return The method id
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
     * \brief Get the arguments
     * \param packet The packet
     * \return The arguments
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