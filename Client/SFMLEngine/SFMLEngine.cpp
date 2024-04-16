#include "SFMLEngine.hpp"

/**
 * \fn SFMLEngine::SFMLEngine(int size_x, int size_y, const std::string& title)
 * \brief Constructor
 * \param size_x The size of the window on the x axis
 * \param size_y The size of the window on the y axis
 * \param title The title of the window
 */
SFMLEngine::SFMLEngine(int size_x, int size_y, const std::string& title)
{
    running = true;
    std::unique_ptr<SFMLWindowEngine> SFMLWindowEngine_ =
        std::make_unique<SFMLWindowEngine>(size_x, size_y, title);
    eventEngine =
        std::make_unique<SFMLEventEngine>(SFMLWindowEngine_->getWindow());
    graphicsEngine =
        std::make_unique<SFMLGraphicsEngine>(SFMLWindowEngine_->getWindow());
    audioEngine = std::make_unique<SFMLAudioEngine>();
    windowEngine = std::move(SFMLWindowEngine_);
}

/**
 * \fn void SFMLEngine::update()
 * \brief Update the engine
 */
void SFMLEngine::update()
{
    if (eventEngine == nullptr)
        return;
    eventEngine->update();
    auto& events = eventEngine->getEvents();
    if (std::find(events.begin(), events.end(), sf::Event::Closed)
        != events.end()) {
        windowEngine->closeWindow();
        running = false;
    }
}