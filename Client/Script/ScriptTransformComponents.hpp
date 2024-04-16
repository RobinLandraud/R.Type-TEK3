#pragma once

#include "TransformComponent.hpp"

/**
 * \class ScriptTransformComponent
 * \brief A class that allows a script to modify the transform component of an entity
 */
class ScriptTransformComponents
{
  public:
  /**
     * \fn ScriptTransformComponents(registry& reg): reg(reg)
     * \brief The constructor of the class
     * \param reg The registry
     */
    ScriptTransformComponents(registry& reg)
        : reg(reg){};
    ~ScriptTransformComponents() = default; /*!< Default destructor */

    /**
     * \fn void add(size_t ent_id)
     * \brief Add a script transform component to an entity
     * \param ent_id The entity id
     */
    void add(size_t ent_id)
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<TransformComponent>(
            entity.value(), TransformComponent());
    }

    /**
     * \fn size_t size()
     * \brief Get the number of script transform components
     * \return The number of script transform components
     */
    size_t size()
    {
        return reg.get_components<TransformComponent>().size();
    }

    /**
     * \fn TransformComponent& at(size_t index)
     * \brief Get a script transform component at a given index
     * \param index The index
     * \return The script transform component
     */
    TransformComponent& at(size_t index)
    {
        return reg.get_components<TransformComponent>()[index].value();
    }

    /**
     * \fn bool exists(size_t index)
     * \brief Check if a script transform component exists at a given index
     * \param index The index
     * \return True if the script transform component exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<TransformComponent>().exists(index);
    }

    /**
     * \fn void setPositionAt(size_t index, float posX, float posY, float posZ)
     * \brief Set the position of a script transform component at a given index
     * \param index The index
     * \param posX The x position
     * \param posY The y position
     * \param posZ The z position
     */
    void setPositionAt(size_t index, float posX, float posY, float posZ)
    {
        if (reg.get_components<TransformComponent>().exists(index)) {
            reg.get_components<TransformComponent>()[index].value().setPosition(
                posX, posY, posZ);
        }
    }

    /**
     * \fn void moveAt(size_t index, float x, float y, float z)
     * \brief Move a script transform component at a given index
     * \param index The index
     * \param x The x value
     * \param y The y value
     * \param z The z value
     */
    void moveAt(size_t index, float x, float y, float z)
    {
        if (reg.get_components<TransformComponent>().exists(index)) {
            reg.get_components<TransformComponent>()[index].value().move(
                x, y, z);
        }
    }

    /**
     * \fn void setRotationAt(size_t index, float rotation)
     * \brief Set the rotation of a script transform component at a given index
     * \param index The index
     * \param rotation The rotation
     */
    void setRotationAt(size_t index, float rotation)
    {
        if (reg.get_components<TransformComponent>().exists(index)) {
            reg.get_components<TransformComponent>()[index].value().setRotation(
                rotation);
        }
    }

    /**
     * \fn void setSizeAt(size_t index, float height, float width)
     * \brief Set the size of a script transform component at a given index
     * \param index The index
     * \param height The height
     * \param width The width
     */
    void setSizeAt(size_t index, float height, float width)
    {
        if (reg.get_components<TransformComponent>().exists(index)) {
            reg.get_components<TransformComponent>()[index].value().setSize(
                height, width);
        }
    }

    /**
     * \fn void rescaleAt(size_t index, float scale)
     * \brief Rescale a script transform component at a given index
     * \param index The index
     * \param scale The scale
     */
    void rescaleAt(size_t index, float scale)
    {
        if (reg.get_components<TransformComponent>().exists(index)) {
            reg.get_components<TransformComponent>()[index].value().rescale(
                scale);
        }
    }

    /**
     * \fn Position3D_t getPositionAt(size_t index) const
     * \brief Get the position of a script transform component at a given index
     * \param index The index
     * \return The position
     */
    Position3D_t getPositionAt(size_t index) const
    {
        if (reg.get_components<TransformComponent>().exists(index)) {
            return reg.get_components<TransformComponent>()[index]
                .value()
                .getPosition();
        }
        return {0, 0, 0};
    }

    /**
     * \fn float getRotationAt(size_t index) const
     * \brief Get the rotation of a script transform component at a given index
     * \param index The index
     * \return The rotation
     */
    float getRotationAt(size_t index) const
    {
        if (reg.get_components<TransformComponent>().exists(index)) {
            return reg.get_components<TransformComponent>()[index]
                .value()
                .getRotation();
        }
        return 0;
    }

    /**
     * \fn Size2D_t getSizeAt(size_t index) const
     * \brief Get the size of a script transform component at a given index
     * \param index The index
     * \return The size
     */
    Size2D_t getSizeAt(size_t index) const
    {
        if (reg.get_components<TransformComponent>().exists(index)) {
            return reg.get_components<TransformComponent>()[index]
                .value()
                .getSize();
        }
        return {0, 0};
    }

  private:
    registry& reg; /*!< The registry */
};