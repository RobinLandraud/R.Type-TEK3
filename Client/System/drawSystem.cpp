#include <map>
#include <ostream>

#include "system.hpp"

/**
 * \fn void drawSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
 * \brief Draw the system
 * \param reg The registry
 * \param engine The engine
 * \param serverToken The server token
 */
void drawSystem(registry& reg, AEngine& engine, ServerToken& serverToken)
{
    auto& drawable_array = reg.get_components<DrawableComponent>();
    auto& transform_array = reg.get_components<TransformComponent>();
    auto& blink_array = reg.get_components<BlinkComponent>();
    std::map<float, std::vector<size_t>> orderedDrawables;
    for (size_t i = 0; i < drawable_array.size(); i++) {
        if (drawable_array[i] && drawable_array[i].value().isEnable()) {
            if ((blink_array.size() <= i || !blink_array[i])
                || (blink_array[i] && blink_array[i].value().isBlink()))
                orderedDrawables[transform_array[i].value().getPosition().z]
                    .push_back(i);
        }
    }
    for (auto& pair : orderedDrawables) {
        for (auto& i : pair.second) {
            auto const& transform = transform_array[i];
            auto& drawable = drawable_array[i];
            if (transform) {
                auto position = transform.value().getPosition();
                switch (drawable.value().getType()) {
                    case SPRITE:
                        engine.getGraphics().drawSprite(
                            drawable.value().getName(), position.x, position.y);
                        break;
                    case CIRCLE:
                        engine.getGraphics().drawCircle(
                            drawable.value().getName(), position.x, position.y);
                        break;
                    case RECTANGLE:
                        engine.getGraphics().drawRectangle(
                            drawable.value().getName(), position.x, position.y);
                        break;
                    case TEXT:
                        engine.getGraphics().drawText(
                            drawable.value().getName(), position.x, position.y);
                        break;
                    case UNKNOWN_TYPE: break;
                };
            }
        }
    }
}