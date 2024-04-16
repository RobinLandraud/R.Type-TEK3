#pragma once

#include "ServerPropertiesComponent.hpp"

/**
 * \class ScriptServerPropertiesComponent
 * \brief A class that allows a script to modify the server properties component of an entity
 */
class ScriptServerPropertiesComponents
{
  public:
    /**
     * \fn ScriptServerPropertiesComponents(registry& reg): reg(reg)
     * \brief The constructor of the class
     * \param reg The registry
     */
    ScriptServerPropertiesComponents(registry& reg)
        : reg(reg){};
    ~ScriptServerPropertiesComponents() = default; /*!< Default destructor */

    /**
     * \fn void add(size_t ent_id, size_t server_id)
     * \brief Add a server properties component to an entity
     * \param ent_id The entity id
     * \param server_id The server id
     */
    void add(size_t ent_id, size_t server_id)
    {
        auto entity = reg.entity_from_index(ent_id);
        if (!entity)
            return;
        reg.add_component<ServerPropertiesComponent>(
            entity.value(), ServerPropertiesComponent(server_id));
    }

    /**
     * \fn size_t size()
     * \brief Get the number of script server properties components
     * \return The number of script server properties components
     */
    size_t size()
    {
        return reg.get_components<ServerPropertiesComponent>().size();
    }

    /**
     * \fn ServerPropertiesComponent& at(size_t index)
     * \brief Get a script server properties component at a given index
     * \param index The index
     * \return The script server properties component
     */
    ServerPropertiesComponent& at(size_t index)
    {
        return reg.get_components<ServerPropertiesComponent>()[index].value();
    }

    /**
     * \fn bool exists(size_t index)
     * \brief Check if a script transform component exists at a given index
     * \param index The index
     * \return True if the script transform component exists, false otherwise
     */
    bool exists(size_t index)
    {
        return reg.get_components<ServerPropertiesComponent>().exists(index);
    }

    /**
     * \fn bool isUpdateAt(size_t index)
     * \brief Check if a script server properties component is updated at a given index
     * \param index The index
     * \return True if the script server properties component is updated, false otherwise
     */
    bool isUpdateAt(size_t index)
    {
        if (reg.get_components<ServerPropertiesComponent>().exists(index)) {
            return reg.get_components<ServerPropertiesComponent>()[index]
                .value()
                .isUpdate();
        }
        return false;
    }

    /**
     * \fn void setMethodListAt(size_t index, std::vector<ServerPropertiesComponent::BufferMethod> method_list)
     * \brief Set the method list of a script server properties component at a given index
     * \param index The index
     * \param method_list The method list
     */
    void setMethodListAt(size_t index,
        std::vector<ServerPropertiesComponent::BufferMethod> method_list)
    {
        if (reg.get_components<ServerPropertiesComponent>().exists(index)) {
            reg.get_components<ServerPropertiesComponent>()[index]
                .value()
                .setMethodList(method_list);
        }
    }

    /**
     * \fn void addMethodAt(size_t index, ServerPropertiesComponent::BufferMethod method)
     * \brief Add a method to a script server properties component at a given index
     * \param index The index
     * \param method The method
     */
    void addMethodAt(
        size_t index, ServerPropertiesComponent::BufferMethod method)
    {
        if (reg.get_components<ServerPropertiesComponent>().exists(index)) {
            reg.get_components<ServerPropertiesComponent>()[index]
                .value()
                .addMethod(method);
        }
    }
    
    /**
     * \fn void BuildAndAddMethodAt(size_t index, u_int64_t header, std::string buffer)
     * \brief Build and add a method to a script server properties component at a given index
     * \param index The index
     * \param header The header
     * \param buffer The buffer
     */
    void BuildAndAddMethodAt(size_t index, u_int64_t header, std::string buffer)
    {
        if (reg.get_components<ServerPropertiesComponent>().exists(index)) {
            reg.get_components<ServerPropertiesComponent>()[index]
                .value()
                .BuildAndAddMethod(header, buffer);
        }
    }

    /**
     * \fn size_t getIdAt(size_t index)
     * \brief Get the id of a script server properties component at a given index
     * \param index The index
     * \return The id
     */
    size_t getIdAt(size_t index)
    {
        if (reg.get_components<ServerPropertiesComponent>().exists(index)) {
            return reg.get_components<ServerPropertiesComponent>()[index]
                .value()
                .getId();
        }
        return 0;
    }

  private:
    registry& reg; /*!< The registry */
};