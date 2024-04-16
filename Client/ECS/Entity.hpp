/**
 * \class Entity
 * \brief A entity class.
 * Used to create an entity
 */
class Entity
{
  public:
    /**
     * \fn explicit Entity(size_t p_id) noexcept
     * \brief Default constructor
     * \param p_id Id of the entity
     */
    explicit Entity(size_t p_id) noexcept
        : id{p_id}
    {
    }

    Entity(Entity const& other) noexcept = default; /*!< Default copy constructor */
    Entity(Entity&& other) noexcept = default; /*!< Default move constructor */
    Entity& operator=(
        Entity const& other) noexcept = default; /*!< Default copy assignment operator */
    Entity& operator=(
        Entity&& other) noexcept = default; /*!< Default move assignment operator */
    ~Entity() noexcept = default;           /*!< Default destructor */

    /**
     * \fn operator size_t() const
     * \brief Get the Id of the entity
     * \return The id of the entity
     */
    operator size_t() const
    {
        return this->id;
    }
    size_t id; /*!< Id of the entity */

  private:
};