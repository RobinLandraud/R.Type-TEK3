#include <iostream>
#include <optional>
#include <vector>

/**
 * \class sparse_array
 * \brief A sparse array.
 * Used to store components
 */
template <typename Component>
class sparse_array
{
  public:
    using value_type =
        std::optional<Component>; /*!< The value type of the sparse array */
    using reference_type =
        value_type&; /*!< The reference type of the sparse array */
    using const_reference_type =
        value_type const&; /*!< The const reference type of the sparse array */
    using container_t =
        std::vector<value_type>; /*!< The container type of the sparse array */
    using size_type = typename container_t::size_type; /*!< The size type of the sparse array */
    using iterator = typename container_t::iterator;   /*!< The iterator type of the sparse array */
    using const_iterator =
        typename container_t::const_iterator; /*!< The const iterator type of the sparse array */

  public:
    sparse_array() = default; /*!< Default constructor, you can add more constructors */
    sparse_array(sparse_array const&) = default;     /*!< Copy constructor */
    sparse_array(sparse_array&&) noexcept = default; /*!< Move constructor */
    ~sparse_array() = default;                       /*!< Default destructor */
    sparse_array& operator=(
        sparse_array const&) = default; /*!< Copy assignment operator */
    sparse_array& operator=(
        sparse_array&&) noexcept = default; /*!< Move assignment operator */

    /**
     * \fn reference_type operator[](size_t idx)
     * \brief Access the element at the given index
     * \param idx The index of the element to access
     * \return A reference to the element at the given index
     */
    reference_type operator[](size_t idx)
    {
        return this->data[idx];
    }

    /**
     * \fn bool exists(size_t idx) const
     * \brief Check if the element at the given index exists
     * \param idx The index of the element to check
     * \return true if the element exists, false otherwise
     */
    bool exists(size_t idx) const
    {
        if (idx >= this->data.size())
            return false;
        return this->data[idx].has_value();
    }

    /**
     * \fn Component& at(size_t idx)
     * \brief Access the element at the given index
     * \param idx The index of the element to access
     * \return A reference to the element at the given index
     */
    Component& at(size_t idx)
    {
        return this->data[idx].value();
    }

    /**
     * \fn const_reference_type operator[](size_t idx) const
     * \brief Access the element at the given index
     * \param idx The index of the element to access
     * \return A const reference to the element at the given index
     */
    const_reference_type operator[](size_t idx) const
    {
        return this->data[idx];
    }

    /**
     * \fn iterator begin()
     * \brief Get an iterator to the beginning of the sparse array
     * \return An iterator to the beginning of the sparse array
     */
    iterator begin()
    {
        return this->data.begin();
    }

    /**
     * \fn const_iterator begin() const
     * \brief Get a const iterator to the beginning of the sparse array
     * \return A const iterator to the beginning of the sparse array
     */
    const_iterator begin() const
    {
        return this->data.begin();
    }

    /**
     * \fn const_iterator cbegin() const
     * \brief Get a const iterator to the beginning of the sparse array
     * \return A const iterator to the beginning of the sparse array
     */
    const_iterator cbegin() const
    {
        return this->data.cbegin();
    }

    /**
     * \fn iterator end()
     * \brief Get an iterator to the end of the sparse array
     * \return An iterator to the end of the sparse array
     */
    iterator end()
    {
        return this->data.end();
    }

    /**
     * \fn const_iterator end() const
     * \brief Get a const iterator to the end of the sparse array
     * \return A const iterator to the end of the sparse array
     */
    const_iterator end() const
    {
        return this->data.end();
    }

    /**
     * \fn const_iterator cend() const
     * \brief Get a const iterator to the end of the sparse array
     * \return A const iterator to the end of the sparse array
     */
    const_iterator cend() const
    {
        return this->data.cend();
    }

    /**
     * \fn size_type size() const
     * \brief Get the size of the sparse array
     * \return The size of the sparse array
     */
    size_type size() const
    {
        return this->data.size();
    }

    /**
     * \fn reference_type insert_at(size_type pos, Component const& component)
     * \brief Insert a component at the given position
     * \param pos The position to insert the component at
     * \param component The component to insert
     * \return A reference to the inserted component
     */
    reference_type insert_at(size_type pos, Component const& component)
    {
        if (pos >= this->size()) {
            this->data.resize(pos + 1);
        }
        this->data[pos] = component;
        return this->data[pos];
    }

    /**
     * \fn reference_type insert_at(size_type pos, Component&& component)
     * \brief Insert a component at the given position
     * \param pos The position to insert the component at
     * \param component The component to insert
     * \return A reference to the inserted component
     */
    reference_type insert_at(size_type pos, Component&& component)
    {
        if (pos >= this->size()) {
            this->data.resize(pos + 1);
        }
        this->data[pos] = std::move(component);
        return this->data[pos];
    }

    /**
     * \fn template <class... Params> reference_type emplace_at(size_type pos, Params&&... args)
     * \brief Emplace a component at the given position
     * \param pos The position to emplace the component at
     * \param args The arguments to forward to the component constructor
     * \return A reference to the emplaced component
     */
    template <class... Params>
    reference_type emplace_at(size_type pos, Params&&... args)
    {
        if (pos >= this->size()) {
            this->data.resize(pos + 1);
        }
        this->data[pos].emplace(std::forward<Params>(args)...);
        return this->data[pos];
    }

    /**
     * \fn void erase(size_type pos)
     * \brief Erase the component at the given position
     * \param pos The position of the component to erase
     */
    void erase(size_type pos)
    {
        if (pos < this->size()) {
            this->data[pos] = std::nullopt;
        }
    }

    /**
     * \fn size_type get_index(value_type const& needle) const
     * \brief Get the index of the given component
     * \param needle The component to get the index of
     * \return The index of the given component
     */
    size_type get_index(value_type const& needle) const
    {
        return std::addressof(needle) - this->data.data();
    }

  private:
    container_t data; /*!< The container of the sparse array */
};