#include <any>
#include <cstdio>
#include <functional>
#include <optional>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "ASocket.hpp"

#pragma once

#include "Entity.hpp"
#include "Sparse.hpp"

/**
 * \class registry
 * \brief A registry that is a container for entities and components.
 */
class registry
{
  public:
    using entity_t = std::optional<Entity>; /*!< The type of an entity */
    using reference_type = entity_t&; /*!< The type of a reference to an entity */
    using const_reference_type = entity_t const&; /*!< The type of a const reference to an entity */
    using container_t = std::vector<entity_t>;  /*!< The type of the container of entities */
    using size_type = typename container_t::size_type; /*!< The type of the size of the container of entities */
    using iterator = typename container_t::iterator; /*!< The type of an iterator to the container of entities */
    using const_iterator = typename container_t::const_iterator; /*!< The type of a const iterator to the container of entities */

    registry() = default; /*!< Default constructor */
    registry(registry const&) = delete; /*!< Deleted copy constructor */
    registry(registry&&) noexcept = default; /*!< Default move constructor */
    ~registry() = default; /*!< Default destructor */
    registry& operator=(registry const&) = delete; /*!< Deleted copy assignment operator */
    registry& operator=(
        registry&&) noexcept = default; /*!< Default move assignment operator */

    /**
     * \fn template <class Component> sparse_array<Component>& register_component()
     * \brief Register a component in the registry
     * \param Component The component to register
     * @return A reference to the sparse array of the component
     */
    template <class Component>
    sparse_array<Component>& register_component()
    {
        auto eraseComponent = [this](Entity& entity) {
            sparse_array<Component>& array =
                std::any_cast<sparse_array<Component>&>(
                    this->components_arrays_[std::type_index(
                        typeid(Component))]);
            array.erase(entity);
        };
        components_destroy.emplace(typeid(Component), eraseComponent);
        std::type_index index = std::type_index(typeid(Component));
        auto any_array = components_arrays_.find(index);
        if (any_array == components_arrays_.end()) {
            auto res = components_arrays_.insert(
                std::make_pair(std::type_index(typeid(Component)),
                    std::make_any<sparse_array<Component>>(
                        sparse_array<Component>())));
            return std::any_cast<sparse_array<Component>&>(res.first->second);
        }
        return std::any_cast<sparse_array<Component>&>(any_array->second);
    }

    /**
     * \fn template <class Component> sparse_array<Component>& get_components()
     * \brief Get a reference to the sparse array of a component
     * \param Component The component to get the sparse array of
     * @return A reference to the sparse array of the component
     */
    template <class Component>
    sparse_array<Component>& get_components()
    {
        auto index = std::type_index(typeid(Component));
        if (components_arrays_.find(index) == components_arrays_.end())
            return register_component<Component>();
        return std::any_cast<sparse_array<Component>&>(
            components_arrays_[index]);
    }

    /**
     * \fn template <class Component> sparse_array<Component> const& get_components() const
     * \brief Get a const reference to the sparse array of a component
     * \param Component The component to get the sparse array of
     * \return A const reference to the sparse array of the component
     */
    template <class Component>
    sparse_array<Component> const& get_components() const
    {
        auto index = std::type_index(typeid(Component));
        if (components_arrays_.find(index) == components_arrays_.end())
            return register_component<Component>();
        return std::any_cast<sparse_array<Component>&>(
            components_arrays_.at(index));
    }

    /**
     * \fn Entity& spawn_entity()
     * \brief Spawn an entity in the registry
     * \return A reference to the entity
     */
    Entity& spawn_entity()
    {
        if (!freePlaces.empty()) {
            size_t index = freePlaces[0];
            freePlaces.erase(freePlaces.begin());
            entities[index] = Entity(index);
            return entities[index].value();
        }
        entities.push_back(Entity(entities.size()));
        return entities[entities.size() - 1].value();
    }

    /**
     * \fn entity_t entity_from_index(std::size_t idx)
     * \brief Get an entity from its index
     * \param idx The index of the entity
     * \return The entity
     */
    entity_t entity_from_index(std::size_t idx)
    {
        if (idx >= entities.size()) {
            return std::nullopt;
        }
        return entities[idx];
    };

