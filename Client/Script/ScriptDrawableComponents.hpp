#pragma once

#include "DrawableComponent.hpp"
#include "Registry.hpp"

/**
 * \class ScriptDrawableComponents
 * \brief The script drawable component
 */
class ScriptDrawableComponents
{
  public:
    /**
     * \fn ScriptDrawableComponents(registry& reg)
     * \brief The constructor
     * \param reg The registry
     */
    ScriptDrawableComponents(registry& reg)
        : reg(reg){};
    ~ScriptDrawableComponents() = default;  /*!< Default destructor */

    /**
     * \fn void add(size_t ent_id, std::string name, DrawableType type)
     * \brief Add a drawable component to an entity
     * \param ent_id The entity id
     * \param name The name of the drawable component
     * \param type The type of the drawable component
     */
    void add(size_t ent_id, std::string name, DrawableType type)
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<DrawableComponent>(
            entity.value(), DrawableComponent(name, type));
    }

    /**
     * \fn size_t size()
     * \brief Get the number of drawable components
     * \return The number of drawable components
     */
    size_t size()
    {
        return reg.get_components<DrawableComponent>().size();
    }

    /**
     * \fn DrawableComponent& at(size_t index)
     * \brief Get a drawable component
     * \param index The index of the drawable component
     * \return The drawable component
     */
    DrawableComponent& at(size_t index)
    {
        return reg.get_components<DrawableComponent>()[index].value();
    }

    /**
     * \fn bool exists(size_t index) 
     * \brief Check if a drawable component exists
     * \param index The index of the drawable component
     * \return true if the drawable component exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<DrawableComponent>().exists(index);
    }

    /**
     * \fn bool isEnableAt(size_t index)
     * \brief Check if a drawable component is enabled
     * \param index The index of the drawable component
     * \return true if the drawable component is enabled, false otherwise
     */
    bool isEnableAt(size_t index)
    {
        if (reg.get_components<DrawableComponent>().exists(index)) {
            return reg.get_components<DrawableComponent>()[index]
                .value()
                .isEnable();
        }
        return false;
    }

    /**
     * \fn void setEnableAt(size_t index)
     * \brief Set a drawable component as enabled
     * \param index The index of the drawable component
     */
    void setEnableAt(size_t index)
    {
        if (reg.get_components<DrawableComponent>().exists(index)) {
            reg.get_components<DrawableComponent>()[index].value().setEnable();
        }
    }

    /**
     * \fn void setDisableAt(size_t index)
     * \brief Set a drawable component as disabled
     * \param index The index of the drawable component
     */
    void setDisableAt(size_t index)
    {
        if (reg.get_components<DrawableComponent>().exists(index)) {
            reg.get_components<DrawableComponent>()[index].value().setDisable();
        }
    }

    /**
     * \fn std::string getNameAt(size_t index)
     * \brief Get the name of a drawable component
     * \param index The index of the drawable component
     * \return The name of the drawable component
     */
    std::string getNameAt(size_t index)
    {
        if (reg.get_components<DrawableComponent>().exists(index)) {
            return reg.get_components<DrawableComponent>()[index]
                .value()
                .getName();
        }
        return "";
    }

    /**
     * \fn DrawableType getTypeAt(size_t index)
     * \brief Get the type of a drawable component
     * \param index The index of the drawable component
     * \return DrawableType The type of the drawable component
     */
    DrawableType getTypeAt(size_t index)
    {
        if (reg.get_components<DrawableComponent>().exists(index)) {
            return reg.get_components<DrawableComponent>()[index]
                .value()
                .getType();
        }
        return DrawableType::UNKNOWN_TYPE;
    }

    /**
     * \fn void changeDrawableAt(size_t index, std::string name, DrawableType type) 
     * \brief Change the drawable of a drawable component
     * \param index The index of the drawable component
     * \param name The name of the drawable component
     * \param type The type of the drawable component
     */
    void changeDrawableAt(size_t index, std::string name, DrawableType type)
    {
        if (reg.get_components<DrawableComponent>().exists(index)) {
            reg.get_components<DrawableComponent>()[index]
                .value()
                .changeDrawable(name, type);
        }
    }

  private:
    registry& reg;  /*!< The registry */
};