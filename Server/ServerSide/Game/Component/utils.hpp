#include <iostream>

#pragma once

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