#include "exec.hpp"

#include <ostream>
#include <string>

#include "ClocksComponent.hpp"
#include "utils.hpp"

/**
 * \fn bool needFrameUpdate(size_t index, registry& reg)
 * \brief Check if the entity at index needs to be updated
 * \param index The index of the entity to check
 * \param reg The registry to check
 * \return True if the entity needs to be updated, false otherwise
 */
bool needFrameUpdate(size_t index, registry& reg)
{
    auto& clock_array = reg.get_components<ClocksComponent>();
    if (index < clock_array.size()) {
        auto& clocks = clock_array[index];
        if (clocks) {
            if (!clocks.value().getDefaultClock().isTick())
                return false;
        }
    }
    return true;
}

/**
 * \fn void moveLeftFirstPara(size_t index, registry& reg, AEngine& engine)
 * \brief Moves the first parallax entity left
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void moveLeftFirstPara(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity) {
        if (transform.value().getPosition().x < -1920) {
            transform.value().setPosition(
                0, transform.value().getPosition().y, 0);
        }
        transform.value().move(-velocity.value().getVelocity(), 0, 0);
    }
}

/**
 * \fn void moveLeftSecondPara(size_t index, registry& reg, AEngine& engine)
 * \brief Moves the second parallax entity left
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void moveLeftSecondPara(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity) {
        if (transform.value().getPosition().x < 0) {
            transform.value().setPosition(
                1920, transform.value().getPosition().y, 0);
        }
        transform.value().move(-velocity.value().getVelocity(), 0, 0);
    }
}

/**
 * \fn void destroyOutsideEntity(size_t index, registry& reg, AEngine& engine)
 * \brief Destroys an entity that is outside the screen
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void destroyOutsideEntity(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& collision_array = reg.get_components<CollideComponent>();
    if (transform_array.size() <= 0)
        return;
    auto& transform = transform_array[index];
    if (collision_array.size() > 0) {
        auto& collision = collision_array[index];
        if (transform && collision) {
            if (transform.value().getPosition().x
                        + collision.value().getCollideBox().width
                    < 0
                || transform.value().getPosition().x > 1920
                || transform.value().getPosition().y
                           + collision.value().getCollideBox().height
                       < 0
                || transform.value().getPosition().y > 1080) {
                auto ent = reg.entity_from_index(index);
                if (ent) {
                    reg.kill_entity(ent.value());
                }
            }
            return;
        }
    }
    if (transform.value().getPosition().x < 0
        || transform.value().getPosition().x > 1920
        || transform.value().getPosition().y < 0
        || transform.value().getPosition().y > 1080) {
        auto ent = reg.entity_from_index(index);
        if (ent) {
            reg.kill_entity(ent.value());
        }
    }
}

/**
 * \fn void execMoveRight(size_t index, registry& reg, AEngine& engine)
 * \brief Moves an entity right
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void execMoveRight(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity)
        transform.value().move(velocity.value().getVelocity(), 0, 0);
}

/**
 * \fn void execMoveLeft(size_t index, registry& reg, AEngine& engine)
 * \brief Moves an entity left
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void execMoveLeft(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity)
        transform.value().move(-velocity.value().getVelocity(), 0, 0);
}

/**
 * \fn void enemyMoveIA(size_t index, registry& reg, AEngine& engine)
 * \brief Moves an enemy
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void enemyMoveIA(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[index];
    auto& collide_array = reg.get_components<CollideComponent>();
    auto& collide = collide_array[index];
    if (transform && velocity && data && collide) {
        if (transform.value().getPosition().y +
            collide.value().getDeltaPos().y < 0) {
            data.value().setValue<bool>("directionY", true);
        } else if (transform.value().getPosition().y +
            collide.value().getCollideBox().height +
            collide.value().getDeltaPos().y > 1080) {
            data.value().setValue<bool>("directionY", false);
        }
        if (data.value().getValue<bool>("directionY")) {
            transform.value().move(0, velocity.value().getVelocity(), 0);
        } else {
            transform.value().move(0, -velocity.value().getVelocity(), 0);
        }
    }
}

void enemyMoveAdvancedIA(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[index];
    auto& collide_array = reg.get_components<CollideComponent>();
    auto& collide = collide_array[index];
    if (transform && velocity && data && collide) {
        if (transform.value().getPosition().y +
            collide.value().getDeltaPos().y < 0) {
            data.value().setValue<bool>("directionY", true);
        } else if (transform.value().getPosition().y +
            collide.value().getCollideBox().height +
            collide.value().getDeltaPos().y > 1080) {
            data.value().setValue<bool>("directionY", false);
        }
        if (transform.value().getPosition().x +
            collide.value().getDeltaPos().x < 1600) {
            data.value().setValue<bool>("directionX", true);
        } else if (transform.value().getPosition().x +
            collide.value().getCollideBox().width +
            collide.value().getDeltaPos().x > 1920) {
            data.value().setValue<bool>("directionX", false);
        }
        if (data.value().getValue<bool>("directionY")) {
            transform.value().move(0, velocity.value().getVelocity(), 0);
        } else {
            transform.value().move(0, -velocity.value().getVelocity(), 0);
        }
        if (data.value().getValue<bool>("directionX")) {
            transform.value().move(velocity.value().getVelocity(), 0, 0);
        } else {
            transform.value().move(-velocity.value().getVelocity(), 0, 0);
        }
    }
}

std::string incrementScore(std::string string)
{
    int pos = string.find_first_of(":");
    if (pos == std::string::npos)
        return string;
    std::string str = string.substr(pos + 2);
    if (!str.empty() && str.find_first_not_of("0123456789") == std::string::npos) {
        int score = std::stoi(str);
        score++;
        std::string new_str = "Score : " + std::to_string(score);
        return new_str;
    }
    return string;
}

/**
 * \fn void EnemyTakeDamage(size_t index, registry& reg, AEngine& engine)
 * \brief Makes an enemy take damage
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void EnemyTakeDamage(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[index];
    auto& collide_array = reg.get_components<CollideComponent>();
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& my_collide = collide_array[index].value();
    auto& my_transform = transform_array[index].value();
    for (size_t i = 0; i < data_array.size() && i < collide_array.size() && i < transform_array.size(); i++) {
        if (i == index)
            continue;
        auto& otherData = data_array[i];
        auto& collide = collide_array[i];
        auto& transform = transform_array[i];
        if (collide && transform && otherData) {
            if (otherData.value().hasValue<std::string>("type")) {
                auto type = otherData.value().getValue<std::string>("type");
                if (type == "PlayerBullet") {
                    auto damage = otherData.value().getValue<int>("damage");
                    if (my_collide.isCollide(my_transform, collide.value(), transform.value())) {
                        auto newLife  = data.value().getValue<int>("life") - damage;
                        data.value().setValue<int>("life", data.value().getValue<int>("life") - damage);
                        auto bullet = reg.entity_from_index(i);
                        auto enemy = reg.entity_from_index(index);
                        if (bullet)
                            reg.kill_entity(bullet.value());
                        if (newLife <= 0) {
                            reg.kill_entity(enemy.value());
                            engine.getGraphics().changeText("score", incrementScore(engine.getGraphics().getText("score")));
                        }
                    }
                }
            }
        }
    }
}

/**
 * \fn void PlayerTakeDamage(size_t index, registry& reg, AEngine& engine)
 * \brief Makes the player take damage
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void PlayerTakeDamage(size_t index, registry& reg, AEngine &engine)
{
    if (!needFrameUpdate(index, reg))
        return;
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[index];
    auto& collide_array = reg.get_components<CollideComponent>();
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& my_collide = collide_array[index].value();
    auto& my_transform = transform_array[index].value();
    for (size_t i = 0; i < data_array.size() && i < collide_array.size() && i < transform_array.size(); i++) {
        if (i == index)
            continue;
        auto& otherData = data_array[i];
        auto& collide = collide_array[i];
        auto& transform = transform_array[i];
        if (collide && transform && otherData) {
            if (otherData.value().hasValue<std::string>("type")) {
                auto type = otherData.value().getValue<std::string>("type");
                if (type == "EnemyBullet") { 
                    auto damage = otherData.value().getValue<int>("damage");
                    if (my_collide.isCollide(my_transform, collide.value(), transform.value())) {
                        auto newLife  = data.value().getValue<int>("life") - damage;
                        data.value().setValue<int>("life", data.value().getValue<int>("life") - damage);
                        auto bullet = reg.entity_from_index(i);
                        auto enemy = reg.entity_from_index(index);
                        if (bullet)
                            reg.kill_entity(bullet.value());
                        if (newLife <= 0)
                            reg.kill_entity(enemy.value());
                    }
                }
            }
        }
    }
}

/**
 * \fn void updateReload(size_t index, registry& reg, AEngine& engine)
 * \brief Updates the reload of a weapon
 * \param index The index of the entity
 * \param reg The registry
 * \param engine The engine
 */
void updateReload(size_t index, registry& reg, AEngine &engine)
{
    auto& clock_array = reg.get_components<ClocksComponent>();
    auto& data_array = reg.get_components<DataComponent>();
    if (index < clock_array.size() && index < data_array.size()) {
        auto& data = data_array[index];
        auto& clocks = clock_array[index];
        if (clocks) {
            if (clocks.value().getClock("reloadTime").isTick() && data) {
                data.value().setValue("reloaded", true);
            }
        }
    }
}