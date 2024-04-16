#pragma once
#include "AEngine.hpp"
#include "SFMLAudioEngine.hpp"
#include "SFMLEventEngine.hpp"
#include "SFMLGraphicsEngine.hpp"
#include "SFMLWindowEngine.hpp"

/**
 * \class SFMLEngine
 * \brief A class that handle the SFML engine.
 * Used to handle the SFML engine
 */
class SFMLEngine : public AEngine
{
  public:
    /**
     * \fn SFMLEngine(int size_x = 500, int size_y = 500, const std::string& title = "R-Type");
     * \brief Constructor
     * \param size_x The size of the window on the x axis
     * \param size_y The size of the window on the y axis
     * \param title The title of the window
     */
    SFMLEngine(int size_x = 500,
        int size_y = 500,
        const std::string& title = "R-Type");
    ~SFMLEngine() = default;  /*!< Default destructor */

    /**
     * \fn void update() override;
     * \brief Update the engine
     */
    void update() override;
};