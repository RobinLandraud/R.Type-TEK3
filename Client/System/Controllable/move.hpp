#pragma once
#include "ClocksComponent.hpp"
#include "CollideComponent.hpp"
#include "DataComponent.hpp"
#include "MountedComponent.hpp"
#include "Registry.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"
#include "gameEntity.hpp"

/**
 * \fn moveUp(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Move the entity up
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void moveUp(size_t index, registry& reg, AEngine& engine, ServerToken& token);

/**
 * \fn moveDown(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Move the entity down
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void moveDown(size_t index, registry& reg, AEngine& engine, ServerToken& token);

/**
 * \fn moveLeft(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Move the entity left
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void moveLeft(size_t index, registry& reg, AEngine& engine, ServerToken& token);

/**
 * \fn moveRight(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Move the entity right
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void moveRight(
    size_t index, registry& reg, AEngine& engine, ServerToken& token);

/**
 * \fn void PlayerFire(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Make the player fire
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void PlayerFire(
    size_t index, registry& reg, AEngine& engine, ServerToken& token);