#include "logger.hpp"
#include "core/actor.hpp"
#include "toml.hpp"

void Actor::start()
{
    for (auto &component : components)
    {
        component->on_start();
    }

    for (auto &child : children)
    {
        child->start();
    }
}

void Actor::update()
{
    for (auto &component : components)
    {
        component->on_update();
    }

    for (auto &child : children)
    {
        child->update();
    }
}

Shared<Actor> load_actor_helper(const toml::value &data)
{
    Shared<Actor> actor = new_shared<Actor>();

    if (data.contains("name"))
        actor->name = toml::find<std::string>(data, "name");

    if (data.contains("path"))
        actor->path = toml::find<std::string>(data, "path");

    if (!actor->path.empty())
        logger.info("Loading actor: {}", actor->path);

    if (data.contains("children"))
    {
        auto children = toml::find(data, "children");

        for (auto &child_data : children.as_array())
        {
            Shared<Actor> child = load_actor_helper(child_data);
            child->parent = actor;
            actor->children.push_back(child);
        }
    }

    return actor;
}

Shared<Actor> Actor::load(const std::filesystem::path &path)
{
    auto data = toml::parse(path.string());

    Shared<Actor> actor = load_actor_helper(data);
    actor->path = path.string();

    return actor;
}

void save_actor_helper(Actor *actor, toml::value &data)
{
    data["name"] = actor->name;
    data["path"] = actor->path;

    // for (auto &component : actor->components)
    // {
    //     toml::value component_data;
    //     component->on_inspector(component_data);
    //     data["components"].push_back(component_data);
    // }

    if (actor->children.size() == 0)
        return;

    data["children"] = toml::array{}; // [1

    for (auto &child : actor->children)
    {
        toml::value child_data;
        save_actor_helper(child.get(), child_data);
        data["children"].push_back(child_data);
    }
}

void Actor::save()
{
    toml::value data;

    save_actor_helper(this, data);

    std::ofstream file(path);
    file << data;
    file.close();
}