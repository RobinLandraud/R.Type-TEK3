#include "SFMLEventEngine.hpp"

/**
 * \fn SFMLEventEngine::SFMLEventEngine(sf::RenderWindow& window)
 * \brief Default constructor
 * \param window The window
 */
SFMLEventEngine::SFMLEventEngine(sf::RenderWindow& window)
    : window(window)
{
}

/**
 * \fn void SFMLEventEngine::updateKeys()
 * \brief Update the keys
 */
void SFMLEventEngine::updateKeys()
{
    for (std::pair<const sf::Keyboard::Key, Key> pair : this->keys) {
        if (sf::Keyboard::isKeyPressed(pair.first)) {
            this->keysPressed.push_back(pair.second);
        } else if (!sf::Keyboard::isKeyPressed(pair.first)) {
            this->keysPressed.erase(std::remove(this->keysPressed.begin(),
                                        this->keysPressed.end(),
                                        pair.second),
                this->keysPressed.end());
        }
    }
}

/**
 * \fn void SFMLEventEngine::update()
 * \brief Update the event
 */
void SFMLEventEngine::update()
{
    sf::Event event = sf::Event();
    this->keysReleased = {};
    this->keysPressed = {};
    this->events = {};
    this->mouse.wheel = 0;

    updateKeys();

    while (window.pollEvent(event)) {
        if (eventTypes.find(event.type) != eventTypes.end()) {
            this->events.push_back(eventTypes[event.type]);
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    this->mouse.left = true;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    this->mouse.right = true;
                } else if (event.mouseButton.button == sf::Mouse::Middle) {
                    this->mouse.middle = true;
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    this->mouse.left = false;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    this->mouse.right = false;
                } else if (event.mouseButton.button == sf::Mouse::Middle) {
                    this->mouse.middle = false;
                }
            } else if (event.type == sf::Event::MouseMoved) {
                this->mouse.x = sf::Mouse::getPosition(window).x;
                this->mouse.y = sf::Mouse::getPosition(window).y;
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                this->mouse.wheel = event.mouseWheelScroll.delta;
            } else if (event.type == sf::Event::KeyReleased) {
                if (keys.find(event.key.code) != keys.end()) {
                    this->keysReleased.push_back(keys[event.key.code]);
                }
            }
        }
    }
}