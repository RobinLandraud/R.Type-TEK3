#include "gameEntity.hpp"

#include "CollideComponent.hpp"
#include "DataComponent.hpp"
#include "ProtocolParser.hpp"
#include "utils.hpp"

/**
 * \fn void createPlayer(registry& reg, Position3D_t pos, int serverId)
 * \brief Create a player
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createPlayer(registry& reg, Position3D_t pos, int serverId)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("playerSprite", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(128, 128));
    reg.add_component(entity, VelocityComponent(5));
    if (serverId != -1)
        reg.add_component(entity, ServerPropertiesComponent(serverId));
    auto& clocks = reg.add_component(entity, ClocksComponent());
    clocks.value().addClock("reloadTime", 0.5);
    sparse_array<KeyboardEventComponent>::reference_type controllable =
        reg.add_component(entity, KeyboardEventComponent());
    if (controllable) {
        controllable.value().addAction(Key::Z, moveUp);
        controllable.value().addAction(Key::Q, moveLeft);
        controllable.value().addAction(Key::S, moveDown);
        controllable.value().addAction(Key::D, moveRight);
        controllable.value().addAction(Key::Space, PlayerFire);
    }
    sparse_array<DataComponent>::reference_type data =
        reg.add_component(entity, DataComponent());
    if (data) {
        data.value().addValue("life", 10);
        data.value().addValue("reloaded", true);
    }
    sparse_array<ExecComponent>::reference_type exec =
        reg.add_component(entity, ExecComponent());
    if (exec) {
        exec.value().addFunction(updateReload);
        exec.value().addFunction(PlayerTakeDamage);
    }
}

/**
 * \fn void createFakePlayer(registry& reg, Position3D_t pos, int serverId)
 * \brief Create a fake player
 * \param reg The registry
 * \param pos The position of the fake player
 * \param serverId The server id of the fake player
 */
void createFakePlayer(registry& reg, Position3D_t pos, int serverId) {
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("playerSprite", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, VelocityComponent(5));
    if (serverId != -1)
        reg.add_component(entity, ServerPropertiesComponent(serverId));
}

/**
 * \fn void createEnemy(registry& reg, Position3D_t pos, int serverId)
 * \brief Create an enemy
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createEnemy(registry& reg, Position3D_t pos, int serverId, std::string IAtype)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("enemySprite", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(128, 128));
    reg.add_component(entity, VelocityComponent(4));
    if (serverId != -1)
        reg.add_component(entity, ServerPropertiesComponent(serverId));
    auto& clocks = reg.add_component(entity, ClocksComponent());
    clocks.value().addClock("reloadTime", 0.8);
    sparse_array<DataComponent>::reference_type data =
        reg.add_component(entity, DataComponent());
    if (data) {
        data.value().addValue("life", 2);
        data.value().addValue("reloaded", true);
        data.value().addValue<bool>("directionY", true);
        data.value().addValue<bool>("directionX", true);
    }
    sparse_array<ExecComponent>::reference_type exec =
        reg.add_component(entity, ExecComponent());
    if (exec) {
        if (IAtype == "basic")
            exec.value().addFunction(enemyMoveIA);
        else
            exec.value().addFunction(enemyMoveAdvancedIA);
        exec.value().addFunction(updateReload);
        exec.value().addFunction(EnemyFire);
        exec.value().addFunction(EnemyTakeDamage);
    }
}

/**
 * \fn void createText(registry& reg, Position3D_t pos, int serverId, const std::string& name)
 * \brief Create a text
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createText(
    registry& reg, Position3D_t pos, int serverId, const std::string& name)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent(name, TEXT));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    if (serverId != -1)
        reg.add_component(entity, ServerPropertiesComponent(serverId));
}

/**
 * \fn void createBullet(registry& reg, Position3D_t pos, int serverId)
 * \brief Create a bullet
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createBullet(registry& reg, Position3D_t pos, int serverId)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("bullet", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, VelocityComponent(12));
    reg.add_component(entity, CollideComponent(39, 11));
    if (serverId != -1)
        reg.add_component(entity, ServerPropertiesComponent(serverId));
    auto& data = reg.add_component(entity, DataComponent());
    if (data) {
        data.value().addValue<std::string>("type", "PlayerBullet");
        data.value().addValue<int>("damage", 1);
    }
    auto& clocks = reg.add_component(entity, ClocksComponent());
    sparse_array<ExecComponent>::reference_type exec =
        reg.add_component(entity, ExecComponent());
    if (exec) {
        exec.value().addFunction(execMoveRight);
        exec.value().addFunction(destroyOutsideEntity);
    }
}

/**
 * \fn void createEnemyBullet(registry& reg, Position3D_t pos, int serverId)
 * \brief Create an enemy bullet
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createEnemyBullet(registry& reg, Position3D_t pos, int serverId)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("bullet", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, VelocityComponent(12));
    reg.add_component(entity, CollideComponent(39, 11));
    if (serverId != -1)
        reg.add_component(entity, ServerPropertiesComponent(serverId));
    auto& data = reg.add_component(entity, DataComponent());
    if (data) {
        data.value().addValue<std::string>("type", "EnemyBullet");
        data.value().addValue<int>("damage", 1);
    }
    auto& clocks = reg.add_component(entity, ClocksComponent());
    sparse_array<ExecComponent>::reference_type exec =
        reg.add_component(entity, ExecComponent());
    if (exec) {
        exec.value().addFunction(execMoveLeft);
        exec.value().addFunction(destroyOutsideEntity);
    }
}

/**
 * \fn void createWall(registry& reg, Position3D_t pos, int serverId)
 * \brief Create a wall
 * \param reg The registry
 * \param pos The position of the player
 * \param serverId The server id of the player
 */
