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

- [namespace ecs](#namespace-ecs)
    - [Functions](#functions)
        - [CreateEntity](#entity-ecscreateentityt-args)
    - [class Component](#class-component)
    - [class Entity](#class-entity)
    - [class System](#class-system)
- [namespace gl](#namespace-gl)
    - [class Mesh](#class-mesh)
    - [class Shader](#class-shader)
    - [class Buffer](#class-buffer)
    - [class Texture](#class-texture)
    - [class Camera](#class-camera)
    - [class Transform](#class-transform)
    - [class WireBatch](#class-wirebatch)
- [namespace wm](#namespace-wm)
    - [class Window](#wmwindow)
- singletons
    - [class Input](#class-input)
    <!-- - [class Time](#class-time) -->
    - [class es](#class-es) (Event System)
- components
    - [Transform](#class-transform)
    - [Sprite](#class-sprite)
    - [Camera](#class-camera)

## `namespace` ecs

### Functions

- [`Entity& ecs::CreateEntity(T... args)`](#entity-ecscreateentityt-args)

#### `Entity& ecs::CreateEntity(T... args)`

    Creates an entity, add all the components passed as arguments and returns it. The entity isn't added to any system.

### `class` Component {#class-component}

Base class for components.

#### Example

```c++
#include <amuse/core.h>

struct SimpleComp : public ecs::Component {
public:
    void Init() override { ... }

    void Update() override { ... }

    void Render() override { ... }

    void Destroy() override { ... }
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

int main(int argc, char** argv) {
    ecs::Entity entity;
    entity.AddComponent<Transofrm>();

    // or

    ecs::Entity& entity2 = ecs::CreateEntity(
        Transofrm()
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

struct SimpleSystem : public ecs::System {
public:
    void Init() override  {
        CreateEntity(
            Transform(),
            Sprite()
        );
    }

    void Update() override { ... }

    void Render() override { ... }

    void Destroy() override { ... }
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

### `class` Mesh

Class for meshes.

#### Methods

- [`Mesh::Mesh()`](#meshmesh)
- [`void Mesh::Bind()`](#void-meshbind)
- [`void Mesh::Unbind()`](#void-meshunbind)
- [`void Mesh::DrawTriangles()`](#void-meshdrawtriangles)
- [`void Mesh::SetVertices(std::vector<glm::vec3> vertices)`](#void-meshsetverticesstdvectorglmvec3-vertices)
- [`void Mesh::SetIndices(std::vector<unsigned int> indices)`](#void-meshsetindicesstdvectorunsigned-int-indices)
- [`void Mesh::SetNormals(std::vector<glm::vec3> normals)`](#void-meshsetnormalsstdvectorglmvec3-normals)
- [`void Mesh::SetUVs(std::vector<glm::vec2> uvs)`](#void-meshsetuvsstdvectorglmvec2-uvs)
- [`void Mesh::Bake()`](#void-meshbake)

### `class` Shader

### `class` Buffer

### `class` Texture

#### Methods

- [`Texture::Texture(int width, int height)`](#texturetextureint-width-int-height)
- [`Texture* Texture::Load(std::string path)`](#texture-textureloadstdstring-path)
- [`void Texture::Bind()`](#void-texturebind)
- [`void Texture::Unbind()`](#void-textureunbind)
- [`void Texture::SetFormat(Format format)`](#void-texturesetformatformat-format)
- [`void Texture::SetFilter(Filter filter)`](#void-texturesetfilterfilter-filter)
- [`void Texture::SetWrap(Wrap wrap)`](#void-texturesetwrapwrap-wrap)
- [`Format Texture::GetFormat()`](#format-texturegetformat)
- [`Wrap Texture::GetWrap()`](#wrap-texturegetwrap)
- [`uint32_t Texture::GetWidth()`](#int-texturegetwidth)
- [`uint32_t Texture::GetHeight()`](#int-texturegetheight)
- [`glm::ivec2 Texture::GetSize()`](#glmivec2-texturegetsize)

#### `Texture::Texture(int width, int height)`

    Constructs a texture with the specified width and height.

#### `Texture* Texture::Load(std::string path)`
        
    Loads a texture from a file.

#### `void Texture::Bind()`
    
    Binds the texture.

#### `void Texture::Unbind()`

    Unbinds the texture.

#### `void Texture::SetFormat(Format format)`

    Sets the texture format.

#### `void Texture::SetFilter(Filter filter)`

    Sets the texture filter.

#### `void Texture::SetWrap(Wrap wrap)`

    [unimplemented yet]
    Sets the texture wrap.

#### `Format Texture::GetFormat()`

    Returns the texture format.

#### `Wrap Texture::GetWrap()`

    [unimplemented yet]
    Returns the texture wrap.

#### `int Texture::GetWidth()`

    Returns the texture width.

#### `int Texture::GetHeight()`

    Returns the texture height.

#### `glm::ivec2 Texture::GetSize()`

    Returns the texture dimensions.

### `class` Camera

### `class` Transform

### `class` WireBatch

## `namespace` wm

### `class` Window

## `class` es

#### Example

```c++
es::AddEventListener("event", [](const es::Event& event) {
    std::cout << "Event triggered!" << std::endl;
});
```

#### Methods

- [`void es::AddEventListener(std::string event, std::function<void()> callback)`](#void-esaddeventlistenerstdstring-event-stdfunctionvoid-callback)
- [`void es::TriggerEvent(std::string event)`](#void-estriggereventstdstring-event)
- [`void es::PollEvents()`](#void-espoll-events)

#### `void es::AddEventListener(std::string event, std::function<void()> callback)`

    Adds an event listener.

#### `void es::TriggerEvent(std::string event)`
        
    Triggers an event.

#### `void es::PollEvents()`
    
    Polls events.