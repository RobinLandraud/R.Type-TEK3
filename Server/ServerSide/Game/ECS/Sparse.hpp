#include <iostream>
#include <optional>
#include <vector>

/**
 * \class sparse_array
 * \brief A sparse array class
 * \param Component The type of the elements of the array
 */
template <typename Component>
class sparse_array
{
  public:
    using value_type = std::optional<Component>; /*!< The type of the elements of the array */
    using reference_type = value_type&; /*!< The type of the reference to the elements of the array */
    using const_reference_type = value_type const&; /*!< The type of the const reference to the elements of the array */
    using container_t = std::vector<value_type>; /*!< The type of the container used to store the elements of the array */
    using size_type = typename container_t::size_type; /*!< The type of the size of the array */
    using iterator = typename container_t::iterator; /*!< The type of the iterator of the array */
    using const_iterator = typename container_t::const_iterator; /*!< The type of the const iterator of the array */

  public:
    sparse_array() = default; /*!< Default constructor */
    sparse_array(sparse_array const&) = default; /*!< Copy constructor */
    sparse_array(sparse_array&&) noexcept = default; /*!< Move constructor */
    ~sparse_array() = default; /*!< Default Destructor */
    sparse_array& operator=(
        sparse_array const&) = default; /*!< Copy assignment operator */
    sparse_array& operator=(
        sparse_array&&) noexcept = default; /*!< Move assignment operator */
    reference_type operator[](size_t idx)
    {
        return this->data[idx];
    } /*!< Operator [] */
    const_reference_type operator[](size_t idx) const
    {
        return this->data[idx];
    } /*!< const Operator [] */
    iterator begin()
    {
        return this->data.begin();
    } /*!< Iterator to the beginning of the array */
    const_iterator begin() const
    {
        return this->data.begin();
    } /*!< const Iterator to the beginning of the array */
    const_iterator cbegin() const
    {
        return this->data.cbegin();
    } /*!< const Iterator to the cbeginning of the array */
    iterator end()
    {
        return this->data.end();
    } /*!< Iterator to the end of the array */
    const_iterator end() const
    {
        return this->data.end();
    } /*!< const Iterator to the end of the array */
    const_iterator cend() const
    {
        return this->data.cend();
    } /*!< const Iterator to the cend of the array */
    size_type size() const
    {
        return this->data.size();
    } /*!< Size of the array */

    /**
     * \fn reference_type insert_at(size_type pos, Component const& component)
     * \brief Insert a component at a given position
     * \param pos The position where to insert the component
     * \param component The const reference of the component to insert
     * \return The reference to the inserted component
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
     * \brief Insert a component at a given position
     * \param pos The position where to insert the component
     * \param component The rvalue reference of the component to insert
     * \return The reference to the inserted component
     */
    reference_type insert_at(size_type pos, Component&& component)
    {
        if (pos >= this->size()) {
            this->data.resize(pos + 1);
        }
        this->data[pos] = std::move(component);
        return this->data[pos];
    } /*!< Insert a component at a given position by moving it */

    /**
     * \fn template <class... Params> reference_type emplace_at(size_type pos, Params&&... args)
     * \brief Emplace a component at a given position
     * \param pos The position where to emplace the component
     * \param args The arguments to forward to the constructor of the component
     * \return The reference to the emplaced component
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
     * \brief Erase the component at a given position
     * \param pos The position where to erase the component
     */
    void erase(size_type pos)
    {
        if (pos < this->size()) {
            this->data[pos] = std::nullopt;
        }
    }

    /**
     * \fn size_type get_index(value_type const& needle) const
     * \brief Get the index of a given component
     * \param needle The const reference of the component to find
     * \return The index of the component if found, std::nullopt otherwise
     */
    size_type get_index(value_type const& needle) const
    {
        return std::addressof(needle) - this->data.data();
    }

  private:
    container_t data; /*!< The container used to store the elements of the array */
};