#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

//#include "utils.hpp"
#include "AGraphicsEngine.hpp"
#include "SFML/Graphics.hpp"

/**
 * \class SFMLGraphicsEngine
 * \brief A class that handle the graphics.
 * Used to draw graphics
 */
class SFMLGraphicsEngine : public AGraphicsEngine
{
  public:
    SFMLGraphicsEngine(sf::RenderWindow& window); /*!< Default constructor */
    ~SFMLGraphicsEngine() override = default; /*!< Default destructor */

    /**
     * \fn int createTexture(const std::string name, const std::string source) override;
     * \brief Create a texture
     * \param name The name of the texture
     * \param source The source of the texture
     * \return The id of the texture
     */
    int createTexture(
        const std::string name, const std::string source) override;

    /**
     * \fn int createSprite(std::string name, std::string textureName) override;
     * \brief Create a sprite
     * \param name The name of the sprite
     * \param textureName The name of the texture
     * \return The id of the sprite
     */
    int createSprite(std::string name, std::string textureName) override;

    /**
     * \fn void drawSprite(std::string name, float x, float y) override;
     * \brief Draw a sprite
     * \param name The name of the sprite
     * \param x The x position of the sprite
     * \param y The y position of the sprite
     */
    void drawSprite(std::string name, float x, float y) override;

    /**
     * \fn int createCircle(std::string name, float radius) override;
     * \brief Create a circle
     * \param name The name of the circle
     * \param radius The radius of the circle
     * \return The id of the circle
     */
    int createCircle(std::string name, float radius) override;

    /**
     * \fn void drawCircle(std::string name, float x, float y) override;
     * \brief Draw a circle
     * \param name The name of the circle
     * \param x The x position of the circle
     * \param y The y position of the circle
     */
    void drawCircle(std::string name, float x, float y) override;
    // Size2D_t getSpriteSize(std::string name) override;

    /**
     * \fn int createRectangle(std::string name, float width, float height) override;
     * \brief Create a rectangle
     * \param name The name of the rectangle
     * \param width The width of the rectangle
     * \param height The height of the rectangle
     * \return The id of the rectangle
     */
    int createRectangle(std::string name, float width, float height) override;

    /**
     * \fn void drawRectangle(std::string name, float x, float y) override;
     * \brief Draw a rectangle
     * \param name The name of the rectangle
     * \param x The x position of the rectangle
     * \param y The y position of the rectangle
     */
    void drawRectangle(std::string name, float x, float y) override;

    /**
     * \fn int createFont(std::string name, std::string source) override;
     * \brief Create a font
     * @param name The name of the font
     * @param source The source of the font
     * @return The id of the font
     */
    int createFont(std::string name, std::string source) override;

    /**
     * \fn int createText(std::string name, std::string text, std::string font, unsigned int size) override;
     * \brief Create a text
     * \param name The name of the text
     * \param text The text to display
     * \param font The font of the text
     * \param size The size of the text
     * \return The id of the text
     */
    int createText(std::string name,
        std::string text,
        std::string font,
        unsigned int size) override;

    /**
     * \fn void drawText(std::string name, float x, float y) override; 
     * \brief Draw a text
     * \param name The name of the text
     * \param x The x position of the text
     * \param y The y position of the text
     */
    void drawText(std::string name, float x, float y) override;

    /**
     * \fn void changeText(std::string name, std::string text) override;
     * \brief Change the text of a text
     * \param name The name of the text
     * \param text The new text
     */
    void changeText(std::string name, std::string text) override;

    /**
     * \fn std::string getText(std::string name) override;
     * \brief Get the text of a text
     * \param name The name of the text
     * \return The text
     */
    std::string getText(std::string name) override;

  private:
    std::unordered_map<std::string, sf::Sprite> sprites;  /*!< The sprites */
    std::unordered_map<std::string, sf::CircleShape> circles; /*!< The circles */
    std::unordered_map<std::string, sf::RectangleShape> rectangles; /*!< The rectangles */
    std::unordered_map<std::string, sf::Font> fonts;  /*!< The fonts */
    std::unordered_map<std::string, sf::Text> texts;  /*!< The texts */
    std::unordered_map<std::string, sf::Texture> textures;  /*!< The textures */
    sf::RenderWindow& window;   /*!< The window */
};