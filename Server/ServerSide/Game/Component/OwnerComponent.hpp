/**
 * \class OwnerComponent
 * \brief Component that holds a pointer to the owner of the entity
 */
class OwnerComponent
{
  public:
    OwnerComponent() = default; /*!< Default constructor */
    /**
     * \fn explicit OwnerComponent(int initId)
     * \brief Construct a new Owner Component object
     * \param initId The id of the owner
     */
    explicit OwnerComponent(int initId)
        : ownerId(initId){};
    ~OwnerComponent() = default; /*!< Default destructor */

    OwnerComponent(
        OwnerComponent const&) = default; /*!< Default copy constructor */
    OwnerComponent(
        OwnerComponent&&) noexcept = default; /*!< Default move constructor */
    OwnerComponent& operator=(
        OwnerComponent const&) = default; /*!< Default copy assignment operator
                                           */
    OwnerComponent& operator=(
        OwnerComponent&&) noexcept = default; /*!< Default move assignment
                                                 operator */

    /**
     * \fn [[nodiscard]] int getOwnerId() const
     * \brief Get the Owner Id object
     * \return The id of the owner
     */
    [[nodiscard]] int getOwnerId() const
    {
        return ownerId;
    }

    /**
     * \fn void setOwnerId(int newOwnerId)
     * \brief Set the Owner Id object
     * \param newId The new id of the owner
     */
    void setOwnerId(int newId)
    {
        ownerId = newId;
    }

  private:
    int ownerId; /*!< The id of the owner */
};