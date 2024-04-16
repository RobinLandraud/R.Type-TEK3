#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

/**
 * \class ServerPropertiesComponent
 * \brief A component that handle the server properties.
 * Used to create a server properties
 */
class ServerPropertiesComponent
{
  public:
    /**
     * \fn explicit ServerPropertiesComponent(size_t p_id) noexcept
     * \brief Default constructor
     * \param p_id The id of the server
     */
    explicit ServerPropertiesComponent(size_t p_id) noexcept
        : id(p_id){};
    ~ServerPropertiesComponent() noexcept = default; /*!< Default destructor */

    ServerPropertiesComponent(
        ServerPropertiesComponent const&) noexcept = default; /*!< Copy constructor */
    ServerPropertiesComponent(
        ServerPropertiesComponent&&) noexcept = default; /*!< Move constructor */
    ServerPropertiesComponent& operator=(
        ServerPropertiesComponent const&) noexcept = default; /*!< Copy assignment operator */
    ServerPropertiesComponent& operator=(
        ServerPropertiesComponent&&) noexcept = default; /*!< Move assignment operator */

    /**
     * \class BufferMethod
     * \brief A class that handle the buffer method.
     * Used to create a buffer method
     */
    struct BufferMethod {
        uint64_t header;
        std::string buffer;
    };

    /**
     * \fn explicit operator size_t() const
     * \brief Get the id of the server
     * \return size_t The id of the server
     */
    explicit operator size_t() const
    {
        return this->id;
    }

    /**
     * \fn bool isUpdate()
     * \brief Check if the server need to be updated
     * \return true if the server need to be updated, false otherwise
     */
    bool isUpdate()
    {
        return !methodList.empty();
    }

    /**
     * \fn [[nodiscard]] std::vector<BufferMethod> getMethodList() const
     * \brief Get the list of method to call
     * \return The list of method to call
     */
    [[nodiscard]] std::vector<BufferMethod> getMethodList() const
    {
        return this->methodList;
    }

    /**
     * \fn void setMethodList(std::vector<BufferMethod> p_args)
     * \brief Set the list of method to call
     * \param p_args The list of method to call
     */
    void setMethodList(std::vector<BufferMethod> p_args)
    {
        this->methodList = std::move(p_args);
    }

    /**
     * \fn void addMethod(BufferMethod p_method)
     * \brief Add a method to the list of method to call
     * \param p_method The method to add
     */
    void addMethod(BufferMethod p_method)
    {
        this->methodList.push_back(std::move(p_method));
    }

    /**
     * \fn void BuildAndAddMethod(uint64_t p_header, std::string p_buffer)
     * \brief Build and add a method to the list of method to call
     * \param p_header The header of the method
     * \param p_buffer The buffer of the method
     */
    void BuildAndAddMethod(uint64_t p_header, std::string p_buffer)
    {
        this->methodList.push_back({p_header, p_buffer});
    }

    /**
     * \fn [[nodiscard]] size_t getId() const
     * \brief Get the id of the server
     * \return The id of the server
     */
    [[nodiscard]] size_t getId() const
    {
        return this->id;
    }

    void clearMethod() {
        methodList.clear();
    }

  private:
    size_t id;  /*!< The id of the server */
    std::vector<BufferMethod> methodList;   /*!< The list of method to call */
};