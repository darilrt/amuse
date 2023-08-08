# Amuse Engine Documentation

## Index

- [FAQ](#faq)
- [Features](#features)
- [Class Reference](#class-reference)

## FAQ

### What is Amuse?

Amuse is a game engine written in C++ and uses SDL2 and OpenGL. It's currently in development.

### How do I build Amuse?

Amuse its commonly build inside a project that uses it.

### Which dependencies does Amuse have?

- SDL2
- OpenGL
- GLEW
- GLM

### Which platforms does Amuse support?

Amuse is currently being developed on Windows, but it should work on Linux and Mac OS X (not tested yet).

## Features

### Platform

- [x] Windows

### Graphics

The graphics module is based on OpenGL 3.3.

- [x] OpenGL 3.3
- [x] Shaders
- [x] Textures

### Input

- [x] Input system based on events (SDL2)
- [x] Keyboard
- [x] Mouse

## Class Reference

- [ecs](#ecs)
    - [Component](#class-component)
    - [Entity](#class-entity)
    - [System](#class-system)
- [gl](#gl)
    - [Shader](#shader)
    - [Texture](#texture)
- [wm](#wm)
    - [Window](#wmwindow)

## `namespace` ecs

### Functions

- [`Entity& ecs::CreateEntity(T... args)`](#entity-ecscreateentityt-args)

#### `Entity& ecs::CreateEntity(T... args)`

    Creates an entity and returns it.
    The entity isn't added to any system.

### `class` Component {#class-component}

Base class for components.

#### Example

```c++
#include <amuse/core.h>

struct SimpleComp : public ecs::Component {
public:
    void Init() override  { ... }

    void Update() override  { ... }

    void Render() override  { ... }

    void Destroy() override  { ... }
};
```

#### Methods

- [`Component::Component()`](#componentcomponent)

#### Overridable Methods

- [`void Component::Init()`](#void-componentinit) 
- [`void Component::Update()`](#void-componentupdate)
- [`void Component::Render()`](#void-componentrender)
- [`void Component::Destroy()`](#void-componentdestroy)

#### `Component::Component()`

    Constructs a component.

#### `void Component::Init()`

    Called when the component is initialized.

#### `void Component::Update()`

    Called every frame to update the component.

#### `void Component::Render()`

    Called every frame to render the component after the update.

#### `void Component::Destroy()`

    Called when the component is destroyed.

### `class` Entity

Class for entities.

#### Methods

- [`Entity::Entity()`](#entityentity)
- [`void Entity::AddComponent<T>()`](#t-entityaddcomponentt)
- [`void Entity::RemoveComponent<T>()`](#void-entityremovecomponentt)
- [`void Entity::GetComponent<T>()`](#t-entitygetcomponentt)
- [`void Entity::HasComponent<T>()`](#bool-entityhascomponentt)

#### Example

```c++
#include <amuse/core.h>

struct SimpleComp : public ecs::Component { ... };

int main(int argc, char** argv) {
    ecs::Entity entity;
    entity.AddComponent<SimpleComp>();

    ecs::Entity& entity2 = ecs::CreateEntity(
        SimpleComp()
    );
    
    return 0;
}
```

#### `Entity::Entity()`

    Constructs an entity.

#### `T& Entity::AddComponent<T>()`
    
    Adds a component to the entity by type.

#### `void Entity::RemoveComponent<T>()`
    
    Removes a component from the entity by type.

#### `T& Entity::GetComponent<T>()`

    Gets a component from the entity by type.

#### `bool Entity::HasComponent<T>()`
    
    Returns true if the entity has a component by type.

## `class` System

Base class for systems.

#### Example

```c++
#include <amuse/core.h>

struct SimpleComp : public ecs::Component { ... };

struct SimpleSystem : public ecs::System {
public:
    void Init() override  {
        CreateEntity(
            SimpleComp()
        );
    }

    void Update() override  { ... }

    void Render() override  { ... }

    void Destroy() override  { ... }
};
```

#### Methods

- [`System::System()`](#void-systemsystem)
- [`Entity& System::CreateEntity()`](#entity-systemcreateentityt-args)

#### Overridable Methods

- [`void System::Init()`](#void-systeminit)
- [`void System::Update()`](#void-systemupdate)
- [`void System::Render()`](#void-systemrender)
- [`void System::Destroy()`](#void-systemdestroy)

#### `void System::System()`

    Constructs a system.

#### `Entity& System::CreateEntity(T... args)`

    Creates an entity and adds it to the system.

#### `void System::Init()`
    
    Called when the system is initialized.

#### `void System::Update()`
    
    Called every frame to update the system.    

#### `void System::Render()`
        
    Called every frame to render the system after the update.

#### `void System::Destroy()`
    
    Called when the system is destroyed.

## `namespace` gl

## `namespace` wm