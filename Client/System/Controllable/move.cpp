#include "move.hpp"
#include <sys/types.h>

#include "ProtocolParser.hpp"
#include "ServerPropertiesComponent.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"
#include "utils.hpp"

/**
 * \fn void moveMountedEntity(size_t entityId, registry& reg, float moveX, float moveY)
 * \brief Moves an entity that is mounted on another entity.
 * \param entityId The entity to move.
 * \param reg The registry to use.
 * \param moveX The amount to move in the x direction.
 * \param moveY The amount to move in the y direction.
 */
void moveMountedEntity(size_t entityId, registry& reg, float moveX, float moveY)
{
    auto& mountedArray = reg.get_components<MountedComponent>();
    for (int index = 0; index < mountedArray.size(); index++) {
        auto& mounted = mountedArray[index];
        if (mounted && mounted->getMountOnId() == entityId) {
            auto& transform_array = reg.get_components<TransformComponent>();
            auto& transform = transform_array[index];
            if (transform) {
                transform.value().move(moveX, moveY, 0);
            }
        }
    }
}

void updateMoveServer(size_t index, registry& reg, TransformComponent transform) {
    auto &serverproperties_array = reg.get_components<ServerPropertiesComponent>();
    if (serverproperties_array.size() < index)
        return;
    auto &serverProperties = serverproperties_array[index];
    if (serverProperties) {
        u_int64_t header = ProtocolBuilder::createPacket(ENTITY_MOVE, static_cast<int>(serverProperties->getId()), static_cast<int>(transform.getPosition().x), static_cast<int>(transform.getPosition().y), 0);
        serverProperties->BuildAndAddMethod(header, "");
    }
}

/**
 * \fn moveUp(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Move the entity up
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void moveUp(size_t index, registry& reg, AEngine& engine, ServerToken& token)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform = transform_array[index];
    if (transform && velocity) {
        transform.value().move(0, -(velocity.value().getVelocity()), 0);
        moveMountedEntity(index, reg, 0, -(velocity.value().getVelocity()));
        updateMoveServer(index, reg, transform.value());
    }
}

/**
 * \fn moveDown(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Move the entity down
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void moveDown(size_t index, registry& reg, AEngine& engine, ServerToken& token)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    if (transform && velocity) {
        transform.value().move(0, velocity.value().getVelocity(), 0);
        moveMountedEntity(index, reg, 0, (velocity.value().getVelocity()));
        updateMoveServer(index, reg, transform.value());
    }
}

/**
 * \fn moveLeft(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Move the entity left
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void moveLeft(size_t index, registry& reg, AEngine& engine, ServerToken& token)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    if (transform && velocity) {
        transform.value().move(-(velocity.value().getVelocity()), 0, 0);
        moveMountedEntity(index, reg, -(velocity.value().getVelocity()), 0);
        updateMoveServer(index, reg, transform.value());
    }
}

/**
 * \fn moveRight(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Move the entity right
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void moveRight(size_t index, registry& reg, AEngine& engine, ServerToken& token)
{
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity) {
        transform.value().move(velocity.value().getVelocity(), 0, 0);
        moveMountedEntity(index, reg, (velocity.value().getVelocity()), 0);
        updateMoveServer(index, reg, transform.value());
    }
}

/**
 * \fn void PlayerFire(size_t index, registry& reg, AEngine& engine, ServerToken& token)
 * \brief Make the player fire
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 * \param token The token
 */
void PlayerFire(
    size_t index, registry& reg, AEngine& engine, ServerToken& token)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& collide_array = reg.get_components<CollideComponent>();
    auto& clock_array = reg.get_components<ClocksComponent>();
    auto& data_array = reg.get_components<DataComponent>();
    if (index < clock_array.size() && index < data_array.size()) {
        auto& clocks = clock_array[index];
        auto& data = data_array[index];
        if (clocks && data) {
            if (data.value().getValue<bool>("reloaded")) {
                data.value().setValue<bool>("reloaded", false);
                clocks.value().getClock("reloadTime").reset();
            } else {
                return;
            }
        } else {
            return;
        }
    } else {
        return;
    }
    if (collide_array.size() > index && transform_array.size() > index) {
        auto& transform = transform_array[index];
        auto pos = transform->getPosition();
        auto& collide = collide_array[index];
        if (collide) {
            auto box = collide.value().getCollideBox();
            pos.x += (box.width / 2);
            pos.y += (box.height / 2);
        }
        createEntity(
            reg, BASIC_BULLET, {pos.x, pos.y, pos.z - 1}, -1, "PlayerOrigin", "");
        engine.getAudio().playSound("shootPlayer");
    }
}

/**
 * \fn void EnemyFire(size_t index, registry& reg, AEngine& engine)
 * \brief Make the enemy fire
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void EnemyFire(size_t index, registry& reg, AEngine& engine)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& collide_array = reg.get_components<CollideComponent>();
    auto& clock_array = reg.get_components<ClocksComponent>();
    auto& data_array = reg.get_components<DataComponent>();
    if (index < clock_array.size() && index < data_array.size()) {
        auto& clocks = clock_array[index];
        auto& data = data_array[index];
        if (clocks && data) {
            if (data.value().getValue<bool>("reloaded")) {
                data.value().setValue<bool>("reloaded", false);
                clocks.value().getClock("reloadTime").reset();
            } else {
                return;
            }
        } else {
            return;
        }
    } else {
        return;
    }
    if (collide_array.size() > index && transform_array.size() > index) {
        auto& transform = transform_array[index];
        auto pos = transform->getPosition();
        auto& collide = collide_array[index];
        if (collide) {
            auto box = collide.value().getCollideBox();
            pos.x += (box.width / 2);
            pos.y += (box.height / 2);
        }
        createEntity(
            reg, ENEMY_BULLET, {pos.x, pos.y, pos.z - 1}, -1, "PlayerOrigin", "");
        engine.getAudio().playSound("shootEnemy");
    }
}