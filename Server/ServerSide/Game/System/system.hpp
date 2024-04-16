#pragma once

#include <iostream>

#include "ASocket.hpp"
#include "ClocksComponent.hpp"
#include "ExecComponent.hpp"
#include "Registry.hpp"
#include "SceneManager.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"
#include "move.hpp"
#include "utils.hpp"

/**
 * \fn void gameSystem(registry& reg, ASocket& socket); 
 * \brief Handle all the game logic
 * \param reg The registry
 * \param socket The socket
 */
void gameSystem(registry& reg, ASocket& socket);

/**
 * \fn void execSystem(registry& reg, ASocket& socket);
 * \brief Handle all the exec logic
 * \param reg The registry
 * \param socket The socket
 */
void execSystem(registry& reg, ASocket& socket);

/**
 * \fn void clocksSystem(registry& reg, ASocket& socket);
 * \brief Handle all the clocks logic
 * \param reg The registry
 * \param socket The socket
 */
void clocksSystem(registry& reg, ASocket& socket);

/**
 * \fn void progressSystem(registry& reg, ASocket& socket);
 * \brief Handle all the progress logic
 * \param reg The registry
 * \param socket The socket
 */
void progressSystem(registry& reg, ASocket& socket);