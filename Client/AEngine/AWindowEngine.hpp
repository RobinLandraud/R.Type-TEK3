#include <any>
#include <iostream>

#pragma once

/**
 * \class AWindowEngine
 * \brief Abstract class for window engine.
 * Used to create and update the window
 */
class AWindowEngine
{
  public:
    AWindowEngine() = default;          /*!< Default constructor */
    virtual ~AWindowEngine() = default; /*!< Default destructor */

    /**
     * \fn virtual void closeWindow() = 0
     * \brief Close the window
     */
    virtual void closeWindow() = 0;

    /**
     * \fn virtual void isOpen() = 0
     * \brief Check if the window is open
     * \return True if the window is open
     */
    virtual bool isOpen() = 0;

    /**
     * \fn virtual void clear() = 0
     * \brief Clear the window
     */
    virtual void clear() = 0;

    /**
     * \fn virtual void display() = 0
     * \brief Display the window
     */
    virtual void display() = 0;
};