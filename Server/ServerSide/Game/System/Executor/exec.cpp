#include "exec.hpp"

#include <ostream>

#include "ASocket.hpp"
#include "ClocksComponent.hpp"
#include "SceneManager.hpp"
#include "utils.hpp"

bool needFrameUpdate(size_t index, registry& reg, ASocket& socket)
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

void moveLeftFirstPara(size_t index, registry& reg, ASocket& socket)
{
    if (!needFrameUpdate(index, reg, socket))
        return;
    auto& scene_array = reg.get_components<SceneManager>();
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    auto& data_array = reg.get_components<DataComponent>();
    auto& data = data_array[index];
    if (transform && velocity) {
        if (transform.value().getPosition().x < -1920) {
            transform.value().setPosition(
                0, transform.value().getPosition().y, 0);
        }
        transform.value().move(-velocity.value().getVelocity(), 0, 0);
        for (auto& sceneManager : scene_array) {
            if (sceneManager) {
                size_t mainEntityIndex = sceneManager->getEntityPos();
                if (mainEntityIndex == index) {
                    auto& mainEntityData = data_array[mainEntityIndex];
                    if (mainEntityData) {
                        mainEntityData.value().setValue("gameProgress",
                            mainEntityData->getValue<int>("gameProgress") + 1);
                    }
                }
            }
        }
    }
}

void moveLeftSecondPara(size_t index, registry& reg, ASocket& socket)
{
    if (!needFrameUpdate(index, reg, socket))
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

void destroyOutsideEntity(size_t index, registry& reg, ASocket& socket)
{
    if (!needFrameUpdate(index, reg, socket))
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

void execMoveRight(size_t index, registry& reg, ASocket& socket)
{
    if (!needFrameUpdate(index, reg, socket))
        return;
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity)
        transform.value().move(velocity.value().getVelocity(), 0, 0);
}

void updateReload(size_t index, registry& reg, ASocket&)
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