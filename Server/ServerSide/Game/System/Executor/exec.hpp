#pragma once
#include "CollideComponent.hpp"
#include "DataComponent.hpp"
#include "Registry.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"

void moveLeftFirstPara(size_t index, registry& reg, ASocket&);
void moveLeftSecondPara(size_t index, registry& reg, ASocket&);
void destroyOutsideEntity(size_t index, registry& reg, ASocket&);
void execMoveRight(size_t index, registry& reg, ASocket&);
void updateReload(size_t index, registry& reg, ASocket&);
void fireEnemyBullet(size_t index, registry& reg, ASocket&);
void PlayerFire(size_t index, registry& reg, ASocket&);