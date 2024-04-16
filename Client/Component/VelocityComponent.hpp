#pragma once

/**
 * \class VelocityComponent
 * \brief A component that handle a velocity.
 * Used to handle a velocity
 */
class VelocityComponent
{
  public:
    explicit VelocityComponent(float velocity = 1)
        : velocity(velocity){};     /*!< Constructor with velocity */
    ~VelocityComponent() = default; /*!< Default destructor */

    VelocityComponent(
        VelocityComponent const&) = default; /*!< Default copy constructor */
    VelocityComponent(VelocityComponent&&) noexcept = default; /*!< Default move constructor */
    VelocityComponent& operator=(
        VelocityComponent const&) = default; /*!< Default copy assignment operator */
    VelocityComponent& operator=(
        VelocityComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn void setVelocity(float velocity)
     * \brief Set the velocity of the entity
     * \param velocity New velocity
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