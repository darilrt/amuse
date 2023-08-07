#pragma once

#include <bitset>
#include <cstdint>
#include <array>
#include <memory>
#include <vector>

namespace ecs {
	class Entity;
    class Component;
    class System;

    using ComponentID = std::uint32_t;
    using SystemID = std::uint32_t;

    constexpr ComponentID MAX_COMPONENTS = 32;
    constexpr SystemID MAX_SYSTEMS = 32;

    constexpr ComponentID INVALID_COMPONENT = MAX_COMPONENTS;
    constexpr SystemID INVALID_SYSTEM = MAX_SYSTEMS;

    extern ComponentID lastComponentID;
    extern SystemID lastSystemID;

    template<typename T>
    constexpr ComponentID GetComponentTypeID() noexcept {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
        static ComponentID typeID = INVALID_COMPONENT;
        if (typeID == INVALID_COMPONENT) {
            typeID = lastComponentID++;
        }
        return typeID;
    }

    template<typename T>
    constexpr SystemID GetSystemTypeID() noexcept {
        static_assert(std::is_base_of<System, T>::value, "T must inherit from System");
        static SystemID typeID = INVALID_SYSTEM;
        if (typeID == INVALID_SYSTEM) {
            typeID = lastSystemID++;
        }
        return typeID;
    }

    class Component {
    public:
        Entity* entity = nullptr;

        virtual void Init() {}
        virtual void Update() {}
        virtual void Render() {}
        virtual void Destroy() {}
    };

    class Entity {
    private:
        std::bitset<MAX_COMPONENTS> componentMask;
        std::array<Component*, MAX_COMPONENTS> components;

    public:
        bool active = true;

        template<typename T>
        bool HasComponent() const noexcept {
            return componentMask[GetComponentTypeID<T>()];
        }

        template<typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args) {
            T* component = new T(std::forward<TArgs>(args)...);
            component->entity = this;
            components[GetComponentTypeID<T>()] = component;
            componentMask[GetComponentTypeID<T>()] = true;
            component->Init();
            return *component;
        }

        template<typename T>
        T& GetComponent() const {
            return *static_cast<T*>(components[GetComponentTypeID<T>()]);
        }

        template<typename T>
        void RemoveComponent() {
            auto ptr(components[GetComponentTypeID<T>()]);
            componentMask[GetComponentTypeID<T>()] = false;
            components[GetComponentTypeID<T>()] = nullptr;
            delete ptr;
        }

        void Update() {
            for (auto& c : components) {
                if (c) { c->Update(); }
            }
        }

        void Render() {
            for (auto& c : components) {
                if (c) { c->Render(); }
            }
        }

        void Destroy() {
            for (auto& c : components) {
                if (c) { c->Destroy(); }
            }
        }
    };

    class System {
    private:
        std::vector<Entity*> entities;

    public:
        virtual void Init() {}
        virtual void Update() {}
        virtual void Render() {}
        virtual void Destroy() {}

        void AddEntity(Entity* entity) {
            entities.push_back(entity);
        }

        void UpdateEntities() {
            for (auto& entity : entities) {
                entity->Update();
            }
        }

        void RenderEntities() {
            for (auto& entity : entities) {
                entity->Render();
            }
        }

        void DestroyEntities() {
            for (auto& entity : entities) {
                entity->Destroy();
            }
        }

        ecs::Entity& CreateEntity() {
            ecs::Entity* entity = new ecs::Entity();
            AddEntity(entity);
            return *entity;
        }

        template<typename... TArgs>
        ecs::Entity& CreateEntity(TArgs&&... args) {
            ecs::Entity* entity = new ecs::Entity();
            (entity->AddComponent<TArgs>(std::forward<TArgs>(args)), ...);
            AddEntity(entity);
            return *entity;
        }
    };   

    class SystemManager {
    private:
        std::array<System*, MAX_SYSTEMS> systems;
        SystemID activeSystem = INVALID_SYSTEM;

    public:
        template<typename T, typename... TArgs>
        T& AddSystem(TArgs&&... args) {
            systems[GetSystemTypeID<T>()] = new T(std::forward<TArgs>(args)...);
            systems[GetSystemTypeID<T>()]->Init();
            return *static_cast<T*>(systems[GetSystemTypeID<T>()]);
        }

        template<typename T>
        T& GetSystem() const {
            auto ptr(systems[GetSystemTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }

        template<typename T>
        void SetActiveSystem() {
            activeSystem = GetSystemTypeID<T>();
        }

        System* GetActiveSystem() {
            return systems[activeSystem];
        }

        SystemID GetActiveSystemID() {
            return activeSystem;
        }

        void Update() {
            systems[activeSystem]->Update();
            systems[activeSystem]->UpdateEntities();
        }

        void Render() {
            systems[activeSystem]->Render();
            systems[activeSystem]->RenderEntities();
        }

        void Destroy() {
            systems[activeSystem]->Destroy();
            systems[activeSystem]->DestroyEntities();
        }
    };

    template<typename... TArgs>
    inline ecs::Entity& CreateEntity(TArgs&&... args) {
        ecs::Entity* entity = new ecs::Entity();
        (entity->AddComponent<TArgs>(std::forward<TArgs>(args)), ...);
        return *entity;
    }
}