void createWall(registry& reg, Position3D_t pos, int serverId)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("wall", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(128, 128));
    if (serverId != -1)
        reg.add_component(entity, ServerPropertiesComponent(serverId));
    auto& button = reg.add_component(entity, MouseEventComponent());
    button->setOnClick(buttonClick);
    button->setOnRelease(sendMessage);
}

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
    const std::string& IAtype)
{
    switch (entType) {
        case ENTITY_PLAYER: createPlayer(reg, pos, serverId); break;
        case BASIC_ENEMY: createEnemy(reg, pos, serverId, IAtype); break;
        case BASIC_BULLET: createBullet(reg, pos, serverId); break;
        case BASIC_WALL: createWall(reg, pos, serverId); break;
        case TEXT_ENTITY: createText(reg, pos, serverId, name); break;
        case ENEMY_BULLET: createEnemyBullet(reg, pos, serverId); break;
        case ENTITY_FAKE_PLAYER: createFakePlayer(reg, pos, serverId); break;
        default: break;
    }
}

/**
 * \fn void createHostLobbyMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a host lobby menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createHostLobbyMenuBtn(registry& reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("menuHostBtn", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(150, 49));
    auto& button = reg.add_component(entity, MouseEventComponent());
    button->setOnClick(buttonClick);
    button->setOnRelease(hostLobby);
    auto const& hostText = reg.spawn_entity();
    reg.add_component(hostText, DrawableComponent("HostText", TEXT));
    reg.add_component(hostText, TransformComponent({pos.x + 10, pos.y + 10, pos.z + 1}));
}

/**
 * \fn void createJoinLobbyMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a join lobby menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createJoinLobbyMenuBtn(registry& reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("menuJoinBtn", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(150, 49));
    auto& button = reg.add_component(entity, MouseEventComponent());
    button->setOnClick(buttonClick);
    button->setOnRelease(joinLobbies);
    auto const& joinText = reg.spawn_entity();
    reg.add_component(joinText, DrawableComponent("JoinText", TEXT));
    reg.add_component(joinText, TransformComponent({pos.x + 10, pos.y + 10, pos.z + 1}));
}

/**
 * \fn void createSettingsMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a settings menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createSettingsMenuBtn(registry& reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("menuSettingsBtn", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(150, 49));
    auto& button = reg.add_component(entity, MouseEventComponent());
    button->setOnClick(buttonClick);
    button->setOnRelease(settings);
    auto const& settingsText = reg.spawn_entity();
    reg.add_component(settingsText, DrawableComponent("SettingsText", TEXT));
    reg.add_component(settingsText, TransformComponent({pos.x + 10, pos.y + 10, pos.z + 1}));
}

/**
 * \fn void createQuitMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a quit menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createQuitMenuBtn(registry& reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("menuQuitBtn", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(150, 49));
    auto& button = reg.add_component(entity, MouseEventComponent());
    button->setOnClick(buttonClick);
    button->setOnRelease(quit);
    auto const& quitText = reg.spawn_entity();
    reg.add_component(quitText, DrawableComponent("QuitText", TEXT));
    reg.add_component(quitText, TransformComponent({pos.x + 10, pos.y + 10, pos.z + 1}));
}

/**
 * \fn void createBackMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a back menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createBackMenuBtn(registry &reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("menuBackBtn", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(150, 49));
    auto& button = reg.add_component(entity, MouseEventComponent());
    button->setOnClick(buttonClick);
    button->setOnRelease(back);
    auto const& backText = reg.spawn_entity();
    reg.add_component(backText, DrawableComponent("BackText", TEXT));
    reg.add_component(backText, TransformComponent({pos.x + 10, pos.y + 10, pos.z + 1}));
}

/**
 * \fn void createLocalMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a local menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createLocalMenuBtn(registry &reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, DrawableComponent("menuLocalBtn", SPRITE));
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(150, 49));
    auto& button = reg.add_component(entity, MouseEventComponent());
    button->setOnClick(buttonClick);
    button->setOnRelease(local);
    auto const& localText = reg.spawn_entity();
    reg.add_component(localText, DrawableComponent("LocalText", TEXT));
    reg.add_component(localText, TransformComponent({pos.x + 10, pos.y + 10, pos.z + 1}));
}

/**
 * \fn void createMenuBtn(registry& reg, Position3D_t pos)
 * \brief Create a menu button
 * \param reg The registry
 * \param pos The position of the player
 */
void createMenuBtn(registry& reg, MenuBtnType btnType, Position3D_t pos)
{
    switch (btnType) {
        case HOST_LOBBY: createHostLobbyMenuBtn(reg, pos); break;
        case JOIN_LOBBY: createJoinLobbyMenuBtn(reg, pos); break;
        case LOCAL: createLocalMenuBtn(reg, pos); break;
        case SETTINGS: createSettingsMenuBtn(reg, pos); break;
        case QUIT: createQuitMenuBtn(reg, pos); break;
        case BACK: createBackMenuBtn(reg, pos); break;
        default: break;
    }
}