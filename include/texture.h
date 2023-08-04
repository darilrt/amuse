#pragma once

#include <cstdint>

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
        
        Texture();
        ~Texture();

        void Bind();
        void Unbind();

        void SetSize(uint32_t width, uint32_t height);

        inline uint32_t GetID() const { return id; }

        inline void SetFormat(Format format) { this->format = format; }

        static Texture* Load(const char* path);

    private:
        Format format = Format::RGBA;
        uint32_t id;
    };
    
}
