#include <cstddef>
#include <ostream>

#include "ASocket.hpp"
#include "DataComponent.hpp"
#include "Registry.hpp"
#include "move.hpp"
#include "system.hpp"

void accesMenu(size_t id, registry& reg)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        sceneManager->changeScene(MENU);
    }
}

void initStart(registry& reg, ASocket& socket)
{
    auto const& background = reg.spawn_entity();
    reg.add_component(background, TransformComponent());

    reg.add_system(gameSystem);
    reg.add_system(clocksSystem);
}

void initMenu(registry& reg, ASocket& socket)
{
}

void initLobby(registry& reg, ASocket& socket)
{
}

void initSettings(registry& reg, ASocket& socket)
{
    
}

void initGame(registry& reg, ASocket& socket, size_t mainEntityIndex)
{
    auto const& paraBackground2 = reg.spawn_entity();
    reg.add_component(paraBackground2, TransformComponent({-1920, 0, 1}));
    reg.add_component(paraBackground2, VelocityComponent(3));
    reg.add_component(paraBackground2, ClocksComponent(0.017));

    auto const& paraBackground1 = reg.spawn_entity();
    reg.add_component(paraBackground1, TransformComponent({0, 0, 1}));
    reg.add_component(paraBackground1, VelocityComponent(3));
    reg.add_component(paraBackground1, ClocksComponent(0.017));

    auto& mainData = reg.add_component(
        reg.getEntities()[mainEntityIndex].value(), DataComponent());
    mainData->addValue("level", 1);
    mainData->addValue("maxLevel", 10);
    mainData->addValue("gameProgress", 0);
    mainData->addValue("levelEnd", 20000);

    reg.add_system(gameSystem);
    reg.add_system(execSystem);
    reg.add_system(clocksSystem);
}

void initEnd(registry& reg, ASocket& socket)
{
}

void initStat(registry& reg, ASocket& socket)
{
}

void deleteAllComponents(registry& reg, size_t mainEntityIndex)
{
    for (auto& entity : reg.getEntities()) {
        if (entity && entity->id != mainEntityIndex) {
            reg.kill_entity(entity.value());
        }
    }
    reg.clearAllSystems();
}

void gameSystem(registry& reg, ASocket& socket)
{
    auto& scene_array = reg.get_components<SceneManager>();
    for (auto& sceneManager : scene_array) {
        if (sceneManager && sceneManager->isUpdated()) {
            size_t mainEntityIndex = sceneManager->getEntityPos();
            deleteAllComponents(reg, mainEntityIndex);
            sceneManager->setUpdate(false);
            switch (sceneManager->getCurrentScene()) {
                case START: initStart(reg, socket); break;
                case MENU: initMenu(reg, socket); break;
                case LOBBY: initLobby(reg, socket); break;
                case SETINGS: initSettings(reg, socket); break;
                case GAME: initGame(reg, socket, mainEntityIndex); break;
                case END: initEnd(reg, socket); break;
                case STAT: initStat(reg, socket); break;
            }
        }
    }
}