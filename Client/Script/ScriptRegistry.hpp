#pragma once

#include "ScriptBlinkComponents.hpp"
#include "ScriptClocksComponents.hpp"
#include "ScriptCollideComponents.hpp"
#include "ScriptDataComponents.hpp"
#include "ScriptDrawableComponents.hpp"
#include "ScriptSceneManagerComponents.hpp"
#include "ScriptServerPropertiesComponents.hpp"
#include "ScriptTransformComponents.hpp"
#include "ScriptVelocityComponents.hpp"

class ScriptRegistry
{
  public:
    /**
     * \fn ScriptRegistry(registry& reg): reg(reg), dataComponents(reg), blinkComponents(reg), clocksComponents(reg), drawableComponents(reg), sceneManagerComponents(reg), velocityComponents(reg), transformComponents(reg), serverPropertiesComponents(reg), collideComponents(reg)
     * \brief The constructor of the class
     * \param reg The registry
     */
    ScriptRegistry(registry& reg)
        : reg(reg)
        , dataComponents(reg)
        , blinkComponents(reg)
        , clocksComponents(reg)
        , drawableComponents(reg)
        , sceneManagerComponents(reg)
        , velocityComponents(reg)
        , transformComponents(reg)
        , serverPropertiesComponents(reg)
        , collideComponents(reg){};
    ~ScriptRegistry() = default; /*!< Default destructor */

    /**
     * \fn size_t spawn_entity()
     * \brief Spawn an entity
     * \return The entity id
     */
    size_t spawn_entity()
    {
        auto entity = reg.spawn_entity();
        return entity.id;
    }

    /**
     * \fn bool entity_exists(size_t id)
     * \brief Check if an entity exists
     * \param id The entity id
     * \return True if the entity exists, false otherwise
     */
    bool entity_exists(size_t id)
    {
        if (reg.entity_from_index(id)) {
            return true;
        }
        return false;
        ;
    }

    /**
     * \fn void kill_entity(size_t id)
     * \brief Kill an entity
     * \param id The entity id
     */
    void kill_entity(size_t id)
    {
        auto ent = reg.entity_from_index(id);
        if (ent) {
            reg.kill_entity(ent.value());
        }
    }

    /**
     * \fn ScriptDataComponents& getDataComponents()
     * \brief Get the data components
     * \return The data components
     */
    ScriptDataComponents& getDataComponents()
    {
        return dataComponents;
    }

    /**
     * \fn ScriptBlinkComponents& getBlinkComponents()
     * \brief Get the blink components
     * \return The blink components
     */
    ScriptBlinkComponents& getBlinkComponents()
    {
        return blinkComponents;
    }

    /**
     * \fn ScriptClocksComponents& getClocksComponents()
     * \brief Get the clocks components
     * \return The clocks components
     */
    ScriptClocksComponents& getClocksComponents()
    {
        return clocksComponents;
    }

    /**
     * \fn ScriptDrawableComponents& getDrawableComponents()
     * \brief Get the drawable components
     * \return The drawable components
     */
    ScriptDrawableComponents& getDrawableComponents()
    {
        return drawableComponents;
    }

    /**
     * \fn ScriptSceneManagerComponents& getSceneManagerComponents()
     * \brief Get the scene manager components
     * \return The scene manager components
     */
    ScriptSceneManagerComponents& getSceneManagerComponents()
    {
        return sceneManagerComponents;
    }

    /**
     * \fn ScriptVelocityComponents& getVelocityComponents()
     * \brief Get the velocity components
     * \return The velocity components
     */
    ScriptVelocityComponents& getVelocityComponents()
    {
        return velocityComponents;
    }

    /**
     * \fn ScriptTransformComponents& getTransformComponents()
     * \brief Get the transform components
     * \return The transform components
     */
    ScriptTransformComponents& getTransformComponents()
    {
        return transformComponents;
    }

    /**
     * \fn ScriptServerPropertiesComponents& getServerPropertiesComponents()
     * \brief Get the server properties components
     * \return The server properties components
     */
    ScriptServerPropertiesComponents& getServerPropertiesComponents()
    {
        return serverPropertiesComponents;
    }

    /**
     * \fn ScriptCollideComponents& getCollideComponents()
     * \brief Get the collide components
     * \return The collide components
     */
    ScriptCollideComponents& getCollideComponents()
    {
        return collideComponents;
    }

  private:
    registry& reg; /*!< The registry */
    ScriptDataComponents dataComponents; /*!< The data components */
    ScriptBlinkComponents blinkComponents; /*!< The blink components */
    ScriptClocksComponents clocksComponents; /*!< The clocks components */
    ScriptDrawableComponents drawableComponents; /*!< The drawable components */
    ScriptSceneManagerComponents sceneManagerComponents; /*!< The scene manager components */
    ScriptVelocityComponents velocityComponents; /*!< The velocity components */
    ScriptTransformComponents transformComponents; /*!< The transform components */
    ScriptServerPropertiesComponents serverPropertiesComponents; /*!< The server properties components */
    ScriptCollideComponents collideComponents; /*!< The collide components */
};