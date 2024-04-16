#pragma once

/**
 * \class VelocityComponent
 * \brief Component that holds the velocity of an entity
 */
class VelocityComponent
{
  public:
    /**
     * \fn explicit VelocityComponent(float velocity = 1)
     * \brief Constructor
     * \param velocity The velocity of the entity
     */
    explicit VelocityComponent(float velocity = 1)
        : velocity(velocity){};
    ~VelocityComponent() = default; /*!< Default Constructor */

    VelocityComponent(VelocityComponent const&) = default; /*!< Default Copy Constructor */
    VelocityComponent(
        VelocityComponent&&) noexcept = default; /*!< Default Move Constructor */
    VelocityComponent& operator=(
        VelocityComponent const&) = default; /*!< Default Copy Assignment Operator */
    VelocityComponent& operator=(
        VelocityComponent&&) noexcept = default; /*!< Default Move Assignment Operator */

    /**
     * \fn float setVelocity(float velocity) const
     * \brief Set the velocity of the entity
     * \param velocity The velocity of the entity
     */
    void setVelocity(float velocity)
    {
        this->velocity = velocity;
    }

    /**
     * \fn [[nodiscard]] float getVelocity() const
     * \brief Get the velocity of the entity
     * \return The velocity of the entity
     */
    [[nodiscard]] float getVelocity() const
    {
        return velocity;
    }

  private:
    float velocity; /*!< The velocity of the entity */
};