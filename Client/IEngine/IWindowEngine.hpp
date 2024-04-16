#include <iostream>

/**
 * \class IWindowEngine
 * \brief Interface for the window engine
 * Used to create a window
 */
class IWindowEngine
{
  public:
    virtual ~IWindowEngine() = default; /*!< Default destructor */

    /**
     * \fn virtual void closeWindow() = 0;
     * \brief Close the window
     */
    virtual void closeWindow() = 0;

    /**
     * \fn virtual bool isOpen() = 0;
     * \brief Check if the window is open
     * \return True if the window is open, false otherwise
     */
    virtual bool isOpen() = 0;

    /**
     * \fn virtual void clear() = 0;
     * \brief Clear the window
     */
    virtual void clear() = 0;

    /**
     * \fn virtual void display() = 0;
     * \brief Display the window
     */
    virtual void display() = 0;
};