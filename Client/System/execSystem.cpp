#include <functional>

#include "move.hpp"
#include "system.hpp"

/**
 * \fn void execSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Execute the system
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void execSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& exec_array = reg.get_components<ExecComponent>();
    auto& clock_array = reg.get_components<ClocksComponent>();
    bool clockOK = true;
    for (size_t i = 0; i < exec_array.size(); i++) {
        auto& exec = exec_array[i];
        if (exec) {
            for (const std::function<void(size_t, registry&, AEngine &)>& func :
                exec.value().getFunctions()) {
                func(i, reg, engine);
            }
        }
    }
}