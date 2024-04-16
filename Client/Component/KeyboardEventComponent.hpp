#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

#include "AEventEngine.hpp"
#include "Registry.hpp"

/**
 * \class KeyboardEventComponent
 * \brief A component that handle a controllable object.
 * Used to create a controllable object
 */
class KeyboardEventComponent
{
  public:
    KeyboardEventComponent() = default;  /*!< Default constructor */
    ~KeyboardEventComponent() = default; /*!< Default destructor */

    KeyboardEventComponent(
        KeyboardEventComponent const&) = default; /*!< Copy constructor */
    KeyboardEventComponent(
        KeyboardEventComponent&&) noexcept = default; /*!< Move constructor */
    KeyboardEventComponent& operator=(
        KeyboardEventComponent const&) = default; /*!< Copy assignment operator */
    KeyboardEventComponent& operator=(
        KeyboardEventComponent&&) noexcept = default; /*!< Move assignment operator */

    /**
     * \fn void addAction(Key key, std::function<void(size_t, registry&, AEngine&, ServerToken&)>&& action)
     * \brief Add a function to the list of function to execute
     * \param key the key to bind the action to
     * \param action the action to execute
     */
    void addAction(Key key,
        std::function<void(size_t, registry&, AEngine&, ServerToken&)>&& action)
    {
        actions[key].push_back(std::move(action));
    }

    /**
     * \fn void addDefaultAction(std::function<void(size_t, registry&, AEngine&, ServerToken&)>&& action)
     * \brief Add a function to the list of function to execute
     * \param action the action to execute
     */
    void addDefaultAction(
        std::function<void(size_t, registry&, AEngine&, ServerToken&)>&& action)
    {
        defaultAction.push_back(std::move(action));
    }

    /**
     * \fn std::vector<std::function<void(size_t, registry&, AEngine&, ServerToken&)>>& getActionsByKey(Key key)
     * \brief Get the list of functions to execute
     * \param key the key to get the actions from
     * \return the list of functions to execute
     */
    std::vector<std::function<void(size_t, registry&, AEngine&, ServerToken&)>>&
    getActionsByKey(Key key)
    {
        if (actions.find(key) != actions.end()) {
            return actions[key];
        }
        return defaultAction;
    }

  private:
    std::unordered_map<Key,
        std::vector<
            std::function<void(size_t, registry&, AEngine&, ServerToken&)>>>
        actions; /*!< Actions binded to a key */
    std::vector<std::function<void(size_t, registry&, AEngine&, ServerToken&)>>
        defaultAction = {}; /*!< Default action */
};