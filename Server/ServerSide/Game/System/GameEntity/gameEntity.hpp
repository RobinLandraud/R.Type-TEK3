#pragma once
#include <cstddef>
#include <ostream>

#include "DataComponent.hpp"
#include "ExecComponent.hpp"
#include "ProtocolParser.hpp"
#include "Registry.hpp"
#include "exec.hpp"
#include "move.hpp"
#include "utils.hpp"

void createPlayer(registry& reg, Position3D_t pos, int serverId);
void createEnemy(registry& reg, Position3D_t pos, int serverId, std::string IAtype);
void createBullet(registry& reg, Position3D_t pos, int serverId);
void createWall(registry& reg, Position3D_t pos, int serverId);
void createText(
    registry& reg, Position3D_t pos, int serverId, const std::string& name);
void createEntity(registry& reg,
    EntityType entType,
    Position3D_t pos,
    int serverId,
    const std::string& name,
    const std::string& IAtype);