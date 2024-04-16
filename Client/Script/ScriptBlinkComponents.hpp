#pragma once

#include "BlinkComponent.hpp"

/**
 * \class ScriptBlinkComponents
 * \brief Script to blink components
 */
class ScriptBlinkComponents
{
  public:
    /**
     * \fn ScriptBlinkComponents(registry& reg)
     * \brief The constructor
     * \param reg The registry
     */
    ScriptBlinkComponents(registry& reg)
        : reg(reg){};
    ~ScriptBlinkComponents() = default; /*!< Default destructor */

    /**
     * \fn void add(size_t ent_id, unsigned int clockLoops = 1, std::string clockName = "")
     * \brief Add a blink component to an entity
     * \param ent_id The entity id
     * \param clockLoops The number of loops of the clock
     * \param clockName The name of the clock
     */
    void add(
        size_t ent_id, unsigned int clockLoops = 1, std::string clockName = "")
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<BlinkComponent>(
            entity.value(), BlinkComponent(clockLoops, clockName));
    }

    /**
     * \fn size_t size()
     * \brief Get the number of blink components
     * \return The number of blink components
     */
    size_t size()
    {
        return reg.get_components<BlinkComponent>().size();
    }

    /**
     * \fn BlinkComponent& at(size_t index)
     * \brief Get a blink component
     * \param index The index of the blink component
     * \return The blink component
     */
    BlinkComponent& at(size_t index)
    {
        return reg.get_components<BlinkComponent>()[index].value();
    }

    /**
     * \fn bool exists(size_t index)
     * \brief Check if a blink component exists
     * \param index The index of the blink component
     * \return true if the blink component exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<BlinkComponent>().exists(index);
    }

    /**
     * \fn bool isBlinkAt(size_t index)
     * \brief Check if a blink component is blinking
     * \param index The index of the blink component
     * \return true if the blink component is blinking, false otherwise
     */
    bool isBlinkAt(size_t index)
    {
        if (reg.get_components<BlinkComponent>().exists(index)) {
            return reg.get_components<BlinkComponent>()[index]
                .value()
                .isBlink();
        }
        return false;
    }

    /**
     * \fn void setClockLoopsAt(size_t index, unsigned int clockLoops)
     * \brief Set the number of loops of a blink component
     * \param index The index of the blink component
     * \param clockLoops The number of loops of the clock
     */
    void setClockLoopsAt(size_t index, unsigned int clockLoops)
    {
        if (reg.get_components<BlinkComponent>().exists(index)) {
            reg.get_components<BlinkComponent>()[index].value().setClockLoops(
                clockLoops);
        }
    }

    /**
     * \fn void addActualLoopAt(size_t index)
     * \brief Add an actual loop to a blink component
     * \param index The index of the blink component
     */
    void addActualLoopAt(size_t index)
    {
        if (reg.get_components<BlinkComponent>().exists(index)) {
            reg.get_components<BlinkComponent>()[index].value().addActualLoop();
        }
    }

    /**
     * \fn std::string getClockNameAt(size_t index)
     * \brief Get the name of the clock of a blink component
     * \param index The index of the blink component
     * \return The name of the clock
     */
    std::string getClockNameAt(size_t index)
    {
        if (reg.get_components<BlinkComponent>().exists(index)) {
            return reg.get_components<BlinkComponent>()[index]
                .value()
                .getClockName();
        }
        return "";
    }

    /**
     * \fn void setClockNameAt(size_t index, std::string clockName)
     * \brief Set the name of the clock of a blink component
     * \param index The index of the blink component
     * \param clockName The name of the clock
     */
    void setClockNameAt(size_t index, std::string clockName)
    {
        if (reg.get_components<BlinkComponent>().exists(index)) {
            reg.get_components<BlinkComponent>()[index].value().setClockName(
                clockName);
        }
    }

  private:
    registry& reg;  /*!< The registry */
};