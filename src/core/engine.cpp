#include "core/engine.hpp"
#include "logger.hpp"

Engine::Engine()
{
    logger = new_unique<Logger>();
    asset_manager = new_unique<AssetManager>();
    component_registry = new_unique<ComponentRegistry>();
}

void Engine::load_actor(const std::filesystem::path &path)
{
    auto actor = asset_manager->get<Actor>(path);

    if (!actor)
    {
        logger->error("Failed to load actor: {}", path.string());
        return;
    }

    root_actor = std::move(actor);
}