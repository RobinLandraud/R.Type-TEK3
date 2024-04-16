#include <iostream>

/**
 * \class IGrapicsEngine
 * \brief Interface for the graphics engine
 * Used to draw stuff
 */
class IGraphicsEngine
{
  public:
    virtual ~IGraphicsEngine() = default; /*!< Default destructor */

    /**
     * \fn virtual int createSprite(std::string& name, std::string& source) = 0;
     * \brief Create a sprite
     * \param name Name of the sprite
     * \param source Path to the sprite file
     * \return Error code
     */
    virtual int createSprite(std::string& name, std::string& source) = 0;

    /**
     * \fn virtual void drawSprite(std::string& name, unsigned int x, unsigned
     * int y) = 0; \brief Draw a sprite \param name Name of the sprite \param x
     * X position of the sprite \param y Y position of the sprite
     */
    virtual void drawSprite(
        std::string& name, unsigned int x, unsigned int y) = 0;

    /**
     * \fn virtual int createCircle(std::string& name, unsigned int radius) = 0;
     * \brief Create a circle
     * \param name Name of the circle
     * \param radius Radius of the circle
     * \return Error code
     */
    virtual int createCircle(std::string& name, unsigned int radius) = 0;

    /**
     * \fn virtual void drawCircle(std::string& name, unsigned int x, unsigned
     * int y) = 0; \brief Draw a circle \param name Name of the circle \param x
     * X position of the circle \param y Y position of the circle
     */
    virtual void drawCircle(
        std::string& name, unsigned int x, unsigned int y) = 0;

    /**
     * \fn virtual int createRectangle(std::string& name, unsigned int width,
     * unsigned int height) = 0; \brief Create a rectangle \param name Name of
     * the rectangle \param width Width of the rectangle \param height Height of
     * the rectangle \return Error code
     */
    virtual int createRectangle(
        std::string& name, unsigned int width, unsigned int height) = 0;

    /**
     * \fn virtual void drawRectangle(std::string& name, unsigned int x,
     * unsigned int y) = 0; \brief Draw a rectangle \param name Name of the
     * rectangle \param x X position of the rectangle \param y Y position of the
     * rectangle
     */
    virtual void drawRectangle(
        std::string& name, unsigned int x, unsigned int y) = 0;

    /**
     * \fn virtual int createFont(std::string& name, std::string& source) = 0;
     * \brief Create a font
     * \param name Name of the font
     * \param source Path to the font file
     * \return Error code
     */
    virtual int createFont(std::string& name, std::string& source) = 0;

    /**
     * \fn virtual int createText(std::string& name, std::string& text,
     * std::string& font, unsigned int size) = 0; \brief Create a text \param
     * name Name of the text \param text Text to display \param font Name of the
     * font \param size Size of the text \return Error code
     */
    virtual int createText(std::string& name,
        std::string& text,
        std::string& font,
        unsigned int size) = 0;

    /**
     * \fn virtual void drawText(std::string& text, unsigned int x, unsigned int
     * y) = 0; \brief Draw a text \param text Name of the text \param x X
     * position of the text \param y Y position of the text
     */
    virtual void drawText(
        std::string& text, unsigned int x, unsigned int y) = 0;
};