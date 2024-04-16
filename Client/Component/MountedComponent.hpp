

class MountedComponent
{
  public:
    explicit MountedComponent(int entityId)
        : mountOnId(entityId){};   /*!< Default constructor */
    ~MountedComponent() = default; /*!< Default destructor */

    MountedComponent(
        MountedComponent const&) = default; /*!< Copy constructor */
    MountedComponent(
        MountedComponent&&) noexcept = default; /*!< Move constructor */
    MountedComponent& operator=(
        MountedComponent const&) = default; /*!< Copy assignment operator */
    MountedComponent& operator=(
        MountedComponent&&) noexcept = default; /*!< Move assignment operator */

    /**
     * \fn [[nodiscard]] int getMountOnId() const
     * \brief Get the Mount On Id object
     * \return The id of the entity mounted on
     */
    [[nodiscard]] int getMountOnId() const
    {
        return this->mountOnId;
    }

    /**
     * \fn void setMountOn(int entityId)
     * \brief Set the Mount On Id object
     * \param entityId The id of the entity mounted on
     */
    void setMountOn(int entityId)
    {
        this->mountOnId = entityId;
    }

  private:
    int mountOnId;  /*!< The id of the entity mounted on */
};