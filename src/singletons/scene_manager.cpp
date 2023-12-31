#include "amuse/singletons/scene_manager.h"

ecs::SystemManager* SceneManager::systemManager = nullptr;

void SceneManager::Start() {
    GetSystemManager()->Start();
}

void SceneManager::Update() {
    GetSystemManager()->Update();
}

void SceneManager::Render() {
    GetSystemManager()->Render();
}