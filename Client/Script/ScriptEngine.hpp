#pragma once
#include "AEngine.hpp"

/**
 * \class ScriptWindowEngine
 * \brief A class that handle the Script window engine.
 * Used to handle the Script window engine
 */
class ScriptWindowEngine
{
  public:
    /**
     * \fn ScriptWindowEngine(AWindowEngine& windowEngine);
     * \brief Constructor
     * \param windowEngine The window engine
     */
    ScriptWindowEngine(AWindowEngine& windowEngine)
        : windowEngine(windowEngine){};
    ~ScriptWindowEngine() = default;    /*!< Default destructor */

    /**
     * \fn void closeWindow();
     * \brief Close the window
     */
    void closeWindow()
    {
        windowEngine.closeWindow();
    }

    /**
     * \fn bool isOpen();
     * \brief Check if the window is open
     * \return True if the window is open, false otherwise
     */
    bool isOpen()
    {
        return windowEngine.isOpen();
    }

    /**
     * \fn void clear();
     * \brief Clear the window
     */
    void clear()
    {
        windowEngine.clear();
    }

    /**
     * \fn void display();
     * \brief Display the window
     */
    void display()
    {
        windowEngine.display();
    }

  private:
    AWindowEngine& windowEngine;    /*!< The window engine */
};

/**
 * \class ScriptGraphicsEngine
 * \brief A class that handle the Script graphics engine.
 * Used to handle the Script graphics engine
 */
class ScriptGraphicsEngine
{
  public:
    /**
     * \fn ScriptGraphicsEngine(AGraphicsEngine& graphicsEngine);
     * \brief Constructor
     * \param graphicsEngine The graphics engine
     */
    ScriptGraphicsEngine(AGraphicsEngine& graphicsEngine)
        : graphicsEngine(graphicsEngine){};
    ~ScriptGraphicsEngine() = default;  /*!< Default destructor */

    /**
     * \fn void createTexture(const std::string name, const std::string source)
     * \brief Create a texture
     * \param name The name of the texture
     * \param source The source of the texture
     */
    void createTexture(const std::string name, const std::string source)
    {
        graphicsEngine.createTexture(name, source);
    }

    /**
     * \fn void createSprite(const std::string name, const std::string textureName)
     * \brief Create a sprite
     * \param name The name of the sprite
     * \param textureName The name of the texture
     */
    int createSprite(std::string name, std::string textureName)
    {
        return graphicsEngine.createSprite(name, textureName);
    }

    /**
     * \fn void drawSprite(std::string name, float x, float y)
     * \brief Draw a sprite
     * \param name The name of the sprite
     * \param x The x position of the sprite
     * \param y The y position of the sprite
     */
    void drawSprite(std::string name, float x, float y)
    {
        graphicsEngine.drawSprite(name, x, y);
    }

    /**
     * \fn int createCircle(std::string name, float radius)
     * \brief Create a circle
     * \param name The name of the circle
     * \param radius The radius of the circle
     * \return The id of the circle
     */
    int createCircle(std::string name, float radius)
    {
        return graphicsEngine.createCircle(name, radius);
    }

    /**
     * \fn void drawCircle(std::string name, float x, float y)
     * \brief Draw a circle
     * \param name The name of the circle
     * \param x The x position of the circle
     * \param y The y position of the circle
     */
    void drawCircle(std::string name, float x, float y)
    {
        graphicsEngine.drawCircle(name, x, y);
    }

    /**
     * \fn int createRectangle(std::string name, float width, float height)
     * \brief Create a rectangle
     * \param name The name of the rectangle
     * \param width The width of the rectangle
     * \param height The height of the rectangle
     * \return The id of the rectangle
     */
    int createRectangle(std::string name, float width, float height)
    {
        return graphicsEngine.createRectangle(name, width, height);
    }

    /**
     * \fn void drawRectangle(std::string name, float x, float y)
     * \brief Draw a rectangle
     * \param name The name of the rectangle
     * \param x The x position of the rectangle
     * \param y The y position of the rectangle
     */
    void drawRectangle(std::string name, float x, float y)
    {
        graphicsEngine.drawRectangle(name, x, y);
    }

