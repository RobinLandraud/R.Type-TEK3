#pragma once
#include <functional>
#include <unordered_map>
#include <vector>

#include "AEventEngine.hpp"
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
        ExecComponent const&) = default; /*!< Default copy assignment operator */
    ExecComponent& operator=(
        ExecComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn void addFunction(std::function<void(size_t, registry&)>&& action)
     * \brief Add a function to the list of function to execute
     * \param name the name of the function
     * \param func the function to execute
     */
    void addFunction(std::function<void(size_t, registry&, AEngine&)>&& action)
    {
        functions.push_back(std::move(action));
    }

    /**
     * \fn std::vector<std::function<void(size_t, registry&)>>& getFunctions()
     * \brief Get the list of functions to execute
     * \return the list of functions to execute
     */
    std::vector<std::function<void(size_t, registry&, AEngine&)>>& getFunctions()
    {
        return functions;
    }

  private:
    std::vector<std::function<void(size_t, registry&, AEngine&)>> functions =
        {}; /*!< The list of functions to execute */
};