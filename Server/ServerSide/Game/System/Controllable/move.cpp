#include "move.hpp"

#include "utils.hpp"

void moveUp(size_t index, registry& reg, ASocket& socket)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform = transform_array[index];
    if (transform && velocity)
        transform.value().move(0, -(velocity.value().getVelocity()), 0);
}

void moveDown(size_t index, registry& reg, ASocket& socket)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    if (transform && velocity)
        transform.value().move(0, velocity.value().getVelocity(), 0);
}

void moveLeft(size_t index, registry& reg, ASocket& socket)
{
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    if (transform && velocity)
        transform.value().move(-(velocity.value().getVelocity()), 0, 0);
}

void moveRight(size_t index, registry& reg, ASocket& socket)
{
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity)
        transform.value().move(velocity.value().getVelocity(), 0, 0);
}

void BulletMove(size_t index, registry& reg, ASocket& socket)
{
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity)
        transform.value().move(velocity.value().getVelocity(), 0, 0);
}

void moveLeftFirstPara(size_t index, registry& reg, ASocket& socket)
{
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity) {
        if (transform.value().getPosition().x > 1920) {
            transform.value().setPosition(
                0, transform.value().getPosition().y, 0);
        }
        transform.value().move(velocity.value().getVelocity(), 0, 0);
    }
}

void moveLeftSecondPara(size_t index, registry& reg, ASocket& socket)
{
    auto& velocity_array = reg.get_components<VelocityComponent>();
    auto& velocity = velocity_array[index];
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& transform = transform_array[index];
    if (transform && velocity) {
        if (transform.value().getPosition().x > 0) {
            transform.value().setPosition(
                -1920, transform.value().getPosition().y, 0);
        }
        transform.value().move(velocity.value().getVelocity(), 0, 0);
    }
}