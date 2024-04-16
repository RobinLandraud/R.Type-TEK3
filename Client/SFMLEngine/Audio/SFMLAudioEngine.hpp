#pragma once
#include <unordered_map>

#include "AAudioEngine.hpp"
#include "SFML/Audio.hpp"

/**
 * \class SFMLAudioEngine
 * \brief A class that handle the audio.
 * Used to play audio
 */
class SFMLAudioEngine : public AAudioEngine
{
  public:
    SFMLAudioEngine() = default;  /*!< Default constructor */
    ~SFMLAudioEngine() override = default;  /*!< Default destructor */

    /**
     * \fn int createSound(std::string name, std::string source) override;
     * \brief Create a sound
     * \param name The name of the sound
     * \param source The source of the sound
     * \return The id of the sound
     */
    int createSound(std::string name, std::string source) override;

    /**
     * \fn void playSound(std::string name) override;
     * \brief Play a sound
     * \param name The name of the sound
     */
    void playSound(std::string name) override;

    /**
     * \fn void stopSound(std::string name) override;
     * \brief Stop a sound
     * \param name The name of the sound
     */
    void stopSound(std::string name) override;

    /**
     * \fn void pauseSound(std::string name) override;
     * \brief Pause a sound
     * \param name The name of the sound
     */
    void pauseSound(std::string name) override;

    /**
     * \fn void resumeSound(std::string name) override;
     * \brief Resume a sound
     * \param name The name of the sound
     */
    void resumeSound(std::string name) override;

    /**
     * \fn void setSoundVolume(std::string name, float volume) override;
     * \brief Set the volume of a sound
     * \param name The name of the sound
     * \param volume The volume of the sound
     */
    void setSoundVolume(std::string name, float volume) override;

    /**
     * \fn void setSoundLoop(std::string name, bool loop) override;
     * \brief Set the loop of a sound
     * \param name The name of the sound
     * \param loop The loop of the sound
     */
    void setSoundLoop(std::string name, bool loop) override;

    /**
     * \fn void setSoundPitch(std::string name, float pitch) override;
     * \brief Set the pitch of a sound
     * \param name The name of the sound
     * \param pitch The pitch of the sound
     */
    void setSoundPitch(std::string name, float pitch) override;

    /**
     * \fn int createMusic(std::string name, std::string source) override;
     * \brief Create a music
     * \param name The name of the music
     * \param source The source of the music
     * \return The id of the music
     */
    int createMusic(std::string name, std::string source) override;

    /**
     * \fn void playMusic(std::string name) override;
     * \brief Play a music
     * \param name The name of the music
     */
    void playMusic(std::string name) override;

    /**
     * \fn void stopMusic(std::string name) override;
     * \brief Stop a music
     * \param name The name of the music
     */
    void stopMusic(std::string name) override;

    /**
     * \fn void pauseMusic(std::string name) override;
     * \brief Pause a music
     * \param name The name of the music
     */
    void pauseMusic(std::string name) override;

    /**
     * \fn void resumeMusic(std::string name) override;
     * \brief Resume a music
     * \param name The name of the music
     */
    void resumeMusic(std::string name) override;

    /**
     * \fn void setMusicVolume(std::string name, float volume) override;
     * \brief Set the volume of a music
     * \param name The name of the music
     * \param volume The volume of the music
     */
    void setMusicVolume(std::string name, float volume) override;

    /**
     * \fn void setMusicLoop(std::string name, bool loop) override;
     * \brief Set the loop of a music
     * \param name The name of the music
     * \param loop The loop of the music
     */
    void setMusicLoop(std::string name, bool loop) override;

    /**
     * \fn void setMusicPitch(std::string name, float pitch) override;
     * \brief Set the pitch of a music
     * \param name The name of the music
     * \param pitch The pitch of the music
     */
    void setMusicPitch(std::string name, float pitch) override;

  private:
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;  /*!< The sound buffers */
    std::unordered_map<std::string, sf::Sound> sounds;  /*!< The sounds */
    std::unordered_map<std::string, sf::Music> musics;  /*!< The musics */
};