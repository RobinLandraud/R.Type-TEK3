//#include "utils.hpp"
#include <iostream>

#pragma once

/**
 * \class AGraphicsEngine
 * \brief Abstract class for graphics engine.
 * Used to draw sprites and texts
 */
class AGraphicsEngine
{
  public:
    AGraphicsEngine() = default;          /*!< Default constructor */
    virtual ~AGraphicsEngine() = default; /*!< Default destructor */

    /**
     * \fn virtual int createTExture(const std::string name, const std::string &path) = 0 
     * \brief Create a texture 
     * \param name Name of the texture 
     * \param path Source of the texture 
     * \return Error code
     */
    virtual int createTexture(
        const std::string name, const std::string source) = 0;

    /**
     * \fn virtual int createSprite(std::string name, std::string source) = 0
     * \brief Create a sprite
     * \param name Name of the sprite
     * \param source Source of the sprite
     * \return Error code
     */
    virtual int createSprite(std::string name, std::string textureName) = 0;

    /**
     * \fn virtual void drawSprite(std::string name, float x, float y) = 0
     * \brief Draw a sprite
     * \param name Name of the sprite
     * \param x X position of the sprite
     * \param y Y position of the sprite
     */
    virtual void drawSprite(std::string name, float x, float y) = 0;

    // virtual Size2D_t getSpriteSize(std::string name) = 0;

    /**
     * \fn virtual int createCircle(std::string name, float radius) = 0
     * \brief Create a circle
     * \param name Name of the circle
     * \param radius Radius of the circle
     * \return Error code
     */
    virtual int createCircle(std::string name, float radius) = 0;

    /**
     * \fn virtual void drawCircle(std::string name, float x, float y) = 0
     * \brief Draw a circle
     * \param name Name of the circle
     * \param x X position of the circle
     * \param y Y position of the circle
     */
    virtual void drawCircle(std::string name, float x, float y) = 0;

    /**
     * \fn virtual int createRectangle(std::string name, float width, float height) = 0 
     * \brief Create a rectangle 
     * \param name Name of the rectangle
     * \param width Width of the rectangle
     * \param height Height of the rectangle
     * \return Error code
     */
    virtual int createRectangle(
        std::string name, float width, float height) = 0;

    /**
     * \fn virtual void drawRectangle(std::string name, float x, float y) = 0
     * \brief Draw a rectangle
     * \param name Name of the rectangle
     * \param x X position of the rectangle
     * \param y Y position of the rectangle
     */
    virtual void drawRectangle(std::string name, float x, float y) = 0;

    /**
     * \fn virtual int createFont(std::string name, std::string source) = 0
     * \brief Create a font
     * \param name Name of the font
     * \param source Source of the font
     * \return Error code
     */
    virtual int createFont(std::string name, std::string source) = 0;

    /**
     * \fn virtual int createText(std::string name, std::string text, std::string font) = 0 
     * \brief Create a text 
     * \param name Name of the text
     * \param text Text to display
     * \param font Font of the text
     * \return Error code
     */
    virtual int createText(std::string name,
        std::string text,
        std::string font,
        unsigned int size) = 0;

    /**
     * \fn virtual void drawText(std::string name, float x, float y) = 0
     * \brief Draw a text
     * \param name Name of the text
     * \param x X position of the text
     * \param y Y position of the text
     */
    virtual void drawText(std::string name, float x, float y) = 0;

    /**
     * \fn virtual void changeText(std::string name, std::string text) = 0;
     * \brief Change the text of a text
     * \param name Name of the text
     * \param text New text
     */
    virtual void changeText(std::string name, std::string text) = 0;

    /**
     * \fn virtual std::string getText(std::string name) = 0;
     * \brief Get the text of a text
     * \param name Name of the text
     * \return The text
     */
    virtual std::string getText(std::string name) = 0;
};