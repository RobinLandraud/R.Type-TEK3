#pragma once
#include <functional>
#include <unordered_map>

#include "AEventEngine.hpp"
#include "Registry.hpp"

/**
 * \class MouseEventComponent
 * \brief A component that handle a button.
 * Used to create a button
 */
class MouseEventComponent
{
  public:
    MouseEventComponent() = default;    /*!< Default constructor */

    /**
     * \fn MouseEventComponent(
        std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onClick,
        std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onRelease,
        std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onHover)
     * \brief Constructor
     * \param onClick the function to execute when the button is clicked
     * \param onRelease the function to execute when the button is released
     * \param onHover the function to execute when the button is hovered
     */
    MouseEventComponent(
        std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onClick,
        std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onRelease,
        std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onHover)
        : onClick(std::move(onClick))
        , onRelease(std::move(onRelease))
        , onHover(std::move(onHover))
    {
    }
    ~MouseEventComponent() = default; /*!< Default destructor */

    MouseEventComponent(
        MouseEventComponent const&) = default; /*!< Copy constructor */
    MouseEventComponent(
        MouseEventComponent&&) noexcept = default; /*!< Move constructor */
    MouseEventComponent& operator=(
        MouseEventComponent const&) = default; /*!< Copy assignment operator */
    MouseEventComponent& operator=(
        MouseEventComponent&&) noexcept = default; /*!< Move assignment operator */

    /**
     * \fn void setOnClick(std::function<void(size_t, registry&, AEngine&, ServerToken& serverToken)>&& onClick)
     * \brief Set the function to execute when the button is clicked
     * \param onClick the function to execute when the button is clicked
     */
    void setOnClick(std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onClick)
    {
        this->onClick = std::move(onClick);
    }

    /**
     * \fn void setOnRelease(std::function<void(size_t, registry&, AEngine&, ServerToken& serverToken)>&& onRelease)
     * \brief Set the function to execute when the button is released
     * \param onRelease the function to execute when the button is released
     */
    void setOnRelease(std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onRelease)
    {
        this->onRelease = std::move(onRelease);
    }

    /**
     * \fn void setOnHover(std::function<void(size_t, registry&, AEngine&, ServerToken& serverToken)>&& onHover)
     * \brief Set the function to execute when the button is hovered
     * \param onHover the function to execute when the button is hovered
     */
    void setOnHover(std::function<void(
            size_t, registry&, AEngine&, ServerToken& serverToken)>&& onHover)
    {
        this->onHover = std::move(onHover);
    }

    std::function<void(size_t, registry&, AEngine&, ServerToken& serverToken)>
        onClick = [](size_t, registry&, AEngine&, ServerToken& serverToken) {
            return;
        }; /*!< Function called when the button is clicked */
    std::function<void(size_t, registry&, AEngine&, ServerToken& serverToken)>
        onRelease = [](size_t, registry&, AEngine&, ServerToken& serverToken) {
            return;
        }; /*!< Function to call when the button is released */
    std::function<void(size_t, registry&, AEngine&, ServerToken& serverToken)>
        onHover = [](size_t, registry&, AEngine&, ServerToken& serverToken) {
            return;
        }; /*!< Function to call when the mouse is on the button */
};