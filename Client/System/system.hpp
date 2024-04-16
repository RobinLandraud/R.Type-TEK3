#pragma once

#include <iostream>

#include "AEngine.hpp"
#include "ASocket.hpp"
#include "BlinkComponent.hpp"
#include "ClocksComponent.hpp"
#include "CollideComponent.hpp"
#include "DataComponent.hpp"
#include "DrawableComponent.hpp"
#include "ExecComponent.hpp"
#include "InputComponent.hpp"
#include "KeyboardEventComponent.hpp"
#include "MouseEventComponent.hpp"
#include "Registry.hpp"
#include "SceneManager.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"
#include "button.hpp"
#include "exec.hpp"
#include "move.hpp"
#include "utils.hpp"

/**
 * \fn void drawSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Draw all the drawable component
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void drawSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void KeyboardEventSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Handle all the keyboard event
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void KeyboardEventSystem(
    registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void gameSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Handle all the game logic
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void gameSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void blinkSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Handle all the blink logic
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void blinkSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void execSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Handle all the exec logic
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void execSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void clocksSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Handle all the clocks logic
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void clocksSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void reloadSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Handle all the reload logic
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void reloadSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void MouseEventSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Handle all the mouse event
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void MouseEventSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void ServerSystem(registry& reg, AEngine& engine, ServerToken& serverToKen)
 * \brief Handle all the server logic
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void ServerSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void listen(registry &reg, AEngine &engine, ServerToken &serverToken, std::vector<Request> &requestList)
 * \brief Listen to the server
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 * \param requestList The request list
 */
void listen(registry &reg,
    AEngine &engine,
    ServerToken &serverToken,
    std::vector<Request> &requestList);

/**
 * \fn void inputSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);
 * \brief Handle all the input logic
 * \param reg The registry
 * \param engine The engine
 * \param serverToKen The server token
 */
void inputSystem(registry& reg, AEngine& engine, ServerToken& serverToKen);

/**
 * \fn void handleRequest(registry& reg, const ParsedPacket& header, const std::string& buff,
    size_t mainEntityIndex, const ServerToken& serverToken, int senderPort, AEngine& engine);
 * \brief Handle the request
 * \param reg The registry
 * \param header The header
 * \param buff The buffer
 * \param mainEntityIndex The main entity index
 * \param serverToken The server token
 * \param senderPort The sender port
 * \param engine The engine
 */
void handleRequest(registry& reg,
    const ParsedPacket& header,
    const std::string& buff,
    size_t mainEntityIndex,
    const ServerToken& serverToken,
    int senderPort,
    AEngine& engine);