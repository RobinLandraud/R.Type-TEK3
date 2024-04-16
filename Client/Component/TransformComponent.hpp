#pragma once
#include "utils.hpp"

/**
 * \class TransformComponent
 * \brief A component that handle a transform.
 * Used to handle a transform
 */
class TransformComponent
{
  public:
    explicit TransformComponent(
        Position3D_t pos = {0, 0, 0}, Size2D_t size = {1, 1}, float rot = 0)
        : size(size)
        , position(pos)
        , rotation(rot){}; /*!< Constructor with position, size and rotation */
    ~TransformComponent() = default; /*!< Default destructor */

    TransformComponent(
        TransformComponent const&) = default; /*!< Default copy constructor */
    TransformComponent(
        TransformComponent&&) noexcept = default; /*!< Default move constructor */
    TransformComponent& operator=(
        TransformComponent const&) = default; /*!< Default copy assignment operator */
    TransformComponent& operator=(
        TransformComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn void setPosition(float posX, float posY, float posZ)
     * \brief Set the position of the entity
     * \param posX New position on X axis
     * \param posY New position on Y axis
     * \param posZ New position on Z axis
     */
    void setPosition(float posX, float posY, float posZ)
    {
        position.x = posX;
        position.y = posY;
        position.z = posZ;
    }

    /**
     * \fn void move(float x, float y, float z)
     * \brief Move the entity
     * \param x Move on X axis
     * \param y Move on Y axis
     * \param z Move on Z axis
     */
    void move(float x, float y, float z)
    {
        position.x += x;
        position.y += y;
        position.z += z;
    }

    /**
     * \fn void setRotation(float rotation)
     * \brief Set the rotation of the entity
     * \param rotation New rotation
     */
    void setRotation(float rotation)
    {
        this->rotation = rotation;
    }

    /**
     * \fn void setSize(float height, float width)
     * \brief Set the size of the entity
     * \param height New height
     * \param width New width
     */
    void setSize(float height, float width)
    {
        size.height = height;
        size.width = width;
    }

    /**
     * \fn void rescale(float scale)
     * \brief Rescale the entity
     * \param scale Scale to apply
     */
    void rescale(float scale)
    {
        size.height = size.height * scale;
        size.width = size.width * scale;
    }

    /**
     * \fn [[nodiscard]] Position3D_t getPosition() const
     * \brief Get the position of the entity
     * \return The position of the entity
     */
    [[nodiscard]] Position3D_t getPosition() const
    {
        return position;
    }

    /**
     * \fn [[nodiscard]] float getRotation() const
     * \brief Get the rotation of the entity
     * \return The rotation of the entity
     */
    [[nodiscard]] float getRotation() const
    {
        return rotation;
    }

    /**
     * \fn [[nodiscard]] Size2D_t getSize() const
     * \brief Get the size of the entity
     * \return The size of the entity
     */
    [[nodiscard]] Size2D_t getSize() const
    {
        return size;
    }

  private:
    Size2D_t size;         /*!< The size of the entity */
    Position3D_t position; /*!< The position of the entity */
    float rotation;        /*!< The rotation of the entity */
};