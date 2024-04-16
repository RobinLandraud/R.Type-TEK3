#include "ClocksComponent.hpp"
#include "system.hpp"

/**
 * \fn void clocksSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief System that make an entity blinks
 * \param reg : the registry
 * \param engine : the engine
 * \param serverToken : the server token
 */
void clocksSystem(registry& reg, AEngine& engine, ServerToken& serverToken) {
    auto& clock_array = reg.get_components<ClocksComponent>();
    for (auto& clocks : clock_array) {
        if (clocks) {
            clocks->updateClocks();
        }
    }
}