    /**
     * \fn int createFont(std::string name, std::string source)
     * \brief Create a font
     * \param name The name of the font
     * \param source The source of the font
     * \return The id of the font
     */
    int createFont(std::string name, std::string source)
    {
        return graphicsEngine.createFont(name, source);
    }

    /**
     * \fn int createText(std::string name, std::string text, std::string font, int size)
     * \brief Create a text
     * \param name The name of the text
     * \param text The text
     * \param font The font
     * \param size The size of the text
     * \return The id of the text
     */
    int createText(
        std::string name, std::string text, std::string font, int size)
    {
        return graphicsEngine.createText(name, text, font, size);
    }

    /**
     * \fn void drawText(std::string name, float x, float y)
     * \brief Draw a text
     * \param name The name of the text
     * \param x The x position of the text
     * \param y The y position of the text
     */
    void drawText(std::string name, float x, float y)
    {
        graphicsEngine.drawText(name, x, y);
    }

  private:
    AGraphicsEngine& graphicsEngine;    /*!< The graphics engine */
};

/**
 * \class ScriptEventEngine
 * \brief A class that handle the Script event engine.
 * Used to handle the Script event engine
 */
class ScriptEventEngine
{
  public:
    /**
     * \fn ScriptEventEngine(AEventEngine& eventEngine);
     * \brief Constructor
     * \param eventEngine The event engine
     */
    ScriptEventEngine(AEventEngine& eventEngine)
        : eventEngine(eventEngine)
    {
    }
    ~ScriptEventEngine() = default; /*!< Default destructor */

    /**
     * \fn void update()
     * \brief Update the event engine
     */
    void update()
    {
        eventEngine.update();
    }

    /**
     * \fn std::vector<Key>& getKeysPressed()
     * \brief Get the keys pressed
     * \return The keys pressed
     */
    std::vector<Key>& getKeysPressed()
    {
        return eventEngine.getKeysPressed();
    }

    /**
     * \fn bool isKeyPressed(Key key)
     * \brief Check if a key is pressed
     * \param key The key to check
     * \return true if the key is pressed, false otherwise
     */
    bool isKeyPressed(Key key)
    {
        auto keys = eventEngine.getKeysPressed();
        for (auto& k : keys) {
            if (k == key) {
                return true;
            }
        }
        return false;
    }

    /**
     * \fn bool isKeyReleased(Key key)
     * \brief Check if a key is released
     * \param key The key to check
     * \return true if the key is released, false otherwise
     */
    bool isKeyReleased(Key key)
    {
        auto keys = eventEngine.getKeysReleased();
        for (auto& k : keys) {
            if (k == key) {
                return true;
            }
        }
        return false;
    }

    /**
     * \fn std::vector<Key>& getKeysReleased()
     * \brief Get the keys released
     * \return The keys released
     */
    std::vector<Key>& getKeysReleased()
    {
        return eventEngine.getKeysReleased();
    }

    /**
     * \fn std::vector<EventType>& getEvents()
     * \brief Get the events
     * \return The events
     */
    std::vector<EventType>& getEvents()
    {
        return eventEngine.getEvents();
    }

    /**
     * \fn bool isEvent(EventType event)
     * \brief Check if an event is triggered
     * \param event The event to check
     * \return true if the event is triggered, false otherwise
     */
    bool isEvent(EventType event)
    {
        auto events = eventEngine.getEvents();
        for (auto& e : events) {
            if (e == event) {
                return true;
            }
        }
        return false;
    }

    /**
     * \fn mouse_t& getMouse()
     * \brief Get the mouse
     * \return The mouse
     */
    mouse_t& getMouse()
    {
        return eventEngine.getMouse();
    }

  private:
    AEventEngine& eventEngine;  /*!< The event engine */
};

/**
 * \class ScriptAudioEngine
 * \brief A class that handle the Script audio engine.
 */
class ScriptAudioEngine
{
  public:
    /**
     * \fn ScriptAudioEngine(AAudioEngine& audioEngine)
     * \brief Constructor
     * \param audioEngine The audio engine
     */
    ScriptAudioEngine(AAudioEngine& audioEngine)
        : audioEngine(audioEngine)
    {
    }

