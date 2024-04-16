#pragma once
#include <cstddef>

#include "Registry.hpp"

/**
 * \enum SceneType
 * \brief Type of the scene
 */
enum SceneType {START, MENU, LOBBY, SETINGS, GAME, END, STAT, LOBBIES, CREATE_LOBBY, WAIT_IN_LOBBY, MULTIPLAYER};

/**
 * \class SceneManager
 * \brief A class that manage the scenes
 * Used to manage the scenes
 */
class SceneManager
{
  public:
    SceneManager() = default;  /*!< Default constructor */
    ~SceneManager() = default; /*!< Default destructor */

    SceneManager(
        SceneManager const&) = default; /*!< Default copy constructor */
    SceneManager(
        SceneManager&&) noexcept = default; /*!< Default move constructor */
    SceneManager& operator=(
        SceneManager const&) = default; /*!< Default copy assignment operator */
    SceneManager& operator=(
        SceneManager&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn SceneType getCurrentScene()
     * \brief Get the current scene
     * \return The current scene
     */
    SceneType getCurrentScene()
    {
        return currentScene;
    }

    /**
     * \fn void changeScene(SceneType type)
     * \brief Change the current scene
     * \param type The new scene
     */
    void changeScene(SceneType type)
    {
        currentScene = type;
        updated = true;
    }

    /**
     * \fn void setUpdate(bool update)
     * \brief Set the update of the scene
     * \param update The new update
     */
    void setUpdate(bool update)
    {
        updated = update;
    }

    /**
     * \fn [[nodiscard]] bool isUpdated() const
     * \brief Check if the scene is updated
     * \return True if the scene is updated, false otherwise
     */
    [[nodiscard]] bool isUpdated() const
    {
        return updated;
    }

    /**
     * \fn void setEntityPos(size_t pos)
     * \brief Set the entity position
     * \param pos The new position
     */
    void setEntityPos(size_t pos)
    {
        entityPos = pos;
    }

    /**
     * \fn [[nodiscard]] size_t getEntityPos() const
     * \brief Get the entity position
     * \return The entity position
     */
    [[nodiscard]] size_t getEntityPos() const
    {
        return entityPos;
    }

  private:
    SceneType currentScene = START; /*!< Current scene */
    bool updated = false;           /*!< If the scene is updated */
    size_t entityPos = 0;           /*!< Entity position */
};