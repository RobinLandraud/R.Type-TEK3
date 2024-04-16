#pragma once

#include "VelocityComponent.hpp"

/**
 * \class ScriptVelocityComponents
 * \brief The class for the script velocity components
 */
class ScriptVelocityComponents
{
  public:
    /**
     * \fn ScriptVelocityComponents(registry& reg): reg(reg)
     * \brief The constructor of the class
     * \param reg The registry
     */
    ScriptVelocityComponents(registry& reg)
        : reg(reg){};
    ~ScriptVelocityComponents() = default; /*!< Default destructor */

    /**
     * \fn void add(size_t ent_id)
     * \brief Add a script velocity component to an entity
     * \param ent_id The entity id
     */
    void add(size_t ent_id)
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<VelocityComponent>(
            entity.value(), VelocityComponent());
    }

    /**
     * \fn size_t size()
     * \brief Get the number of script velocity components
     * \return The number of script velocity components
     */
    size_t size()
    {
        return reg.get_components<VelocityComponent>().size();
    }

    /**
     * \fn VelocityComponent& at(size_t index)
     * \brief Get a script velocity component at a given index
     * \param index The index
     * \return The script velocity component
     */
    VelocityComponent& at(size_t index)
    {
        return reg.get_components<VelocityComponent>()[index].value();
    }

    /**
     * \fn bool exists(size_t index)
     * \brief Check if a script velocity component exists at a given index
     * \param index The index
     * \return True if the script velocity component exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<VelocityComponent>().exists(index);
    }

    /**
     * \fn void setVelocityAt(size_t index, float velocity)
     * \brief Set the velocity of a script velocity component at a given index
     * \param index The index of the script velocity component
     * \param velocity The velocity
     */
    void setVelocityAt(size_t index, float velocity)
    {
        if (reg.get_components<VelocityComponent>().exists(index)) {
            reg.get_components<VelocityComponent>()[index].value().setVelocity(
                velocity);
        }
    }

    /**
     * \fn float getVelocityAt(size_t index)
     * \brief Get the velocity of a script velocity component at a given index
     * \param index The index of the script velocity component
     * \return The velocity
     */
    float getVelocityAt(size_t index) const
    {
        if (reg.get_components<VelocityComponent>().exists(index)) {
            return reg.get_components<VelocityComponent>()[index]
                .value()
                .getVelocity();
        }
        return 0;
    }

  private:
    registry& reg; /*!< The registry */
};