#pragma once
#include "ASocket.hpp"
#include "Registry.hpp"
#include "TransformComponent.hpp"
#include "VelocityComponent.hpp"

void moveUp(size_t index, registry& reg, ASocket& socket);
void moveDown(size_t index, registry& reg, ASocket& socket);
void moveLeft(size_t index, registry& reg, ASocket& socket);
void moveLeftFirstPara(size_t index, registry& reg, ASocket& socket);
void moveLeftSecondPara(size_t index, registry& reg, ASocket& socket);
void moveRight(size_t index, registry& reg, ASocket& socket);
void BulletMove(size_t index, registry& reg, ASocket& socket);