    /**
     * \fn void createSound(std::string name, std::string source)
     * \brief Create a sound
     * \param name The name of the sound
     * \param source The source of the sound
     */
    void createSound(std::string name, std::string source)
    {
        audioEngine.createSound(name, source);
    }

    /**
     * \fn void playSound(std::string name)
     * \brief Play a sound
     * \param name The name of the sound
     */
    void playSound(std::string name)
    {
        audioEngine.playSound(name);
    }

    /**
     * \fn void stopSound(std::string name)
     * \brief Stop a sound
     * \param name The name of the sound
     */
    void stopSound(std::string name)
    {
        audioEngine.stopSound(name);
    }

    /**
     * \fn void pauseSound(std::string name)
     * \brief Pause a sound
     * \param name The name of the sound
     */
    void pauseSound(std::string name)
    {
        audioEngine.pauseSound(name);
    }

    /**
     * \fn void resumeSound(std::string name)
     * \brief Resume a sound
     * \param name The name of the sound
     */
    void resumeSound(std::string name)
    {
        audioEngine.resumeSound(name);
    }

    /**
     * \fn void setSoundVolume(std::string name, float volume)
     * \brief Set the volume of a sound
     * \param name The name of the sound
     * \param volume The volume of the sound
     */
    void setSoundVolume(std::string name, float volume)
    {
        audioEngine.setSoundVolume(name, volume);
    }

    /**
     * \fn void setSoundLoop(std::string name, bool loop)
     * \brief Set the loop of a sound
     * \param name The name of the sound
     * \param loop The loop of the sound
     */
    void setSoundLoop(std::string name, bool loop)
    {
        audioEngine.setSoundLoop(name, loop);
    }

    /**
     * \fn void setSoundPitch(std::string name, float pitch)
     * \brief Set the pitch of a sound
     * \param name The name of the sound
     * \param pitch The pitch of the sound
     */
    void setSoundPitch(std::string name, float pitch)
    {
        audioEngine.setSoundPitch(name, pitch);
    }

    /**
     * \fn void createMusic(std::string name, std::string source)
     * \brief Create a music
     * \param name The name of the music
     * \param source The source of the music
     */
    void createMusic(std::string name, std::string source)
    {
        audioEngine.createMusic(name, source);
    }

    /**
     * \fn void playMusic(std::string name)
     * \brief Play a music
     * \param name The name of the music
     */
    void playMusic(std::string name)
    {
        audioEngine.playMusic(name);
    }

    /**
     * \fn void stopMusic(std::string name)
     * \brief Stop a music
     * \param name The name of the music
     */
    void stopMusic(std::string name)
    {
        audioEngine.stopMusic(name);
    }

    /**
     * \fn void pauseMusic(std::string name)
     * \brief Pause a music
     * \param name The name of the music
     */
    void pauseMusic(std::string name)
    {
        audioEngine.pauseMusic(name);
    }

    /**
     * \fn void resumeMusic(std::string name)
     * \brief Resume a music
     * \param name The name of the music
     */
    void resumeMusic(std::string name)
    {
        audioEngine.resumeMusic(name);
    }

    /**
     * \fn void setMusicVolume(std::string name, float volume)
     * \brief Set the volume of a music
     * \param name The name of the music
     * \param volume The volume of the music
     */
    void setMusicVolume(std::string name, float volume)
    {
        audioEngine.setMusicVolume(name, volume);
    }

    /**
     * \fn void setMusicLoop(std::string name, bool loop)
     * \brief Set the loop of a music
     * \param name The name of the music
     * \param loop The loop of the music
     */
    void setMusicLoop(std::string name, bool loop)
    {
        audioEngine.setMusicLoop(name, loop);
    }

    /**
     * \fn void setMusicPitch(std::string name, float pitch)
     * \brief Set the pitch of a music
     * \param name The name of the music
     * \param pitch The pitch of the music
     */
    void setMusicPitch(std::string name, float pitch)
    {
        audioEngine.setMusicPitch(name, pitch);
    }

  private:
    AAudioEngine& audioEngine;  /*!< The audio engine */
};