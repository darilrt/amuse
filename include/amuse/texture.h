#pragma once

#include <cstdint>
#include <string>

#include <glm/glm.hpp>

namespace gl {

    class Texture {
    public:
        enum class Format : uint32_t {
            RGB     = 0x1907,
            RGBA    = 0x1908,
            DEPTH16 = 0x81A5,
            DEPTH24 = 0x81A6,
            DEPTH32 = 0x81A7,
        };

        enum class Filter : int32_t {
            NEAREST = 0x2600,
            LINEAR  = 0x2601,
        };
        
        Texture();

        ~Texture();

        void Bind();

        void Unbind();

        void SetSize(uint32_t width, uint32_t height);

        inline uint32_t GetID() const { return id; }

        inline void SetFormat(Format format) { this->format = format; }

        void SetFilter(Filter filter);

        static Texture* Load(const char* path);

        static Texture& LoadAsset(const std::string& assetPath) {
            return *Load(assetPath.c_str());
        }

        inline Format GetFormat() const { return format; }

        inline uint32_t GetWidth() const { return width; }

        inline uint32_t GetHeight() const { return height; }

        inline glm::ivec2 GetSize() const { return glm::ivec2(width, height); }

    private:
        Format format = Format::RGBA;
        uint32_t id;
        uint32_t width = 0;
        uint32_t height = 0;
    };
    
}
