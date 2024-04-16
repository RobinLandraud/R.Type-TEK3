#include <functional>
#include <ostream>

#include "move.hpp"
#include "system.hpp"

/**
 * \fn void blinkSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief System that make an entity blinks
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void blinkSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& blink_array = reg.get_components<BlinkComponent>();
    auto& clock_array = reg.get_components<ClocksComponent>();
    for (size_t i = 0; i < blink_array.size(); i++) {
        if (clock_array.size() > i) {
            auto& clocks = clock_array[i];
            auto& blink = blink_array[i];
            if (blink && clocks) {
                if (clocks->getClock(blink->getClockName()).isTick()) {
                    blink_array[i]->addActualLoop();
                }
            }
        }
    }
}