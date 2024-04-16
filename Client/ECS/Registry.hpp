#include <algorithm>
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

#include "AEngine.hpp"
#include "Entity.hpp"
#include "Sparse.hpp"

/**
 * \class Registry
 * \brief The registry of the game.
 * Used to store entities
 */
class registry
{
  public:
    using entity_t =
        std::optional<Entity>; /*!< Entity is a wrapper around an index */
    using reference_type = entity_t&; /*!< Reference to an entity */
    using const_reference_type =
        entity_t const&; /*!< Const reference to an entity */
    using container_t = std::vector<entity_t>; /*!< Container of entities */
    using size_type =
        typename container_t::size_type; /*!< Size type of the container */
    using iterator =
        typename container_t::iterator; /*!< Iterator of the container */
    using const_iterator =
        typename container_t::const_iterator; /*!< Const iterator of the container */

    registry() = default; /*!< Default constructor, You can add more constructors */
    registry(registry const&) = delete;      /*!< Copy constructor */
    registry(registry&&) noexcept = default; /*!< Move constructor */
    ~registry() = default;                   /*!< Default Destructor */
    registry& operator=(
        registry const&) = delete; /*!< Copy assignment operator */
    registry& operator=(
        registry&&) noexcept = default; /*!< Move assignment operator */

    /**
     * \fn template <class Component> sparse_array<Component>& register_component()
     * \brief Register a component in the registry
     * \tparam Component The component to register
     * \return The sparse array of the component
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
     * \brief Get the sparse array of a component
     * \tparam Component The component to get
     * \return The sparse array of the component
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
     * \brief Get the sparse array of a component
     * \tparam Component The component to get
     * \return The sparse array of the component
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
     * \brief Spawn an entity
     * \return The entity
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
     * \brief Get an entity from an index
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
        freePlaces.push_back(idx);
        std::sort(freePlaces.begin(), freePlaces.end());
        entities[idx] = std::nullopt;
    }

    /**
     * \fn template <typename Component> typename sparse_array<Component>::reference_type add_component(Entity const& to, Component&& c) 
     * \brief Add a component to an entity
     * \tparam Component Type component to add
     * \param to The entity to add the component to
     * \param c The component to add
     * \return The component
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
     * \fn template <typename Component, typename... Params>
        typename sparse_array<Component>::reference_type emplace_component(Entity const& to, Params&&... p)
     * \brief Emplace a component to an entity
     * \tparam Component Type component to add
     * \tparam Params The parameters of the component
     * \param to The entity to add the component to
     * \param p The parameters of the component
     * \return The component
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
     * \tparam Component The component to remove
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
     * \fn void add_system(std::function<void(registry&, AEngine&, ServerToken&)>&& system)
     * \brief Add a system to the registry
     * \param system The system to add
     */
    void add_system(
        std::function<void(registry&, AEngine&, ServerToken&)>&& system)
    {
        systems.push_back(std::move(system));
    }

    /**
     * \fn void run_systems(AEngine& engine, ServerToken& serverToken)
     * \brief Run all the systems
     * \param engine The engine to run the systems on
     * \param serverToken The server token
     */
    void run_systems(AEngine& engine, ServerToken& serverToken)
    {
        for (auto& system : systems) {
            system(*this, engine, serverToken);
        }
    }

    /**
     * \fn void clearAllSystems()
     * \brief Clear all the systems
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
     * \brief Get the entities in the registry
     * \return The entities
     */
    std::vector<std::optional<Entity>> getEntities() const
    {
        return entities;
    }

  private:
    container_t entities;           /*!< The entities */
    std::vector<size_t> freePlaces; /*!< The free places */
    std::vector<std::function<void(registry&, AEngine&, ServerToken&)>>
        systems; /*!< The systems */
    std::unordered_map<std::type_index, std::any>
        components_arrays_; /*!< The components arrays */
    std::unordered_map<std::type_index, std::function<void(Entity&)>>
        components_destroy; /*!< The components destroy functions */
};