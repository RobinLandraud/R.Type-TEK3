#include "SFMLWindowEngine.hpp"

/**
 * \fn SFMLWindowEngine::SFMLWindowEngine(int size_x, int size_y, const std::string& title)
 * \brief Constructor
 * \param size_x The size of the window on the x axis
 * \param size_y The size of the window on the y axis
 * \param title The title of the window
 */
SFMLWindowEngine::SFMLWindowEngine(
    int size_x, int size_y, const std::string& title)
    : window(sf::VideoMode(size_x, size_y),
        title,
        sf::Style::Titlebar | sf::Style::Close)
{
}

/**
 * \fn void SFMLWindowEngine::closeWindow()
 * \brief Close the window
 */
void SFMLWindowEngine::closeWindow()
{
    window.close();
}

/**
 * \fn bool SFMLWindowEngine::isOpen()
 * \brief Check if the window is open
 * \return True if the window is open, false otherwise
 */
bool SFMLWindowEngine::isOpen()
{
    return window.isOpen();
}

/**
 * \fn void SFMLWindowEngine::clear()
 * \brief Clear the window
 */
void SFMLWindowEngine::clear()
{
    window.clear();
}

/**
 * \fn void SFMLWindowEngine::display()
 * \brief Display the window
 */
void SFMLWindowEngine::display()
{
    window.display();
}

/**
 * \fn sf::RenderWindow& SFMLWindowEngine::getWindow()
 * \brief Get the window
 * \return The window
 */
sf::RenderWindow& SFMLWindowEngine::getWindow()
{
    return window;
}