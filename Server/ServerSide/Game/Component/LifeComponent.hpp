/**
 * \class LifeComponent
 * \brief Class that handle the life of a component
 */
class LifeComponent
{
  public:
    LifeComponent() = default; /*!< Default constructor */

    /**
     * \fn explicit LifeComponent(int initLife)
     * \brief Constructor
     * \param initLife
     */
    explicit LifeComponent(int initLife)
        : life(initLife){};
    ~LifeComponent() = default; /*!< Default destructor */

    LifeComponent(LifeComponent const&) = default; /*!< Default copy constructor */
    LifeComponent(LifeComponent&&) noexcept = default; /*!< Default move constructor */
    LifeComponent& operator=(
        LifeComponent const&) = default; /*!< Default copy assignment operator */
    LifeComponent& operator=(
        LifeComponent&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn void setLife(int newLife)
     * \brief Set the life of the component
     * \param newLife New life of the component
     */
    void setLife(int newLife)
    {
        life = newLife;
    };

    /**
     * \fn void damage(int damage)
     * \brief Damage the component
     * \param damage Damage to apply to the component
     */
    void damage(int damage)
    {
        life = life - damage;
    }

    /**
     * \fn void heal(int heal)
     * \brief Heal the component
     * \param heal Heal to apply to the component
     */
    void heal(int health)
    {
        life = life + health;
    }

    /**
     * \fn [[nodiscard]] int getLife() const
     * \brief Get the life of the component
     * \return Life of the component
     */
    [[nodiscard]] int getLife() const
    {
        return life;
    };

  private:
    int life = 1; /*!< Life of the component */
};