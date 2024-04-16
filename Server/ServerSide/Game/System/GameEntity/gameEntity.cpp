#include "gameEntity.hpp"

#include "ClocksComponent.hpp"
#include "ProtocolParser.hpp"
#include "utils.hpp"

void createPlayer(registry& reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(128, 128));
    reg.add_component(entity, VelocityComponent(5));
    auto& clocks = reg.add_component(entity, ClocksComponent());
    clocks.value().addClock("reloadTime", 0.5);
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
    }
}

void createEnemy(registry& reg, Position3D_t pos, std::string IAtype)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(70, 30));
    reg.add_component(entity, VelocityComponent(5));
    auto& clocks = reg.add_component(entity, ClocksComponent());
    clocks.value().addClock("reloadTime", 0.5);
    sparse_array<DataComponent>::reference_type data =
        reg.add_component(entity, DataComponent());
    if (data) {
        data.value().addValue("life", 2);
        data.value().addValue("reloaded", true);
    }
    sparse_array<ExecComponent>::reference_type exec =
        reg.add_component(entity, ExecComponent());
    if (exec) {
        exec.value().addFunction(fireEnemyBullet);
    }
}

void createText(registry& reg, Position3D_t pos, const std::string& name)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
}

void createBullet(registry& reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, VelocityComponent(12));
    auto& clocks = reg.add_component(entity, ClocksComponent());
    sparse_array<ExecComponent>::reference_type exec =
        reg.add_component(entity, ExecComponent());
    if (exec) {
        exec.value().addFunction(execMoveRight);
        exec.value().addFunction(destroyOutsideEntity);
    }
}

void createWall(registry& reg, Position3D_t pos)
{
    const auto& entity = reg.spawn_entity();
    reg.add_component(entity, TransformComponent({pos.x, pos.y, pos.z}));
    reg.add_component(entity, CollideComponent(128, 128));
}

void createEntity(registry& reg,
    EntityType entType,
    Position3D_t pos,
    const std::string& name,
    const std::string& IAtype)
{
    switch (entType) {
        case ENTITY_PLAYER: createPlayer(reg, pos); break;
        case BASIC_ENEMY: createEnemy(reg, pos, IAtype); break;
        case BASIC_BULLET: createBullet(reg, pos); break;
        case BASIC_WALL: createWall(reg, pos); break;
        case TEXT_ENTITY: createText(reg, pos, name); break;
        default: break;
    }
}