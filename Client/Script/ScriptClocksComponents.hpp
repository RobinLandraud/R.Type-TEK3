#pragma once

#include "ClocksComponent.hpp"

/**
 * \class ScriptClocksComponents
 * \brief ScriptClocksComponents class
 */
class ScriptClocksComponents
{
  public:
    /**
     * \fn ScriptClocksComponents(registry& reg)
     * \brief The constructor
     * \param reg The registry
     */
    ScriptClocksComponents(registry& reg)
        : reg(reg){};
    ~ScriptClocksComponents() = default;    /*!< Default destructor */

    /**
     * \fn void add(size_t ent_id, float secondes)
     * \brief Add a clock component to an entity
     * \param ent_id The entity id
     * \param secondes The number of secondes of the clock
     */
    void add(size_t ent_id, float secondes)
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<ClocksComponent>(
            entity.value(), ClocksComponent(secondes));
    }

    /**
     * \fn size_t size()
     * \brief Get the number of clock components
     * \return size_t The number of clock components
     */
    size_t size()
    {
        return reg.get_components<ClocksComponent>().size();
    }

    /**
     * \fn ClocksComponent& at(size_t index)
     * \brief Get a clock component at a specific index
     * \param index The index of the clock component
     * \return ClocksComponent& The clock component
     */
    ClocksComponent& at(size_t index)
    {
        return reg.get_components<ClocksComponent>()[index].value();
    }

    /**
     * \fn bool exists(size_t index)
     * \brief Check if a clock component exists at a specific index
     * \param index The index of the clock component
     * \return bool True if the clock component exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<ClocksComponent>().exists(index);
    }

    /**
     * \fn void addClockAt(size_t index, std::string key, float secondes) 
     * \brief Add a clock to a clock component at a specific index
     * \param index The index of the clock component
     * \param key The key of the clock
     * \param secondes The number of secondes of the clock
     */
    void addClockAt(size_t index, std::string key, float secondes)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index].value().addClock(
                key, secondes);
        }
    }

    /**
     * \fn void removeClockAt(size_t index, std::string key)
     * \brief Remove a clock from a clock component at a specific index
     * \param index The index of the clock component
     * \param key The key of the clock
     */
    void removeClockAt(size_t index, std::string key)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index].value().removeClock(
                key);
        }
    }

    /**
     * \fn void updateClocksAt(size_t index)
     * \brief Update the clocks of a clock component at a specific index
     * \param index The index of the clock component
     */
    void updateClocksAt(size_t index)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index].value().updateClocks();
        }
    }

    /**
     * \fn void pauseClockAt(size_t index, std::string key)
     * \brief Pause a clock of a clock component at a specific index
     * \param index The index of the clock component
     * \param key The key of the clock
     */
    void pauseClockAt(size_t index, std::string key)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getClock(key)
                .pause();
        }
    }

    /**
     * \fn void playClockAt(size_t index, std::string key)
     * \brief Play a clock of a clock component at a specific index
     * \param index The index of the clock component
     * \param key The key of the clock
     */
    void playClockAt(size_t index, std::string key)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getClock(key)
                .play();
        }
    }

    /**
     * \fn bool isRunningClockAt(size_t index, std::string key)
     * \brief Check if a clock of a clock component at a specific index is running
     * \param index The index of the clock component
     * \param key The key of the clock
     * \return true if the clock is running, false otherwise
     */
    bool isRunningClockAt(size_t index, std::string key)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            return reg.get_components<ClocksComponent>()[index]
                .value()
                .getClock(key)
                .isRunning();
        }
        return false;
    }

    /**
     * \fn void refreshClockAt(size_t index, std::string key)
     * \brief Refresh a clock of a clock component at a specific index
     * \param index The index of the clock component
     * \param key The key of the clock
     */
    void refreshClockAt(size_t index, std::string key)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getClock(key)
                .refresh();
        }
    }

    /**
     * \fn void resetClockAt(size_t index, std::string key) 
     * \brief Reset a clock of a clock component at a specific index
     * \param index The index of the clock component
     * \param key The key of the clock
     */
    void resetClockAt(size_t index, std::string key)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getClock(key)
                .reset();
        }
    }

    /**
     * \fn void loopClockAt(size_t index, std::string key)
     * \brief Loop a clock of a clock component at a specific index
     * \param index The index of the clock component
     * \param key The key of the clock
     */
    void loopClockAt(size_t index, std::string key)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getClock(key)
                .loop();
        }
    }

    /**
     * \fn bool isTickClockAt(size_t index, std::string key)
     * \brief Check if a clock of a clock component at a specific index is ticked
     * \param index The index of the clock component
     * \param key The key of the clock
     * \return true if the clock is ticked, false otherwise
     */
    bool isTickClockAt(size_t index, std::string key)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            return reg.get_components<ClocksComponent>()[index]
                .value()
                .getClock(key)
                .isTick();
        }
        return false;
    }

    /**
     * \fn void pauseDefaultClockAt(size_t index)
     * \brief Pause the default clock of a clock component at a specific index
     * \param index The index of the clock component
     */
    void pauseDefaultClockAt(size_t index)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getDefaultClock()
                .pause();
        }
    }

    /**
     * \fn void playDefaultClockAt(size_t index)
     * \brief Play the default clock of a clock component at a specific index
     * \param index The index of the clock component
     */
    void playDefaultClockAt(size_t index)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getDefaultClock()
                .play();
        }
    }

    /**
     * \fn bool isRunningDefaultClockAt(size_t index)
     * \brief Check if the default clock of a clock component at a specific index is running
     * \param index The index of the clock component
     * \return true if the default clock is running, false otherwise
     */
    bool isRunningDefaultClockAt(size_t index)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            return reg.get_components<ClocksComponent>()[index]
                .value()
                .getDefaultClock()
                .isRunning();
        }
        return false;
    }

    /**
     * \fn void refreshDefaultClockAt(size_t index)
     * \brief Refresh the default clock of a clock component at a specific index
     * \param index The index of the clock component
     */
    void refreshDefaultClockAt(size_t index)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getDefaultClock()
                .refresh();
        }
    }

    /**
     * \fn void resetDefaultClockAt(size_t index)
     * \brief Reset the default clock of a clock component at a specific index
     * \param index The index of the clock component
     */
    void resetDefaultClockAt(size_t index)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getDefaultClock()
                .reset();
        }
    }

    /**
     * \fn void loopDefaultClockAt(size_t index)
     * \brief Loop the default clock of a clock component at a specific index
     * \param index The index of the clock component
     */
    void loopDefaultClockAt(size_t index)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            reg.get_components<ClocksComponent>()[index]
                .value()
                .getDefaultClock()
                .loop();
        }
    }

    /**
     * \fn bool isTickDefaultClockAt(size_t index)
     * \brief Check if the default clock of a clock component at a specific index is ticked
     * \param index The index of the clock component
     * \return true if the default clock is ticked, false otherwise
     */
    bool isTickDefaultClockAt(size_t index)
    {
        if (reg.get_components<ClocksComponent>().exists(index)) {
            return reg.get_components<ClocksComponent>()[index]
                .value()
                .getDefaultClock()
                .isTick();
        }
        return false;
    }

  private:
    registry& reg;  /*!< The registry */
};