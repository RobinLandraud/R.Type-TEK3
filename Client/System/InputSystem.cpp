#include "system.hpp"

/**
 * \fn void inputSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief The input system
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void inputSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& input_array = reg.get_components<InputComponent>();
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& collide_array = reg.get_components<CollideComponent>();
    for (size_t i = 0; i < input_array.size(); i++) {
        if (transform_array.size() > i && collide_array.size() > i) {
            auto& input = input_array[i];
            auto& transform = transform_array[i];
            auto& collide = collide_array[i];
            if (input && transform && collide) {
                input->update(engine, transform.value(), collide.value());
            }
        }
    }
}