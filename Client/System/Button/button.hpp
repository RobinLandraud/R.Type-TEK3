#pragma once
#include "ProtocolBuilder.hpp"
#include "Registry.hpp"
#include "SceneManager.hpp"
#include "TransformComponent.hpp"

/**
 * \fn void accesSettings(registry& reg, AEngine& engine)
 * \brief Function to access the settings
 * \param reg The registry
 * \param engine The engine
 */
void accesSettings(registry& reg, AEngine& engine);

/**
 * \fn void accesEnd(registry& reg, AEngine& engine)
 * \brief Function to access the end of the game
 * \param reg The registry
 * \param engine The engine
 */
void accesEnd(registry& reg, AEngine& engine);

/**
 * \fn void hostLobby(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to host a lobby
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void hostLobby(size_t, registry&, AEngine&, ServerToken& serverToken);

/**
 * \fn void joinLobby(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to join a lobby
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void joinLobby(size_t, registry&, AEngine&, ServerToken& serverToken);

/**
 * \fn void settings(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to access the settings
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void settings(size_t, registry&, AEngine&, ServerToken& serverToken);

/**
 * \fn void quit(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to quit the game
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void quit(size_t, registry&, AEngine&, ServerToken& serverToken);

/**
 * \fn void sendMessage(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to send a message
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void sendMessage(size_t, registry&, AEngine&, ServerToken& serverToken);

/**
 * \fn void buttonClick(size_t, registry&, AEngine&, ServerToken& serverToken)
 * \brief Function to click on a button
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void buttonClick(size_t, registry&, AEngine&, ServerToken& serverToken);

/**
 * \fn void switchReady(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to switch the ready state of a player
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void switchReady(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken);

/**
 * \fn void buttonDeny(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to deny a player
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void buttonDeny(
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken);

/**
 * \fn void joinLobbies(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to join a lobby
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void joinLobbies(
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken);

/**
 * \fn void back(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to go back to the main menu
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void back (
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken);

/**
 * \fn void local(size_t index, registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Function to play locally
 * \param index The index of the player
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void local (
    size_t index, registry& reg, AEngine& engine, ServerToken& serverToken);