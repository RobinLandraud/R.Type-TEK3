#pragma once
#include <optional>

#include "TransformComponent.hpp"
#include "utils.hpp"

/**
 * \class CollideComponent
 * \brief A component that handle a collision.
 * Used to create a collision box
 */
class CollideComponent
{
  public:
    /**
     * \fn explicit CollideComponent(float width = 1, float height = 1, float deltaX = 0, float deltaY = 0)
     * \brief Constructor of the CollideComponent
     * \param width Width of the collision box
     * \param height Height of the collision box
     * \param deltaX X position of the collision box relative to the entity
     * \param deltaY Y position of the collision box relative to the entity
     */
    explicit CollideComponent(
        float width = 1, float height = 1, float deltaX = 0, float deltaY = 0)
        : box({width, height})
        , deltaPos({deltaX, deltaY}){};

    ~CollideComponent() = default; /*!< Default destructor */

    CollideComponent(
        CollideComponent const&) = default; /*!< Default copy constructor */
    CollideComponent(
        CollideComponent&&) noexcept = default; /*!< Default move constructor */
    CollideComponent& operator=(
        CollideComponent const&) = default; /*!< Default copy assignment operator */
    CollideComponent& operator=(
        CollideComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn [[nodiscard]] bool isEnable() const
     * \brief Check if the collision is enable
     * \return true if the collision is enable
     */
    [[nodiscard]] bool isEnable() const
    {
        return enable;
    };

    /**
     * \fn [[nodiscard]] CollideBox getCollideBox() const
     * \brief Get the collision box
     * \return The collision box
     */
    [[nodiscard]] CollideBox getCollideBox() const
    {
        return box;
    };

    /**
     * \fn bool isCollide(TransformComponent& transform, CollideComponent& other, TransformComponent& otherTransform)
     * \brief Check if the entity collide with another entity
     * \param transform The transform of the entity
     * \param other The other entity
     * \param otherTransform The transform of the other entity
     * \return true if the entity collide with the other entity, false otherwise
     */
    bool isCollide(TransformComponent& transform,
        CollideComponent& other,
        TransformComponent& otherTransform)
    {
        if (!enable || !other.isEnable()) {
            return false;
        }
        auto pos = transform.getPosition();
        auto otherPos = otherTransform.getPosition();
        auto otherSize = other.getCollideBox();
        auto delta = deltaPos;
        auto otherDelta = other.getDeltaPos();
        return (
            pos.x + delta.x < otherPos.x + otherSize.width + otherDelta.x
            && pos.x + delta.x + box.width > otherPos.x + otherDelta.x
            && pos.y + delta.y < otherPos.y + otherSize.height + otherDelta.y
            && pos.y + delta.y + box.height > otherPos.y + otherDelta.y);
    }

    /**
     * \fn bool isCollide(TransformComponent& transform, float x, float y)
     * \brief Check if the entity collide with a point
     * \param transform The transform of the entity
     * \param x X position of the point
     * \param y Y position of the point
     * \return true if the entity collide with the point, false otherwise
     */
    bool isCollide(TransformComponent& transform, float x, float y)
    {
        if (!enable) {
            return false;
        }
        auto pos = transform.getPosition();
        auto delta = deltaPos;
        return (pos.x + delta.x < x && pos.x + delta.x + box.width > x
                && pos.y + delta.y < y && pos.y + delta.y + box.height > y);
    }

    /**
     * \fn void setCollideBox(CollideBox box)
     * \brief Set the collision box
     * \param box The collision box
     */
    void setCollideBox(CollideBox box)
    {
        this->box = box;
    };

    /**
     * \fn void setEnable(bool enable)
     * \brief Set the collision enable
     * \param enable The collision enable
     */
    void setEnable(bool enable)
    {
        this->enable = enable;
    };

    /**
     * \fn [[nodiscard]] Position2D_t getDeltaPos() const
     * \brief Get the delta position of the collision box
     * \return The delta position of the collision box
     */
    [[nodiscard]] Position2D_t getDeltaPos() const
    {
        return deltaPos;
    }

  private:
    CollideBox box;        /*!< The collision box */
    Position2D_t deltaPos; /*!< The delta position of the collision box relative to the entity */
    bool enable = true;    /*!< check if the collision is enable */
};