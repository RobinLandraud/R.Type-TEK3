#pragma once

#include "DataComponent.hpp"
#include "Registry.hpp"

/**
 * \class ScriptDataComponents
 * \brief The script data component
 */
class ScriptDataComponents
{
  public:
    /**
     * \fn ScriptDataComponents(registry& reg)
     * \brief The constructor
     * \param reg The registry
     */
    ScriptDataComponents(registry& reg)
        : reg(reg){};
    ~ScriptDataComponents() = default;  /*!< Default destructor */

    /**
     * \fn void add(size_t ent_id)
     * \brief Add a data component to an entity
     * \param ent_id The entity id
     */
    void add(size_t ent_id)
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<DataComponent>(entity.value(), DataComponent());
    }

    /**
     * \fn size_t size()
     * \brief Get the number of data components
     * \return The number of data components
     */
    size_t size()
    {
        return reg.get_components<DataComponent>().size();
    }

    /**
     * \fn DataComponent& at(size_t index)
     * \brief Get a data component
     * \param index The index of the data component
     * \return The data component
     */
    DataComponent& at(size_t index)
    {
        return reg.get_components<DataComponent>()[index].value();
    }

    /**
     * \fn bool exists(size_t index) 
     * \brief Check if a data component exists
     * \param index The index of the data component
     * \return true if the data component exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<DataComponent>().exists(index);
    }

    /**
     * \fn void addStringAt(size_t index, std::string key, std::string value)
     * \brief Add a string to a data component
     * \param index The index of the data component
     * \param key The key of the string
     * \param value The value of the string
     */
    void addStringAt(size_t index, std::string key, std::string value)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            reg.get_components<DataComponent>()[index].value().addValue(
                key, value);
        }
    }

    /**
     * \fn void setStringAt(size_t index, std::string key, std::string value)
     * \brief Set a string to a data component
     * \param index The index of the data component
     * \param key The key of the string
     * \param value The value of the string
     */
    void setStringAt(size_t index, std::string key, std::string value)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            reg.get_components<DataComponent>()[index].value().setValue(
                key, value);
        }
    }

    /**
     * \fn std::string getStringAt(size_t index, std::string key)
     * \brief Get a string from a data component
     * \param index The index of the data component
     * \param key The key of the string
     * \return The value of the string
     */
    std::string getStringAt(size_t index, std::string key)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            return reg.get_components<DataComponent>()[index]
                .value()
                .getValue<std::string>(key);
        }
        return "";
    }

    /**
     * \fn void addIntAt(size_t index, std::string key, int value)
     * \brief Add an int to a data component
     * \param index The index of the data component
     * \param key The key of the int
     * \param value The value of the int
     */
    void addIntAt(size_t index, std::string key, int value)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            reg.get_components<DataComponent>()[index].value().addValue(
                key, value);
        }
    }

    /**
     * \fn void setIntAt(size_t index, std::string key, int value)
     * \brief Set an int to a data component
     * \param index The index of the data component
     * \param key The key of the int
     * \param value The value of the int
     */
    void setIntAt(size_t index, std::string key, int value)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            reg.get_components<DataComponent>()[index].value().setValue(
                key, value);
        }
    }

    /**
     * \fn int getIntAt(size_t index, std::string key)
     * \brief Get an int from a data component
     * \param index The index of the data component
     * \param key The key of the int
     * \return The value of the int
     */
    int getIntAt(size_t index, std::string key)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            return reg.get_components<DataComponent>()[index]
                .value()
                .getValue<int>(key);
        }
        return 0;
    }

    /**
     * \fn void addFloatAt(size_t index, std::string key, float value)
     * \brief Add a float to a data component
     * \param index The index of the data component
     * \param key The key of the float
     * \param value The value of the float
     */
    void addFloatAt(size_t index, std::string key, float value)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            reg.get_components<DataComponent>()[index].value().addValue(
                key, value);
        }
    }

    /**
     * \fn void setFloatAt(size_t index, std::string key, float value)
     * \brief Set a float to a data component
     * \param index The index of the data component
     * \param key The key of the float
     * \param value The value of the float
     */
    void setFloatAt(size_t index, std::string key, float value)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            reg.get_components<DataComponent>()[index].value().setValue(
                key, value);
        }
    }

    /**
     * \fn float getFloatAt(size_t index, std::string key)
     * \brief Get a float from a data component
     * \param index The index of the data component
     * \param key The key of the float
     * \return The value of the float
     */
    float getFloatAt(size_t index, std::string key)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            return reg.get_components<DataComponent>()[index]
                .value()
                .getValue<float>(key);
        }
        return 0.0f;
    }

    /**
     * \fn void addBoolAt(size_t index, std::string key, bool value)
     * \brief Add a bool to a data component
     * \param index The index of the data component
     * \param key The key of the bool
     * \param value The value of the bool
     */
    void addBoolAt(size_t index, std::string key, bool value)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            reg.get_components<DataComponent>()[index].value().addValue(
                key, value);
        }
    }

    /**
     * \fn void setBoolAt(size_t index, std::string key, bool value)
     * \brief Set a bool to a data component
     * \param index The index of the data component
     * \param key The key of the bool
     * \param value The value of the bool
     */
    void setBoolAt(size_t index, std::string key, bool value)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            reg.get_components<DataComponent>()[index].value().setValue(
                key, value);
        }
    }

    /**
     * \fn bool getBoolAt(size_t index, std::string key)
     * \brief Get a bool from a data component
     * \param index The index of the data component
     * \param key The key of the bool
     * \return The value of the bool
     */
    bool getBoolAt(size_t index, std::string key)
    {
        if (reg.get_components<DataComponent>().exists(index)) {
            return reg.get_components<DataComponent>()[index]
                .value()
                .getValue<bool>(key);
        }
        return false;
    }

  private:
    registry& reg;  /*!< The registry */
};