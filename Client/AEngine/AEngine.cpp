#include "AEngine.hpp"

/**
 * \fn AEngine
 * \brief Default constructor of the engine
 */
AEngine::AEngine()
    : running(true)
    , eventEngine(nullptr)
    , windowEngine(nullptr)
    , graphicsEngine(nullptr)
    , audioEngine(nullptr)
{
}

/**
 * \fn bool AEngine::isRunning() const
 * \brief Check if the engine is running
 * \return True if the engine is running
 */
bool AEngine::isRunning() const
{
    return running;
}

/**
 * \fn AWindowEngine& AEngine::getWindow()
 * \brief Get the window engine
 * \return The window engine
 */
AWindowEngine& AEngine::getWindow()
{
    return *windowEngine;
}

/**
 * \fn AGraphicsEngine& AEngine::getGraphics()
 * \brief Get the graphics engine
 * \return The graphics engine
 */
AGraphicsEngine& AEngine::getGraphics()
{
    return *graphicsEngine;
}

/**
 * \fn AEventEngine& AEngine::getEvent()
 * \brief Get the event engine
 * \return The event engine
 */
AEventEngine& AEngine::getEvent()
{
    return *eventEngine;
}

/**
 * \fn AAudioEngine& AEngine::getAudio()
 * \brief Get the audio engine
 * \return The audio engine
 */
AAudioEngine& AEngine::getAudio()
{
    return *audioEngine;
}

/**
 * \fn void AEngine::stop()
 * \brief Stop the engine
 */
void AEngine::stop()
{
    running = false;
}