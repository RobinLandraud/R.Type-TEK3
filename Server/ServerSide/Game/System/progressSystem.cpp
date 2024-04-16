#include <cstddef>

#include "DataComponent.hpp"
#include "system.hpp"

#define BlockFrequency 2000
#define EntityFrequency 1500

void spawnNewBlock()
{
}

void progressSystem(registry& reg, ASocket& socket)
{
    auto& data_array = reg.get_components<DataComponent>();
    auto& scene_array = reg.get_components<SceneManager>();
    size_t mainEntityIndex = -1;
    for (auto& sceneManager : scene_array) {
        if (sceneManager) {
            mainEntityIndex = sceneManager.value().getEntityPos();
            break;
        }
    }
    if (mainEntityIndex == -1) {
        std::cout << "progress system error stoping system" << std::endl;
        return;
    }
    auto& data = data_array[mainEntityIndex];
    if (data) {
        int levelProgress = data.value().getValue<int>("gameProgress");
        if (levelProgress % BlockFrequency == 0) {
            spawnNewBlock();
        }
    }
}