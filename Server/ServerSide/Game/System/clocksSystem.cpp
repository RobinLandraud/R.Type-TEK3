#include "ASocket.hpp"
#include "ClocksComponent.hpp"
#include "system.hpp"

void clocksSystem(registry& reg, ASocket&)
{
    auto& clock_array = reg.get_components<ClocksComponent>();
    for (auto& clocks : clock_array) {
        if (clocks) {
            clocks->updateClocks();
        }
    }
}