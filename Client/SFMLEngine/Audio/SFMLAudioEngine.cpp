#include "SFMLAudioEngine.hpp"

/**
 * \fn int SFMLAudioEngine::createSound(std::string name, std::string source)
 * \brief Create a sound
 * \param name The name of the sound
 * \param source The source of the sound
 * \return The id of the sound
 */
int SFMLAudioEngine::createSound(std::string name, std::string source)
{
    if (soundBuffers.find(name) != soundBuffers.end())
        return 1;
    if (!soundBuffers[name].loadFromFile(source))
        return 2;
    sounds[name].setBuffer(soundBuffers[name]);
    return 0;
}

/**
 * \fn void SFMLAudioEngine::playSound(std::string name)
 * \brief Play a sound
 * \param name The name of the sound
 */
void SFMLAudioEngine::playSound(std::string name)
{
    if (sounds.find(name) != sounds.end())
        sounds[name].play();
}


/**
 * \fn void SFMLAudioEngine::stopSound(std::string name)
 * \brief Stop a sound
 * \param name The name of the sound
 */
void SFMLAudioEngine::stopSound(std::string name)
{
    if (sounds.find(name) != sounds.end())
        sounds[name].stop();
}


/**
 * \fn void SFMLAudioEngine::pauseSound(std::string name)
 * \brief Pause a sound
 * \param name The name of the sound
 */
void SFMLAudioEngine::pauseSound(std::string name)
{
    if (sounds.find(name) != sounds.end())
        sounds[name].pause();
}

/**
 * \fn void SFMLAudioEngine::resumeSound(std::string name)
 * \brief Resume a sound
 * \param name The name of the sound
 */
void SFMLAudioEngine::resumeSound(std::string name)
{
    if (sounds.find(name) != sounds.end())
        sounds[name].play();
}

/**
 * \fn void SFMLAudioEngine::setSoundVolume(std::string name, float volume)
 * \brief Set the volume of a sound
 * \param name The name of the sound
 * \param volume The volume of the sound
 */
void SFMLAudioEngine::setSoundVolume(std::string name, float volume)
{
    if (sounds.find(name) != sounds.end())
        sounds[name].setVolume(volume);
}

/**
 * \fn void SFMLAudioEngine::setSoundLoop(std::string name, bool loop)
 * \brief Set the loop of a sound
 * \param name The name of the sound
 * \param loop The loop of the sound
 */
void SFMLAudioEngine::setSoundLoop(std::string name, bool loop)
{
    if (sounds.find(name) != sounds.end())
        sounds[name].setLoop(loop);
}

/**
 * \fn void SFMLAudioEngine::setSoundPitch(std::string name, float pitch)
 * \brief Set the pitch of a sound
 * \param name The name of the sound
 * \param pitch The pitch of the sound
 */
void SFMLAudioEngine::setSoundPitch(std::string name, float pitch)
{
    if (sounds.find(name) != sounds.end())
        sounds[name].setPitch(pitch);
}

/**
 * \fn int SFMLAudioEngine::createMusic(std::string name, std::string source)
 * \brief Create a music
 * \param name The name of the music
 * \param source The source of the music
 * \return The id of the music
 */
int SFMLAudioEngine::createMusic(std::string name, std::string source)
{
    if (musics.find(name) != musics.end())
        return 1;
    if (!musics[name].openFromFile(source))
        return 2;
    return 0;
}

/**
 * \fn void SFMLAudioEngine::playMusic(std::string name)
 * \brief Play a music
 * \param name The name of the music
 */
void SFMLAudioEngine::playMusic(std::string name)
{
    if (musics.find(name) != musics.end())
        musics[name].play();
}

/**
 * \fn void SFMLAudioEngine::stopMusic(std::string name)
 * \brief Stop a music
 * \param name The name of the music
 */
void SFMLAudioEngine::stopMusic(std::string name)
{
    if (musics.find(name) != musics.end())
        musics[name].stop();
}

/**
 * \fn void SFMLAudioEngine::pauseMusic(std::string name)
 * \brief Pause a music
 * \param name The name of the music
 */
void SFMLAudioEngine::pauseMusic(std::string name)
{
    if (musics.find(name) != musics.end())
        musics[name].pause();
}

/**
 * \fn void SFMLAudioEngine::resumeMusic(std::string name)
 * \brief Resume a music
 * \param name The name of the music
 */
void SFMLAudioEngine::resumeMusic(std::string name)
{
    if (musics.find(name) != musics.end())
        musics[name].play();
}

/**
 * \fn void SFMLAudioEngine::setMusicVolume(std::string name, float volume)
 * \brief Set the volume of a music
 * \param name The name of the music
 * \param volume The volume of the music
 */
void SFMLAudioEngine::setMusicVolume(std::string name, float volume)
{
    if (musics.find(name) != musics.end())
        musics[name].setVolume(volume);
}

/**
 * \fn void SFMLAudioEngine::setMusicLoop(std::string name, bool loop)
 * \brief Set the loop of a music
 * \param name The name of the music
 * \param loop The loop of the music
 */
void SFMLAudioEngine::setMusicLoop(std::string name, bool loop)
{
    if (musics.find(name) != musics.end())
        musics[name].setLoop(loop);
}

/**
 * \fn void SFMLAudioEngine::setMusicPitch(std::string name, float pitch)
 * \brief Set the pitch of a music
 * \param name The name of the music
 * \param pitch The pitch of the music
 */
void SFMLAudioEngine::setMusicPitch(std::string name, float pitch)
{
    if (musics.find(name) != musics.end())
        musics[name].setPitch(pitch);
}