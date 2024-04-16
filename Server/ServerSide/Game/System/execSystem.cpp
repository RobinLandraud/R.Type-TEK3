#include <functional>

#include "ASocket.hpp"
#include "move.hpp"
#include "system.hpp"

void execSystem(registry& reg, ASocket& socket)
{
    auto& exec_array = reg.get_components<ExecComponent>();
    auto& clock_array = reg.get_components<ClocksComponent>();
    bool clockOK = true;
    for (size_t i = 0; i < exec_array.size(); i++) {
        auto& exec = exec_array[i];
        if (exec) {
            for (const std::function<void(size_t, registry&, ASocket&)>& func :
                exec.value().getFunctions()) {
                func(i, reg, socket);
            }
        }
    }
}