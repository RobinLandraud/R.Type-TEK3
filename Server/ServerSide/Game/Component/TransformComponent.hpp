#pragma once
#include "utils.hpp"

/**
 * \class TransformComponent
 * \brief A component that holds the position, rotation and scale of an entity
 */
class TransformComponent
{
  public:
    /**
     * \fn explicit TransformComponent(Position3D_t pos = {0, 0, 0}, Size2D_t size = {1, 1}, float rot = 0)
     * \brief Constructor
     * \param pos The position of the entity
     * \param size The size of the entity
     * \param rot The rotation of the entity
     */
    explicit TransformComponent(
        Position3D_t pos = {0, 0, 0}, Size2D_t size = {1, 1}, float rot = 0)
        : size(size)
        , position(pos)
        , rotation(rot){};
    ~TransformComponent() = default; /*!< Default destructor */

    TransformComponent(TransformComponent const&) = default; /*!< Default copy constructor */
    TransformComponent(
        TransformComponent&&) noexcept = default; /*!< Default move constructor */
    TransformComponent& operator=(
        TransformComponent const&) = default; /*!< Default copy assignment operator */
    TransformComponent& operator=(
        TransformComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn void setPos(float posX, float posY, float posZ)
     * \brief Set the position of the entity
     * \param posX The x position of the entity
     * \param posY The y position of the entity
     * \param posZ The z position of the entity
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
     * \param x The x position to move to
     * \param y The y position to move to
     * \param z The z position to move to
     */
    void move(float x, float y, float z)
    {
        position.x += x;
        position.y += y;
        position.z += z;
    }

    /**
     * \fn void setRotation(float rot)
     * \brief Set the rotation of the entity
     * \param rotation The rotation of the entity
     */
    void setRotation(float rotation)
    {
        this->rotation = rotation;
    }

    /**
     * \fn void setSize(float height, float width)
     * \brief Set the size of the entity
     * \param height The height of the entity
     * \param width The width of the entity
     */
    void setSize(float height, float width)
    {
        size.height = height;
        size.width = width;
    }

    /**
     * \fn void rescale(float scale)
     * \brief Rescale the entity
     * \param scale The scale to apply to the entity
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
    Size2D_t size; /*!< The size of the entity */
    Position3D_t position; /*!< The position of the entity */
    float rotation; /*!< The rotation of the entity */
};