#include <iostream>
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

/**
 * \enum DrawableType
 * \brief Enum for drawable type
 */
enum DrawableType {
    UNKNOWN_TYPE = 0, /*!< Unknown type */
    SPRITE = 1,       /*!< Sprite type */
    RECTANGLE,        /*!< Rectangle type */
    CIRCLE,           /*!< Circle type */
    TEXT              /*!< Text type */
};

/**
 * \struct CollideBox
 * \brief Struct for collide box
 */
struct CollideBox {
    float width;  /*!< Width of the collide box */
    float height; /*!< Height of the collide box */
};

/**
 * \struct Position2D_t
 * \brief Struct for 2D position
 */
struct Position2D_t {
    float x; /*!< X position */
    float y; /*!< Y position */
};

/**
 * \struct Position3D_t
 * \brief Struct for 3D position
 */
struct Position3D_t {
    float x; /*!< X position */
    float y; /*!< Y position */
    float z; /*!< Z position */
};

/**
 * \struct Size2D_t
 * \brief Struct for 2D size
 */
struct Size2D_t {
    float width = 1;  /*!< Width of the size */
    float height = 1; /*!< Height of the size */
};