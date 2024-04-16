#include "AWindowEngine.hpp"
#include "SFML/Graphics.hpp"

/**
 * \class SFMLWindowEngine
 * \brief A class that handle the window.
 * Used to create a window
 */
class SFMLWindowEngine : public AWindowEngine
{
  public:
    /**
     * \fn SFMLWindowEngine(int size_x = 500, int size_y = 500, const std::string& title = "R-Type");
     * \brief Constructor
     * \param size_x The size of the window on the x axis
     * \param size_y The size of the window on the y axis
     * \param title The title of the window
     */
    SFMLWindowEngine(int size_x = 500,
        int size_y = 500,
        const std::string& title = "R-Type");
    ~SFMLWindowEngine() = default;  /*!< Default destructor */
    void closeWindow() override;  /*!< Close the window */
    bool isOpen() override; /*!< Check if the window is open */
    void clear() override;  /*!< Clear the window */
    void display() override;  /*!< Display the window */
    sf::RenderWindow& getWindow();  /*!< Get the window */

  private:
    sf::RenderWindow window;  /*!< The window */
};