#include "AEventEngine.hpp"

/**
 * \fn std::vector<Key> &AEventEngine::getKeysPressed()
 * \brief Get the keys pressed
 * \return the keys pressed
 */
std::vector<Key>& AEventEngine::getKeysPressed()
{
    return keysPressed;
}

/**
 * \fn std::vector<Key> &AEventEngine::getKeysReleased()
 * \brief Get the keys released
 * \return the keys released
 */
std::vector<Key>& AEventEngine::getKeysReleased()
{
    return keysReleased;
}

/**
 * \fn std::vector<EventType> &AEventEngine::getEvents()
 * \brief Get the events
 * \return the events
 */
std::vector<EventType>& AEventEngine::getEvents()
{
    return events;
}

/**
 * \fn mouse_t &AEventEngine::getMouse()
 * \brief Get the mouse
 * \return The mouse
 */
mouse_t& AEventEngine::getMouse()
{
    return mouse;
}