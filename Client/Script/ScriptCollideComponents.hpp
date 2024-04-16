#pragma once

#include "CollideComponent.hpp"
#include "TransformComponent.hpp"

/**
 * \class ScriptCollideComponent
 * \brief The script collide component
 */
class ScriptCollideComponents
{
  public:
    /**
     * \fn ScriptCollideComponents(registry& reg)
     * \brief The constructor
     * \param reg The registry
     */
    ScriptCollideComponents(registry& reg)
        : reg(reg){};
    ~ScriptCollideComponents() = default;   /*!< Default destructor */

    /**
     * \fn void add(size_t ent_id, float width, float height, float deltaX, float deltaY)
     * \brief Add a collide component to an entity
     * \param ent_id The entity id
     * \param width The width of the collide component
     * \param height The height of the collide component
     * \param deltaX The delta x of the collide component
     * \param deltaY The delta y of the collide component
     */
    void add(
        size_t ent_id, float width, float height, float deltaX, float deltaY)
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<CollideComponent>(
            entity.value(), CollideComponent(width, height, deltaX, deltaY));
    }

    /**
     * \fn size_t size()
     * \brief Get the number of collide components
     * \return The number of collide components
     */
    size_t size()
    {
        return reg.get_components<CollideComponent>().size();
    }

    /**
     * \fn CollideComponent& at(size_t index)
     * \brief Get a collide component
     * \param index The index of the collide component
     * \return The collide component
     */
    CollideComponent& at(size_t index)
    {
        return reg.get_components<CollideComponent>()[index].value();
    }

    /**
     * \fn bool exists(size_t index)
     * \brief Check if a collide component exists
     * \param index The index of the collide component
     * \return true if the collide component exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<CollideComponent>().exists(index);
    }

    /**
     * \fn bool isEnableAt(size_t index)
     * \brief Check if a collide component is enable
     * \param index The index of the collide component
     * \return true if the collide component is enable, false otherwise
     */
    bool isEnableAt(size_t index)
    {
        if (reg.get_components<CollideComponent>().exists(index)) {
            return reg.get_components<CollideComponent>()[index]
                .value()
                .isEnable();
        }
        return false;
    }

    /**
     * \fn CollideBox getCollideBoxAt(size_t index)
     * \brief Get the collide box of a collide component
     * \param index The index of the collide component
     * \return CollideBox The collide box of the collide component
     */
    CollideBox getCollideBoxAt(size_t index)
    {
        if (reg.get_components<CollideComponent>().exists(index)) {
            return reg.get_components<CollideComponent>()[index]
                .value()
                .getCollideBox();
        }
        return CollideBox();
    }

    /**
     * \fn bool isCollideAt(size_t index, size_t other) 
     * \brief Check if a collide component is collide with another
     * \param index The index of the collide component
     * \param other The index of the other collide component
     * \return true if the collide component is collide with the other, false otherwise
     */
    bool isCollideAt(size_t index, size_t other)
    {
        if (reg.get_components<CollideComponent>().exists(index)
            && reg.get_components<CollideComponent>().exists(other)) {
            return reg.get_components<CollideComponent>()[index]
                .value()
                .isCollide(
                    reg.get_components<TransformComponent>()[index].value(),
                    reg.get_components<CollideComponent>()[other].value(),
                    reg.get_components<TransformComponent>()[other].value());
        }
        return false;
    }

  private:
    registry& reg;  /*!< The registry */
};