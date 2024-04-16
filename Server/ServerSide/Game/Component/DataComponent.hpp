#pragma once
#include <any>
#include <optional>
#include <string>
#include <typeindex>
#include <unordered_map>

/**
 * \class DataComponent
 * \brief A component that stores data
 */
class DataComponent
{
  public:
    /**
     * \fn explicit DataComponent() = default
     * \brief Default constructor
     */
    explicit DataComponent() = default;
    ~DataComponent() = default; /*!< Default destructor */

    DataComponent(
        DataComponent const&) = default; /*!< Default copy constructor */
    DataComponent(
        DataComponent&&) noexcept = default; /*!< Default move constructor */
    DataComponent& operator=(
        DataComponent const&) = default; /*!< Default copy assignment operator
                                          */
    DataComponent& operator=(
        DataComponent&&) noexcept = default; /*!< Default move assignment
                                                operator */

    /**
     * \fn template <typename T> T getValue(std::string name)
     * \brief Get the value of a data
     * \param name The name of the data
     * \return The value of the data
     */
    template <typename T>
    T getValue(std::string name)
    {
        auto index = std::type_index(typeid(T));
        if (this->data.find(index) != this->data.end()) {
            if (this->data[index].find(name) != this->data[index].end()) {
                return std::any_cast<T>(this->data[index][name]);
            }
        }
        return T();
    }

    /**
     * \fn template <typename T> void addValue(std::string name, T&& value)
     * \brief Add a value to the data
     * \param name The name of the data
     * \param value The value of the data
     */
    template <typename T>
    void addValue(std::string name, T&& value)
    {
        auto index = std::type_index(typeid(T));
        if (this->data.find(index) != this->data.end()) {
            this->data[index][name] = std::move(value);
        } else {
            this->data[index] = std::unordered_map<std::string, std::any>();
            this->data[index][name] = std::move(value);
        }
    }

    /**
     * \fn template <typename T> void setValue(std::string name, T&& value)
     * \brief Set the value of a data
     * \param name The name of the data
     * \param value The value of the data
     */
    template <typename T>
    void setValue(std::string name, T&& value)
    {
        auto index = std::type_index(typeid(T));
        if (this->data.find(index) != this->data.end()) {
            if (this->data[index].find(name) != this->data[index].end()) {
                this->data[index][name] = std::move(value);
            }
        }
    }

    /**
     * \fn template <typename T> void removeValue(std::string name)
     * \brief Remove a value from the data
     * \param name The name of the data
     */
    template <typename T>
    void removeValue(std::string name)
    {
        auto index = std::type_index(typeid(T));
        if (this->data.find(index) != this->data.end()) {
            if (this->data[index].find(name) != this->data[index].end()) {
                this->data[index].erase(name);
                if (this->data[index].empty()) {
                    this->data.erase(index);
                }
            }
        }
    }

  private:
    std::unordered_map<std::type_index,
        std::unordered_map<std::string, std::any>>
        data{}; /*!< The data */
};