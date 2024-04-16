#pragma once
#include "utils.hpp"

/**
 * \class DrawableComponent
 * \brief A component that handle a drawable object.
 * Used to create a drawable object
 */
class DrawableComponent
{
  public:
    /**
     * \fn DrawableComponent(std::string name, DrawableType type)
     * \brief Default constructor
     * \param name Name of the object from engine to draw
     * \param type Type of the object from engine to draw
     */
    DrawableComponent(std::string name, DrawableType type)
        : name(std::move(name))
        , type(type)
    {
    }

    ~DrawableComponent() = default; /*!< Default destructor */

    DrawableComponent(
        DrawableComponent const&) = default; /*!< Default copy constructor */
    DrawableComponent(DrawableComponent&&) noexcept = default; /*!< Default moveconstructor */
    DrawableComponent& operator=(
        DrawableComponent const&) = default; /*!< Default copy assignment operator */
    DrawableComponent& operator=(
        DrawableComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn [[nodiscard]] bool isEnable() const
     * \brief Check if the component is enable
     * \return true if the component is enable
     */
    [[nodiscard]] bool isEnable() const
    {
        return enable;
    }

    /**
     * \fn void setEnable()
     * \brief enable the component
     */
    void setEnable()
    {
        enable = true;
    }

    /**
     * \fn void setDisable()
     * \brief disable the component
     */
    void setDisable()
    {
        enable = false;
    }

    /**
     * \fn std::string& getName()
     * \brief Get the name of the object from engine to draw
     * \return The name of the object from engine to draw
     */
    std::string& getName()
    {
        return name;
    }

    /**
     * \fn [[nodiscard]] DrawableType getType() const
     * \brief Get the type of the object from engine to draw
     * \return The type of the object from engine to draw
     */
    [[nodiscard]] DrawableType getType() const
    {
        return type;
    }

    /**
     * \fn void changeDrawable(std::string& name, DrawableType type)
     * \brief Change the drawable object
     * \param name Name of the object from engine to draw
     * \param type Type of the object from engine to draw
     */
    void changeDrawable(std::string& name, DrawableType type)
    {
        this->name = name;
        this->type = type;
    }

  private:
    DrawableType type =
        UNKNOWN_TYPE;   /*!< Type of the object from engine to draw */
    std::string name;   /*!< Name of the object from engine to draw */
    bool enable = true; /*!< check if the component is enable */
};