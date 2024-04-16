#include <cstddef>
#include <utility>
#include <vector>

#include "Registry.hpp"
#include "User.hpp"

#pragma once

/**
 * \enum SceneManager
 * \brief The types of the scene manager
 */
enum SceneType { START, MENU, LOBBY, SETINGS, GAME, END, STAT};

/**
 * \class SceneManager
 * \brief Manages the scenes of the game
 */
class SceneManager
{
  public:
    SceneManager() = default; /*!< Default constructor */
    ~SceneManager() = default; /*!< Default destructor */

    SceneManager(SceneManager const&) = default; /*!< Default copy constructor */
    SceneManager(SceneManager&&) noexcept = default; /*!< Default move constructor */
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
     * \fn void changeScene(SceneType scene)
     * \brief change the current scene
     * \param type The new scene
     */
    void changeScene(SceneType type)
    {
        currentScene = type;
        updated = true;
    }

    /**
     * \fn void setUpdated(bool update)
     * \brief Set the updated state
     * \param update The new updated state
     */
    void setUpdate(bool update)
    {
        updated = update;
    }

    /**
     * \fn [[nodiscard]] bool isUpdated()
     * \brief Get the updated state
     * \return True if the scene has been updated, False otherwise
     */
    [[nodiscard]] bool isUpdated() const
    {
        return updated;
    }

    /**
     * \fn void setEntityPos(size_t pos)
     * \brief Set the entity position
     * \param pos The new entity position
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
    SceneType currentScene = LOBBY; /*!< The current scene */
    bool updated = false; /*!< The updated state */
    size_t entityPos = 0; /*!< The entity position */
};