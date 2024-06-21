#include "core/components/transform.hpp"
#include "core/engine.hpp"
#include "logger.hpp"

Engine::Engine()
{
    logger = new_unique<Logger>();

    asset_manager = new_unique<AssetManager>();
    asset_manager->engine = this;

    component_registry = new_unique<ComponentRegistry>();

    component_registry->register_component<Transform>("Transform");
}

void Engine::load_actor(const std::filesystem::path &path)
{
    auto actor = asset_manager->get<Actor>(path);

    if (!actor)
    {
        logger->error("Failed to load actor: {}", path.string());
        return;
    }

    actor->engine = this;

    root_actor = std::move(actor);
}