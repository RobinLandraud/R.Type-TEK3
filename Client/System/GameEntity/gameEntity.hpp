#pragma once
#include <cstddef>
#include <ostream>

#include "AEngine.hpp"
#include "CollideComponent.hpp"
#include "DataComponent.hpp"
#include "DrawableComponent.hpp"
#include "ExecComponent.hpp"
#include "KeyboardEventComponent.hpp"
#include "MouseEventComponent.hpp"
#include "ProtocolParser.hpp"
#include "Registry.hpp"
#include "ServerPropertiesComponent.hpp"
#include "button.hpp"
#include "exec.hpp"
#include "move.hpp"
#include "utils.hpp"

/**
 * \enum MenuBtnType
 * \brief Enum for the different type of buttons in the menu
 */
enum MenuBtnType { HOST_LOBBY, JOIN_LOBBY, LOCAL, SETTINGS, QUIT, BACK };

/**
 * \fn void createPlayer(registry& reg, Position3D_t pos, int serverId)
 * \brief Create a player
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createPlayer(registry& reg, Position3D_t pos, int serverId);

/**
 * \fn void createEnemy(registry& reg, Position3D_t pos, int serverId)
 * \brief Create an enemy
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createEnemy(registry& reg, Position3D_t pos, int serverId);

/**
 * \fn void createBullet(registry& reg, Position3D_t pos, int serverId)
 * \brief Create a bullet
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createBullet(registry& reg, Position3D_t pos, int serverId);

/**
 * \fn void createWall(registry& reg, Position3D_t pos, int serverId)
 * \brief Create a wall
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createWall(registry& reg, Position3D_t pos, int serverId);

/**
 * \fn void createText(registry& reg, Position3D_t pos, int serverId, const std::string& name)
 * \brief Create a text
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createText(
    registry& reg, Position3D_t pos, int serverId, const std::string& name);

/**
 * \fn void createWall(registry& reg, Position3D_t pos)
 * \brief Create a wall
 * \param reg The registry
 * \param pos The position of the player
 */
void createWall(registry& reg, Position3D_t pos);

/**
 * \fn void createEntity(registry& reg, EntityType entType, Position3D_t pos, int serverId, const std::string& name)
 * \brief Create an entity
 * \param reg The registry
 * \param entType The type of the entity
 * \param pos The position of the entity
 * \param serverId The server id of the entity
 * \param name The name of the entity
 */
void createEntity(registry& reg,
    EntityType entType,
    Position3D_t pos,
    int serverId,
    const std::string& name,
    const std::string& IAtype);

/**
 * \fn void createHostLobbyMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a host lobby menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createHostLobbyMenuBtn(registry& reg, Position3D_t pos);

/**
 * \fn void createJoinLobbyMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a join lobby menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createJoinLobbyMenuBtn(registry& reg, Position3D_t pos);

/**
 * \fn void createSettingsMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a settings menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createSettingsMenuBtn(registry& reg, Position3D_t pos);

/**
 * \fn void createQuitMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a quit menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createQuitMenuBtn(registry& reg, Position3D_t pos);

/**
 * \fn void createLocalMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a local menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createLocalMenuBtn(registry& reg, Position3D_t pos);

/**
 * \fn void createMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createMenuBtn(registry& reg, MenuBtnType menuBtnType, Position3D_t pos);

/**
 * \fn void createBackMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a back menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createBackMenuBtn(registry &reg, Position3D_t pos);