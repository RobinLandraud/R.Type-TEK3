
/**
 * \class TestComponent
 * \brief A test component
 */
class TestComponent
{
  public:
    TestComponent() = default; /*!< Default constructor */
    ~TestComponent() = default; /*!< Default destructor */

    /**
     * \fn void setValue(int val)
     * \brief Set the value of the component
     * \param val The new value
     */
    void setValue(int val)
    {
        value = val;
    };

    /**
     * \fn int getValue() const
     * \brief Get the value of the component
     * \return int The value of the component
     */
    int getValue() const
    {
        return value;
    }

  private:
    int value = 0; /*!< The value of the component */
};