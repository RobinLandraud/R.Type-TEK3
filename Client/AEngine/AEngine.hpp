#include <memory>

#pragma once

#include "AAudioEngine.hpp"
#include "AEventEngine.hpp"
#include "AGraphicsEngine.hpp"
#include "AWindowEngine.hpp"

/**
 * \class AEngine
 * \brief Abstract class for engine.
 * Used to manage all the other engines
 */
class AEngine
{
  public:
    AEngine();                    /*!< Default constructor */
    virtual ~AEngine() = default; /*!< Default destructor */

    /**
     * \fn virtual void update() = 0
     * \brief Update the engine
     */
    virtual void update() = 0;

    /**
     * \fn bool isRunning() const
     * \brief Check if the engine is running
     * \return True if the engine is running
     */
    bool isRunning() const;

    /**
     * \fn AWindowEngine& getWindow()
     * \brief Get the window engine
     * \return The window engine
     */
    AWindowEngine& getWindow();

    /**
     * \fn AGraphicsEngine& getGraphics()
     * \brief Get the graphics engine
     * \return The graphics engine
     */
    AGraphicsEngine& getGraphics();

    /**
     * \fn AEventEngine& getEvent()
     * \brief Get the event engine
     * \return The event engine
     */
    AEventEngine& getEvent();

    /**
     * \fn AAudioEngine& getAudio()
     * \brief Get the audio engine
     * \return The audio engine
     */
    AAudioEngine& getAudio();

    /**
     * \fn void stop()
     * \brief Stop the engine
     */
    void stop();

  protected:
    bool running;                                    /*!< Check if the engine is running */
    std::unique_ptr<AEventEngine> eventEngine;       /*!< Event engine */
    std::unique_ptr<AWindowEngine> windowEngine;     /*!< Window engine */
    std::unique_ptr<AGraphicsEngine> graphicsEngine; /*!< Graphics engine */
    std::unique_ptr<AAudioEngine> audioEngine;       /*!< Audio engine */
};