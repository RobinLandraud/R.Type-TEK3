
/**
 * \class MountedComponent
 * \brief A mounted component.
 */
class MountedComponent
{
  public:
    /**
     * \fn explicit MountedComponent(int entityID)
     * \brief Constructor
     * \param entityID The entity ID
     */
    explicit MountedComponent(int entityId)
        : mountOnId(entityId){};
    ~MountedComponent() = default; /*!< Default destructor */

    MountedComponent(
        MountedComponent const&) = default; /*!< Copy constructor */
    MountedComponent(
        MountedComponent&&) noexcept = default; /*!< Move constructor */
    MountedComponent& operator=(
        MountedComponent const&) = default; /*!< Copy assignment operator
                                             */
    MountedComponent& operator=(
        MountedComponent&&) noexcept = default; /*!< Move assignment
                                                         operator */

    /**
     * \fn [[nodiscard]] int getMountOnId() const
     * \brief Get the mount on ID
     * \return The mount on ID
     */
    [[nodiscard]] int getMountOnId() const
    {
        return this->mountOnId;
    }

    /**
     * \fn void setMountOn(int entityId)
     * \brief Set the mount on ID
     * \param entityId The entity ID
     */  
    void setMountOn(int entityId)
    {
        this->mountOnId = entityId;
    }

  private:
    int mountOnId; /*!< The mount on ID */
};