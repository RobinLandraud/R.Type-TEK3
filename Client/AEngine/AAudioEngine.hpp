#include <iostream>

#pragma once

/**
 * \class AAudioEngine
 * \brief Abstract class for audio engine.
 * Used to play sound and music
 */
class AAudioEngine
{
  public:
    AAudioEngine() = default;          /*!< Default constructor */
    virtual ~AAudioEngine() = default; /*!< Default destructor */

    /**
     * \fn virtual int AAudioEngine::createSound(std::string name, std::string
     * source) = 0 \brief Create a sound \param name Name of the sound \param
     * source Source of the sound
     */
    virtual int createSound(std::string name, std::string source) = 0;

    /**
     * \fn virtual void AAudioEngine::playSound(std::string name) = 0
     * \brief Play a sound
     * \param name Name of the sound
     */
    virtual void playSound(std::string name) = 0;

    /**
     * \fn virtual void AAudioEngine::stopSound(std::string name) = 0
     * \brief Stop a sound
     * \param name Name of the sound
     */
    virtual void stopSound(std::string name) = 0;

    /**
     * \fn virtual void AAudioEngine::pauseSound(std::string name) = 0
     * \brief Pause a sound
     * \param name Name of the sound
     */
    virtual void pauseSound(std::string name) = 0;

    /**
     * \fn virtual void AAudioEngine::resumeSound(std::string name) = 0
     * \brief Resume a sound
     * \param name Name of the sound
     */
    virtual void resumeSound(std::string name) = 0;

    /**
     * \fn virtual void setSoundVolume(std::string name, float volume) = 0
     * \brief Set the volume of a sound
     * \param name Name of the sound
     * \param volume Volume of the sound
     */
    virtual void setSoundVolume(std::string name, float volume) = 0;

    /**
     * \fn virtual void setSoundLoop(std::string name, bool loop) = 0
     * \brief Set the loop of a sound
     * \param name Name of the sound
     * \param loop Enable or disable the loop
     */
    virtual void setSoundLoop(std::string name, bool loop) = 0;

    /**
     * \fn virtual void setSoundPitch(std::string name, float pitch) = 0
     * \brief Set the pitch of a sound
     * \param name Name of the sound
     * \param pitch Pitch of the sound
     */
    virtual void setSoundPitch(std::string name, float pitch) = 0;

    /**
     * \fn virtual int createMusic(std::string name, std::string source) = 0
     * \brief Create a music
     * \param name Name of the music
     * \param source Source of the music
     * \return Error code
     */
    virtual int createMusic(std::string name, std::string source) = 0;

    /**
     * \fn virtual void playMusic(std::string name) = 0
     * \brief Play a music
     * \param name Name of the music
     */
    virtual void playMusic(std::string name) = 0;

    /**
     * \fn virtual void stopMusic(std::string name) = 0
     * \brief Stop a music
     * \param name Name of the music
     */
    virtual void stopMusic(std::string name) = 0;

    /**
     * \fn virtual void pauseMusic(std::string name) = 0
     * \brief Pause a music
     * \param name Name of the music
     */
    virtual void pauseMusic(std::string name) = 0;

    /**
     * \fn virtual void resumeMusic(std::string name) = 0
     * \brief Resume a music
     * \param name Name of the music
     */
    virtual void resumeMusic(std::string name) = 0;

    /**
     * \fn virtual void setMusicVolume(std::string name, float volume) = 0
     * \brief Set the volume of a music
     * \param name Name of the music
     * \param volume Volume of the music
     */
    virtual void setMusicVolume(std::string name, float volume) = 0;

    /**
     * \fn virtual void setMusicLoop(std::string name, bool loop) = 0
     * \brief Set the loop of a music
     * \param name Name of the music
     * \param loop Enable or disable the loop
     */
    virtual void setMusicLoop(std::string name, bool loop) = 0;

    /**
     * \fn virtual void setMusicPitch(std::string name, float pitch) = 0
     * \brief Set the pitch of a music
     * \param name Name of the music
     * \param pitch Pitch of the music
     */
    virtual void setMusicPitch(std::string name, float pitch) = 0;
};