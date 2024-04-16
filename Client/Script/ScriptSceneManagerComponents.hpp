#pragma once

#include "SceneManager.hpp"

/**
 * \class ScriptSceneManagerComponents
 * 
 */
class ScriptSceneManagerComponents
{
  public:
    /**
     * \fn ScriptSceneManagerComponents(registry& reg): reg(reg)
     * \brief The constructor of the class
     * \param reg The registry
     */
    ScriptSceneManagerComponents(registry& reg)
        : reg(reg){};
    ~ScriptSceneManagerComponents() = default;

    /**
     * \fn void add(size_t ent_id)
     * \brief Add a component to the entity
     * \param ent_id The entity id
     */
    void add(size_t ent_id)
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<SceneManager>(entity.value(), SceneManager());
    }

    /**
     * \fn size_t size()
     * \brief Get the number of script scene manager components
     * \return The number of script scene manager components
     */
    size_t size()
    {
        return reg.get_components<SceneManager>().size();
    }

    /**
     * \fn ServerPropertiesComponent& at(size_t index)
     * \brief Get a script scene manager component at a given index
     * \param index The index
     * \return The script scene manager component
     */
    SceneManager& at(size_t index)
    {
        return reg.get_components<SceneManager>()[index].value();
    }

    /**
     * \fn bool exists(size_t index)
     * \brief Check if a script scene manager exists at a given index
     * \param index The index
     * \return True if the script scene manager exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<SceneManager>().exists(index);
    }

    /**
     * \fn SceneType getCurrentSceneAt(size_t index)
     * \brief Get the current scene at a given index
     * \param index The index
     * \return The current scene
     */
    SceneType getCurrentSceneAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                .value()
                .getCurrentScene();
        }
        return SceneType::END;
    }

    /**
     * \fn void changeSceneAt(size_t index, SceneType type)
     * \brief Change the scene at a given index
     * \param index The index
     * \param type The scene type
     */
    void changeSceneAt(size_t index, SceneType type)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            reg.get_components<SceneManager>()[index].value().changeScene(type);
        }
    }

    /**
     * \fn void setUpdateAt(size_t index, bool update)
     * \brief Set the update at a given index
     * \param index The index
     * \param update The update
     */
    void setUpdateAt(size_t index, bool update)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            reg.get_components<SceneManager>()[index].value().setUpdate(update);
        }
    }

    /**
     * \fn bool isUpdatedAt(size_t index)
     * \brief Check if the scene manager is updated at a given index
     * \param index The index
     * \return True if the scene manager is updated, false otherwise
     */
    bool isUpdatedAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                .value()
                .isUpdated();
        }
        return false;
    }

    /**
     * \fn void setEntityPosAt(size_t index, size_t pos)
     * \brief Set the entity position at a given index
     * \param index The index
     * \param pos The position
     */
    void setEntityPosAt(size_t index, size_t pos)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            reg.get_components<SceneManager>()[index].value().setEntityPos(pos);
        }
    }

    /**
     * \fn size_t getEntityPosAt(size_t index)
     * \brief Get the entity position at a given index
     * \param index The index
     * \return The entity position
     */
    size_t getEntityPosAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                .value()
                .getEntityPos();
        }
        return 0;
    }

    /**
     * \fn bool isStartAt(size_t index)
     * \brief Check if the scene manager is started at a given index
     * \param index The index
     * \return True if the scene manager is started, false otherwise
     */
    bool isStartAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                       .value()
                       .getCurrentScene()
                   == START;
        }
        return false;
    }

    /**
     * \fn bool isMenuAt(size_t index)
     * \brief Check if the scene manager is in the menu at a given index
     * \param index The index
     * \return True if the scene manager is in the menu, false otherwise
     */
    bool isMenuAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                       .value()
                       .getCurrentScene()
                   == MENU;
        }
        return false;
    }

    /**
     * \fn bool isSettingAt(size_t index)
     * \brief Check if the scene manager is in the settings at a given index
     * \param index The index
     * \return True if the scene manager is in the settings, false otherwise
     */
    bool isSettingsAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                       .value()
                       .getCurrentScene()
                   == SETINGS;
        }
        return false;
    }

    /**
     * \fn bool isGameAt(size_t index)
     * \brief Check if the scene manager is in the game at a given index
     * \param index The index
     * \return True if the scene manager is in the game, false otherwise
     */
    bool isGameAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                       .value()
                       .getCurrentScene()
                   == GAME;
        }
        return false;
    }

    /**
     * \fn bool isEndAt(size_t index)
     * \brief Check if the scene manager is in the end at a given index
     * \param index The index
     * \return True if the scene manager is in the end, false otherwise
     */
    bool isEndAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                       .value()
                       .getCurrentScene()
                   == END;
        }
        return false;
    }

    /**
     * \fn bool isStatAt(size_t index)
     * \brief Check if the scene manager is in the stats at a given index
     * \param index The index
     * \return True if the scene manager is in the stats, false otherwise
     */
    bool isStatAt(size_t index)
    {
        if (reg.get_components<SceneManager>().exists(index)) {
            return reg.get_components<SceneManager>()[index]
                       .value()
                       .getCurrentScene()
                   == SETINGS;
        }
        return false;
    }

  private:
    registry& reg; /**< The registry */
};