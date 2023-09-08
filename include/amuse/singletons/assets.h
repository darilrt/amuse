#pragma once

#include <unordered_map>
#include <string>

class Assets {
public:
    static void Init(const std::string& basePath);
    static void Destroy();

    template<typename T>
    static std::unordered_map<std::string, T*>& GetAssetList() {
        static std::unordered_map<std::string, T*> assets;
        return assets;
    }

    template<typename T>
    static T& Get(const std::string& name) {
        auto it = GetAssetList<T>().find(name);

        if (it == GetAssetList<T>().end()) {
            T& asset = T::LoadAsset(basePath + name);
            GetAssetList<T>()[name] = &asset;
            
            return asset;
        }
        
        return *it->second;
    }

private:
    static std::string basePath;
};