#include <functional>

#include "button.hpp"
#include "system.hpp"

/**
 * \fn void MouseEventSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief The mouse event system
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void MouseEventSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& button_array = reg.get_components<MouseEventComponent>();
    auto& collide_array = reg.get_components<CollideComponent>();
    auto& transform_array = reg.get_components<TransformComponent>();
    auto mouse = engine.getEvent().getMouse();
    for (size_t i = 0; i < button_array.size(); i++) {
        if (collide_array.size() > i && transform_array.size() > i) {
            auto& transform = transform_array[i];
            auto& button = button_array[i];
            auto& collide = collide_array[i];
            if (button && transform && collide) {
                auto box = collide->getCollideBox();
                auto pos = transform->getPosition();
                if (mouse.x >= pos.x && mouse.x <= pos.x + box.width
                    && mouse.y >= pos.y && mouse.y <= pos.y + box.height) {
                    for (auto event : engine.getEvent().getEvents()) {
                        if (event == MouseButtonPressed) {
                            button->onClick(i, reg, engine, serverToken);
                        } else if (event == MouseButtonReleased) {
                            button->onRelease(i, reg, engine, serverToken);
                        } else if (event == MouseMoved) {
                            button->onHover(i, reg, engine, serverToken);
                        }
                    }
                }
            }
        }
    }
}