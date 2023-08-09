#pragma once

#include "amuse/ecs.h"

class SceneManager {
public:
    static void Update();

    static void Render();

    template <typename T>
    static void AddScene() {
        GetSystemManager()->AddSystem<T>();
    }

    template <typename T>
    static void SetActiveScene() {
        GetSystemManager()->SetActiveSystem<T>();
    }

private:
    static ecs::SystemManager* systemManager;

    static ecs::SystemManager* GetSystemManager() {
        if (!systemManager) {
            systemManager = new ecs::SystemManager();
        }
        return systemManager;
    }
};