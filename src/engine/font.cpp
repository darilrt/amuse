#include <cstdint>
#include <fstream>

#include "engine/font.hpp"
#include "logger.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.hpp"

#define FONT_TEXTURE_SIZE 512

uint8_t temp_bitmap[FONT_TEXTURE_SIZE * FONT_TEXTURE_SIZE];

Font::Font(const char *path, int size)
{
    uint8_t *ttf_buffer;

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        logger.panic("Failed to open font file '{}'", path);
    }

    file.seekg(0, std::ios::end);
    size_t size_bytes = file.tellg();
    file.seekg(0, std::ios::beg);
    ttf_buffer = new uint8_t[size_bytes];
    file.read(reinterpret_cast<char *>(ttf_buffer), size_bytes);
    file.close();

    cdata = new stbtt_bakedchar[96];

    stbtt_BakeFontBitmap(ttf_buffer, 0, size, temp_bitmap, FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 32, 96, reinterpret_cast<stbtt_bakedchar *>(cdata));

    _texture = new_shared<Texture>(
        FONT_TEXTURE_SIZE,
        FONT_TEXTURE_SIZE,
        gfx::TextureFormat::R,
        gfx::SamplerFilter::Linear,
        gfx::SamplerFilter::Linear,
        gfx::SamplerWrap::ClampToEdge,
        gfx::SamplerWrap::ClampToEdge);

    _texture->image.set_data(temp_bitmap, FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 1);
}

Font::~Font()
{
}

void Font::get_text_size(const char *text, int *width, int *height)
{
    *width = 0;
    *height = 0;

    float x = 0;
    float y = 0;
    for (const char *c = text; *c; c++)
    {
        if (*c == '\n')
        {
            x = 0;
            y += 1;
        }
        else
        {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(reinterpret_cast<stbtt_bakedchar *>(cdata), FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, *c - 32, &x, &y, &q, 1);
            *width = std::max(*width, static_cast<int>(q.x1));
            *height = std::max(*height, static_cast<int>(q.y1));
        }
    }
}

Vec2i Font::get_text_mesh(const char *text, float x, float y, std::vector<float> &vertices, std::vector<float> &uvs)
{
    float start_x = x;
    float start_y = y;

    float width = 0;
    float height = 0;

    for (const char *c = text; *c; c++)
    {
        if (*c == '\n')
        {
            x = start_x;
            y += 1;
        }
        else
        {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(reinterpret_cast<stbtt_bakedchar *>(cdata), FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, *c - 32, &x, &y, &q, 1);

            width = std::max(width, q.x1);
            height = std::max(height, q.y1);

            vertices.insert(vertices.end(),
                            {q.x0, q.y0, 0.0f,
                             q.x1, q.y1, 0.0f,
                             q.x1, q.y0, 0.0f,
                             q.x1, q.y1, 0.0f,
                             q.x0, q.y0, 0.0f,
                             q.x0, q.y1, 0.0f});

            uvs.insert(uvs.end(),
                       {q.s0, q.t0,
                        q.s1, q.t1,
                        q.s1, q.t0,
                        q.s1, q.t1,
                        q.s0, q.t0,
                        q.s0, q.t1});
        }
    }

    return Vec2i(width, height);
}