#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

#include "ASocket.hpp"
#include "Registry.hpp"

/**
 * \class ExecComponent
 * \brief A component that handle a clock.
 * Used to execute a function
 */
class ExecComponent
{
  public:
    ExecComponent() = default;  /*!< Default constructor */
    ~ExecComponent() = default; /*!< Default destructor */

    ExecComponent(
        ExecComponent const&) = default; /*!< Default copy constructor */
    ExecComponent(
        ExecComponent&&) noexcept = default; /*!< Default move constructor */
    ExecComponent& operator=(
        ExecComponent const&) = default; /*!< Default copy assignment operator
                                          */
    ExecComponent& operator=(
        ExecComponent&&) noexcept = default; /*!< Default move assignment
                                                operator */

    /**
     * \fn void addFunction(std::function<void(size_t, registry&)> &&action)
     * \brief Add an event to the component
     * \param name Name of the event
     * \param func Function to execute
     */
    void addFunction(std::function<void(size_t, registry&, ASocket&)>&& action)
    {
        functions.push_back(std::move(action));
    }

    /**
     * \fn std::vector<std::function<void(size_t, registry&)>> &getFunctions()
     * \brief Get the functions of the component
     * \return The functions of the component
     */
    std::vector<std::function<void(size_t, registry&, ASocket&)>>&
    getFunctions()
    {
        return functions;
    }

  private:
    std::vector<std::function<void(size_t, registry&, ASocket&)>> functions =
        {}; /*!< Functions to execute */
};