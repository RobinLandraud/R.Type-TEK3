#pragma once
#include "CollideComponent.hpp"
#include "DataComponent.hpp"
#include "Registry.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"

/**
 * \fn void moveLeftFirstPara(size_t index, registry& reg, AEngine& engine)
 * \brief Moves the first parallax entity left
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void moveLeftFirstPara(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void moveLeftSecondPara(size_t index, registry& reg, AEngine& engine)
 * \brief Moves the second parallax entity left
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void moveLeftSecondPara(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void destroyOutsideEntity(size_t index, registry& reg, AEngine& engine)
 * \brief Destroys an entity that is outside the screen
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void destroyOutsideEntity(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void execMoveRight(size_t index, registry& reg, AEngine& engine)
 * \brief Moves an entity right
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void execMoveRight(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void updateReload(size_t index, registry& reg, AEngine& engine)
 * \brief Updates the reload of a weapon
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void updateReload(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void execMoveLeft(size_t index, registry& reg, AEngine& engine)
 * \brief Moves an entity left
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void execMoveLeft(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void enemyMoveAdvancedIA(size_t index, registry& reg, AEngine& engine)
 * \brief Moves an enemy
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void enemyMoveAdvancedIA(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void enemyMoveIA(size_t index, registry& reg, AEngine& engine)
 * \brief Moves an enemy
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void enemyMoveIA(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void EnemyFire(size_t index, registry& reg, AEngine& engine)
 * \brief Makes an enemy fire
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void EnemyFire(size_t index, registry& reg, AEngine& engine);

/**
 * \fn void EnemyTakeDamage(size_t index, registry& reg, AEngine& engine)
 * \brief Makes an enemy take damage
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void EnemyTakeDamage(size_t index, registry& reg, AEngine &engine);

/**
 * \fn void PlayerTakeDamage(size_t index, registry& reg, AEngine& engine)
 * \brief Makes the player take damage
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void PlayerTakeDamage(size_t index, registry& reg, AEngine &engine);