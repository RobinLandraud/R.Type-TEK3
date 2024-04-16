#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>

/**
 * \class Clock
 * \brief A simple class to measure time.
 * Used to create a clock.
 */
class Clock
{
  public:
    /**
     * \fn explicit Clock(float secondes = 1)
     * \brief Default constructor
     * \param secondes The number of seconds
     */
    explicit Clock(float secondes = 1)
        : loopTime(std::chrono::milliseconds(
            static_cast<int>(secondes * static_cast<float>(1000.0))))
        , deltaTime(std::chrono::milliseconds(0))
        , begin(std::chrono::steady_clock::now())
        , now(std::chrono::steady_clock::now()){};

    ~Clock() = default; /*!< Default destructor */

    Clock(Clock const&) = default;     /*!< Default copy constructor */
    Clock(Clock&&) noexcept = default; /*!< Default move constructor */
    Clock& operator=(
        Clock const&) = default; /*!< Default copy assignment operator */
    Clock& operator=(
        Clock&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn void pause()
     * \brief Pause the clock
     */
    void pause()
    {
        running = false;
    }

    /**
     * \fn void play()
     * \brief Run the clock
     */
    void play()
    {
        running = true;
    }

    /**
     * \fn [[nodiscard]] bool isRunning() const
     * \brief Check if the clock is running
     * \return True if the clock is running, false otherwise
     */
    [[nodiscard]] bool isRunning() const
    {
        return running;
    }

    /**
     * \fn void refresh()
     * \brief Refresh the clock
     */
    void refresh()
    {
        now = std::chrono::steady_clock::now();
        if (!running)
            begin += std::chrono::steady_clock::now() - now;
        deltaTime = now - begin;
    }

    /**
     * \fn void reset()
     * \brief Reset the clock
     */
    void reset()
    {
        running = true;
        tick = false;
        begin = std::chrono::steady_clock::now();
        now = std::chrono::steady_clock::now();
        deltaTime = std::chrono::milliseconds(0);
    }

    /**
     * \fn void loop()
     * \brief Loop the clock
     */
    void loop()
    {
        refresh();
        if (!running) {
            tick = false;
        } else if (deltaTime >= loopTime) {
            begin += loopTime;
            deltaTime = std::chrono::milliseconds(0);
            tick = true;
        } else {
            tick = false;
        }
    }

    /**
     * \fn [[nodiscard]] bool isTick() const
     * \brief Check if the clock is tick
     * \return true if the clock is tick, false otherwise
     */
    [[nodiscard]] bool isTick() const
    {
        return tick;
    }

  private:
    bool tick = false;                  /*!< True if the clock made a loop */
    bool running = true;                /*!< Check if the clock is running */
    std::chrono::milliseconds loopTime; /*!< Time to wait */
    std::chrono::duration<float> deltaTime; /*!< Time between the last loop and the current loop */
    std::chrono::time_point<std::chrono::steady_clock> begin; /*!< Time of the last loop */
    std::chrono::time_point<std::chrono::steady_clock> now;   /*!< Time of the current loop */
};

/**
 * \class ClocksComponent
 * \brief A component that handle a clock.
 * Used to manage the time
 */
class ClocksComponent
{
  public:
    /**
     * \fn explicit ClocksComponent(float secondes = 0.017)
     * \brief Default constructor
     * @param secondes The number of seconds
     */
    explicit ClocksComponent(float secondes = 0.017)
        : defaultClock(secondes){};
    ~ClocksComponent() = default; /*!< Default destructor */

    ClocksComponent(
        ClocksComponent const&) = default; /*!< Default copy constructor */
    ClocksComponent(
        ClocksComponent&&) noexcept = default; /*!< Default move constructor */
    ClocksComponent& operator=(
        ClocksComponent const&) = default; /*!< Default copy assignment operator */
    ClocksComponent& operator=(
        ClocksComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn Clock& getClock(std::string name)
     * \brief Get a clock
     * \param name The name of the clock
     * \return The clock
     */
    Clock& getClock(std::string name)
    {
        if (this->clocks.find(name) != this->clocks.end()) {
            return this->clocks[name];
        }
        return this->defaultClock;
    }

    /**
     * \fn std::unordered_map<std::string, Clock>& getClocks()
     * \brief Get all the clocks
     * @return All the clocks
     */
    std::unordered_map<std::string, Clock>& getClocks()
    {
        return this->clocks;
    }

    /**
     * \fn void addClock(std::string name, float secondes)
     * \brief Add a clock
     * \param name The name of the clock
     * \param secondes The number of seconds
     */
    void addClock(std::string name, float secondes)
    {
        clocks[name] = std::move(Clock(secondes));
    }

    /**
     * \fn void removeClock(std::string name)
     * \brief Remove a clock
     * \param name The name of the clock
     */
    void removeClock(std::string name)
    {
        if (this->clocks.find(name) != this->clocks.end()) {
            this->clocks.erase(name);
        }
    }

    /**
     * \fn Clock& getDefaultClock()
     * \brief Get the default clock
     * \return The default clock
     */
    Clock& getDefaultClock()
    {
        return this->defaultClock;
    }

    /**
     * \fn void updateClocks()
     * \brief Update all the clocks
     */
    void updateClocks()
    {
        for (auto& clock : clocks) {
            clock.second.loop();
        }
        defaultClock.loop();
    }

  private:
    Clock defaultClock;                             /*!< The default clock */
    std::unordered_map<std::string, Clock> clocks;  /*!< A map of clocks */
};