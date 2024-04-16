#include <functional>

#include "ASocket.hpp"
#include "move.hpp"
#include "system.hpp"

/**
 * \fn void KeyboardEventSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief The keyboard event system
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void KeyboardEventSystem(
    registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& controllable_array = reg.get_components<KeyboardEventComponent>();
    auto& clock_array = reg.get_components<ClocksComponent>();
    bool clockOK = true;
    for (size_t i = 0; i < controllable_array.size(); i++) {
        auto& move = controllable_array[i];
        if (move) {
            clockOK = true;
            if (clock_array.size() > i) {
                auto& clocks = clock_array[i];
                if (clocks && !clocks->getDefaultClock().isTick())
                    clockOK = false;
            }
            if (clockOK) {
                for (Key key : engine.getEvent().getKeysPressed()) {
                    for (const std::function<void(
                             size_t, registry&, AEngine&, ServerToken&)>& func :
                        move->getActionsByKey(key)) {
                        func(i, reg, engine, serverToken);
                    }
                }
            }
        }
    }
}