    /**
     * \fn void kill_entity(Entity& e)
     * \brief Kill an entity
     * \param e The entity to kill
     */
    void kill_entity(Entity& e)
    {
        size_t idx = e.id;
        for (auto& [type, func] : components_destroy) {
            func(e);
        }
        for (size_t i = 0; i < freePlaces.size(); i++) {
            if (idx > freePlaces[i]) {
                freePlaces.insert(freePlaces.begin() + i, idx);
                break;
            }
        }
        if (freePlaces.empty())
            freePlaces.push_back(idx);
        entities[idx] = std::nullopt;
    }

    /**
     * \fn template <typename Component> typename sparse_array<Component>::reference_type add_component(Entity const& to, Component&& c)
     * \brief Add a component to an entity
     * \param to The entity to add the component to
     * \param c The component to add
     * \return A reference to the component
     */
    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(
        Entity const& to, Component&& c)
    {
        auto index = std::type_index(typeid(Component));
        auto it = components_arrays_.find(index);
        if (it == components_arrays_.end()) {
            this->register_component<Component>();
        }
        sparse_array<Component>& array =
            std::any_cast<sparse_array<Component>&>(components_arrays_[index]);
        array.insert_at(to.id, std::move(c));
        return array[to.id];
    }


    /**
     * \fn template <typename Component, typename... Params> typename sparse_array<Component>::reference_type emplace_component(Entity const& to, Params&&... p)
     * \brief Emplace a component to an entity
     * \param to The entity to add the component to
     * \param p The parameters to pass to the constructor of the component
     * \return A reference to the component
     */
    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(
        Entity const& to, Params&&... p)
    {
        auto index = std::type_index(typeid(Component));
        auto it = components_arrays_.find(index);
        if (it == components_arrays_.end()) {
            this->register_component<Component>();
        }
        sparse_array<Component>& array =
            std::any_cast<sparse_array<Component>&>(components_arrays_[index]);
        array.emplace_at(to.id, std::forward<Params>(p)...);
        return array[to.id];
    }

    /**
     * \fn template <typename Component> void remove_component(Entity& from)
     * \brief Remove a component from an entity
     * \param from The entity to remove the component from
     */
    template <typename Component>
    void remove_component(Entity& from)
    {
        auto index = std::type_index(typeid(Component));
        auto array = components_arrays_.find(index);
        if (array != components_arrays_.end()) {
            sparse_array<Component>& sparse =
                std::any_cast<sparse_array<Component>&>(array->second);
            sparse.erase(from.id);
        }
    }

    /**
     * \fn void add_system(std::function<void(registry&, ASocket&)>&& system)
     * \brief Add a system to the registry
     * \param system The system to add
     */
    void add_system(std::function<void(registry&, ASocket&)>&& system)
    {
        systems.push_back(std::move(system));
    }

    /**
     * \fn void run_systems(ASocket& socket)
     * \brief Run all the systems of the registry
     * \param socket The socket to use
     */
    void run_systems(ASocket& socket)
    {
        for (auto& system : systems) {
            system(*this, socket);
        }
    }

    /**
     * \fn void clearAllSystems()
     * \brief Clear all the systems of the registry
     */
    void clearAllSystems()
    {
        systems.clear();
    }

    /**
     * \fn std::vector<size_t> getFreePlaces()
     * \brief Get the free places in the registry
     * \return The free places
     */
    std::vector<size_t> getFreePlaces()
    {
        return freePlaces;
    }

    /**
     * \fn std::vector<std::optional<Entity>> getEntities() const
     * \brief Get the entities of the registry
     * \return The entities
     */
    std::vector<std::optional<Entity>> getEntities() const
    {
        return entities;
    }

  private:
    container_t entities; /*!< The entities of the registry */
    std::vector<size_t> freePlaces; /*!< The free places in the registry */
    std::vector<std::function<void(registry&, ASocket&)>> systems; /*!< The systems of the registry */
    std::unordered_map<std::type_index, std::any> components_arrays_; /*!< The components of the registry */
    std::unordered_map<std::type_index, std::function<void(Entity&)>>
        components_destroy; /*!< The functions to destroy the components of the registry */
};