#include "SFMLGraphicsEngine.hpp"

#include <SFML/Graphics/Color.hpp>

/**
 * \fn SFMLGraphicsEngine::SFMLGraphicsEngine(sf::RenderWindow& window)
 * \brief Default constructor
 * \param window The window
 */
SFMLGraphicsEngine::SFMLGraphicsEngine(sf::RenderWindow& window)
    : window(window)
{
}

/**
 * \fn int SFMLGraphicsEngine::createTexture(const std::string name, const std::string source)
 * \brief Create a texture
 * \param name The name of the texture
 * \param source The source of the texture
 * \return The id of the texture
 */
int SFMLGraphicsEngine::createTexture(
    const std::string name, const std::string source)
{
    if (!textures[name].loadFromFile(source)) {
        return -1;
    }
    return 0;
}

/**
 * \fn int SFMLGraphicsEngine::createSprite(std::string name, std::string textureName)
 * \brief Create a sprite
 * \param name The name of the sprite
 * \param textureName The name of the texture
 * \return The id of the sprite
 */
int SFMLGraphicsEngine::createSprite(std::string name, std::string textureName)
{
    if (textures.find(textureName) == textures.end()) {
        return -1;
    }
    sprites[name].setTexture(textures[textureName]);
    return 0;
}

/**
 * \fn void SFMLGraphicsEngine::drawSprite(std::string name, float x, float y)
 * \brief Draw a sprite
 * \param name The name of the sprite
 * \param x The x position of the sprite
 * \param y The y position of the sprite
 */
void SFMLGraphicsEngine::drawSprite(std::string name, float x, float y)
{
    if (sprites.find(name) != sprites.end()) {
        sprites[name].setPosition(x, y);
        window.draw(sprites[name]);
    }
}

/**
 * \fn int SFMLGraphicsEngine::createCircle(std::string name, float radius)
 * \brief Create a circle
 * \param name The name of the circle
 * \param radius The radius of the circle
 * \return The id of the circle
 */
int SFMLGraphicsEngine::createCircle(std::string name, float radius)
{
    sf::CircleShape circle(radius);
    circles[name] = circle;
    return 0;
}

/**
 * \fn void SFMLGraphicsEngine::drawCircle(std::string name, float x, float y)
 * \brief Draw a circle
 * \param name The name of the circle
 * \param x The x position of the circle
 * \param y The y position of the circle
 */
void SFMLGraphicsEngine::drawCircle(std::string name, float x, float y)
{
    if (circles.find(name) != circles.end()) {
        circles[name].setPosition(x, y);
        window.draw(circles[name]);
    }
}

/**
 * \fn int SFMLGraphicsEngine::createRectangle(std::string name, float width, float height)
 * \brief Create a rectangle
 * \param name The name of the rectangle
 * \param width The width of the rectangle
 * \param height The height of the rectangle
 * \return The id of the rectangle
 */
int SFMLGraphicsEngine::createRectangle(
    std::string name, float width, float height)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setFillColor(sf::Color::Black);
    rectangles[name] = rectangle;
    return 0;
}

/**
 * \fn void SFMLGraphicsEngine::drawRectangle(std::string name, float x, float y)
 * \brief Draw a rectangle
 * \param name The name of the rectangle
 * \param x The x position of the rectangle
 * \param y The y position of the rectangle
 */
void SFMLGraphicsEngine::drawRectangle(std::string name, float x, float y)
{
    if (rectangles.find(name) != rectangles.end()) {
        rectangles[name].setPosition(x, y);
        window.draw(rectangles[name]);
    }
}

/**
 * \fn int SFMLGraphicsEngine::createFont(std::string name, std::string source)
 * \brief Create a font
 * \param name The name of the font
 * \param source The source of the font
 * \return The id of the font
 */
int SFMLGraphicsEngine::createFont(std::string name, std::string source)
{
    sf::Font font;
    if (!font.loadFromFile(source))
        return -1;
    fonts[name] = font;
    return 0;
}

/**
     * \fn int SFMLGraphicsEngine::createText(std::string name, std::string text, std::string font, unsigned int size) override;
     * \brief Create a text
     * \param name The name of the text
     * \param text The text to display
     * \param font The font of the text
     * \param size The size of the text
     * \return The id of the text
     */
int SFMLGraphicsEngine::createText(
    std::string name, std::string text, std::string font, unsigned int size)
{
    if (fonts.find(font) != fonts.end()) {
        sf::Text sfmlText;
        sfmlText.setFont(fonts[font]);
        sfmlText.setString(text);
        sfmlText.setCharacterSize(size);
        sfmlText.setFillColor(sf::Color::White);
        sfmlText.setOutlineColor(sf::Color::Green);
        texts[name] = sfmlText;
        return 0;
    }
    return 1;
}

/**
 * \fn void SFMLGraphicsEngine::drawText(std::string name, float x, float y)
 * \brief Draw a text
 * \param name The name of the text
 * \param x The x position of the text
 * \param y The y position of the text
 */
void SFMLGraphicsEngine::drawText(std::string name, float x, float y)
{
    if (texts.find(name) != texts.end()) {
        texts[name].setPosition(x, y);
        window.draw(texts[name]);
    }
}

/**
 * \fn void SFMLGraphicsEngine::changeText(std::string name, std::string text)
 * \brief Change the text of a text
 * \param name The name of the text
 * \param text The new text
 */
void SFMLGraphicsEngine::changeText(std::string name, std::string text)
{
    if (texts.find(name) != texts.end()) {
        texts[name].setString(text);
    }
}

/**
 * \fn std::string SFMLGraphicsEngine::getText(std::string name)
 * \brief Get the text of a text
 * \param name The name of the text
 * \return The text
 */
std::string SFMLGraphicsEngine::getText(std::string name)
{
    if (texts.find(name) != texts.end()) {
        return texts[name].getString();
    }
    return "";
}