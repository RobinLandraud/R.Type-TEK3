#pragma once
#include <SFML/System/Clock.hpp>
#include <string>

#include "ClocksComponent.hpp"

/**
 * \class BlinkComponent
 * \brief A component to blink an entity.
 * Used to create a blinking entity
 */
class BlinkComponent
{
  public:
    /**
     * \fn explicit BlinkComponent(unsigned int clockLoops = 1, std::string clockName = "")
     * \brief Default constructor
     * \param clockLoops Number of loops of the clock
     * \param clockName Name of the clock
     */
    explicit BlinkComponent(
        unsigned int clockLoops = 1, std::string clockName = "")
        : clockLoops(clockLoops)
        , actualLoop(0)
        , blink(true)
        , clockName(clockName){};
    ~BlinkComponent() = default; /*!< Default destructor */

    BlinkComponent(
        BlinkComponent const&) = default; /*!< Default copy constructor */
    BlinkComponent(
        BlinkComponent&&) noexcept = default; /*!< Default move constructor */
    BlinkComponent& operator=(
        BlinkComponent const&) = default; /*!< Default copy assignment operator */
    BlinkComponent& operator=(
        BlinkComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn [[nodiscard]] bool isBlink() const
     * \brief Check if the entity is blinking
     * \return true if the entity is blinking
     */
    [[nodiscard]] bool isBlink() const
    {
        return blink;
    }

    /**
     * \fn void setClockLoops(unsigned int count)
     * \brief Set the number of loops of clock to switch the state of blink
     * \param clockLoops the number of loops of clock to switch the state of
     * blink
     */
    void setClockLoops(unsigned int count)
    {
        clockLoops = count;
    }

    /**
     * \fn void addActualLoop()
     * \brief Add a loop to the actual loop
     */
    void addActualLoop()
    {
        actualLoop += 1;
        if (actualLoop >= clockLoops) {
            blink = !blink;
            actualLoop = 0;
        }
    }

    /**
     * \fn std::string getClockName()
     * \brief Get the name of the clock
     * \return The name of the clock
     */
    std::string getClockName()
    {
        return clockName;
    }

    /**
     * \fn void setClockName(const std::string clockName)
     * \brief Set the name of the clock
     * \param clockName The name of the clock
     */
    void setClockName(const std::string clockName)
    {
        this->clockName = clockName;
    }

  private:
    std::string clockName;   /*!< The name of the clock */
    unsigned int clockLoops; /*!< Number of loops of clock to blink */
    unsigned int actualLoop; /*!< Actual loop of clock */
    bool blink;              /*!< Check if the entity is blinking */
};