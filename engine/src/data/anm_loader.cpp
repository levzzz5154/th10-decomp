#include "th10/anm_loader.h"
#include <cstdio>
#include <cstring>
#include <algorithm>

namespace th10 {

static constexpr int THTX_HEADER_SIZE = 20;

#pragma pack(push, 1)
struct ThtxHeader {
    char     magic[4];       // "THTX"
    uint32_t format_info;    // low 16 bits = format id
    uint16_t width;
    uint16_t height;
    uint32_t data_size;
    uint32_t zero;
};
#pragma pack(pop)
static_assert(sizeof(ThtxHeader) == 20, "ThtxHeader must be 20 bytes");

static TextureFormat thtx_format_to_gl(int fmt) {
    switch (fmt) {
    case  0: return TextureFormat::A4R4G4B4;  // 16-bit ARGB4444
    case 10: return TextureFormat::A8R8G8B8;  // 32-bit ARGB8888
    case  3: return TextureFormat::A1R5G5B5;  // 16-bit ARGB1555
    case  5: return TextureFormat::A4R4G4B4;  // 16-bit ARGB4444
    case  1: case 7: return TextureFormat::DXT1;
    case  2:            return TextureFormat::DXT3;
    case  9:            return TextureFormat::DXT5;
    default:  return TextureFormat::A4R4G4B4;  // most TH10 textures are 16-bit
    }
}

// ─── 8-bit indexed palette decoder (format 8) ────────────────────────────────

static uint8_t* decode_indexed_bgra(const uint8_t* idx_data, int w, int h,
                                    const uint8_t* pal_data, int pal_entries) {
    uint8_t* dst = new uint8_t[w * h * 4];
    const uint32_t* palette = (const uint32_t*)pal_data;
    for (int i = 0; i < w * h; i++) {
        uint8_t idx = idx_data[i];
        if (idx < pal_entries) {
            uint32_t c = palette[idx];
            dst[i * 4 + 0] = (c      ) & 0xFF;  // B
            dst[i * 4 + 1] = (c >>  8) & 0xFF;  // G
            dst[i * 4 + 2] = (c >> 16) & 0xFF;  // R
            dst[i * 4 + 3] = (c >> 24) & 0xFF;  // A
        } else {
            dst[i * 4 + 0] = 0;
            dst[i * 4 + 1] = 0;
            dst[i * 4 + 2] = 0;
            dst[i * 4 + 3] = 0;
        }
    }
    return dst;
}

// ─── entry -> frame UV normalization ─────────────────────────────────────────

static void normalize_uvs(std::vector<AnmFrameUV>& frames,
                          const AnmSpriteEntry* entries, size_t count,
                          float tex_w, float tex_h) {
    for (size_t i = 0; i < count; i++) {
        float x = entries[i].x;
        float y = entries[i].y;
        float w = entries[i].w;
        float h_val = entries[i].h;

        frames[i].u0 = x / tex_w;
        frames[i].v0 = y / tex_h;
        frames[i].u1 = (x + w) / tex_w;
        frames[i].v1 = (y + h_val) / tex_h;
        frames[i].id = (uint32_t)entries[i].frame_index;
    }
}

// =============================================================================
//  AnmLoader
// =============================================================================

AnmLoader::AnmLoader(Renderer* renderer)
    : renderer_(renderer) {}

AnmLoader::~AnmLoader() {
    unload();
}

void AnmLoader::unload() {
    for (auto& t : textures_) {
        if (t.gl_texture_id) {
            glDeleteTextures(1, (GLuint*)&t.gl_texture_id);
        }
    }
    textures_.clear();
    raw_data_.clear();
}

bool AnmLoader::load(const std::string& path) {
    unload();

    FILE* fp = fopen(path.c_str(), "rb");
    if (!fp) return false;

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    if (fsize < (long)sizeof(AnmSprite06)) {
        fclose(fp);
        return false;
    }
    rewind(fp);

    std::vector<uint8_t> file_data((size_t)fsize);
    if (fread(file_data.data(), 1, (size_t)fsize, fp) != (size_t)fsize) {
        fclose(fp);
        return false;
    }
    fclose(fp);

    int section_count = 0;
    uint32_t offset = 0;

    while (offset + sizeof(AnmSprite06) <= file_data.size() &&
           section_count < MAX_SECTIONS) {
        const AnmSprite06* hdr =
            (const AnmSprite06*)(file_data.data() + offset);

        if (hdr->sprite_count == 0) break;

        if (!load_section(file_data.data(), file_data.size(), offset))
            break;

        section_count++;

        if (hdr->next_offset == 0 || hdr->next_offset == offset)
            break;

        offset = hdr->next_offset;
        if (offset >= file_data.size()) break;
    }

    raw_data_.push_back(std::move(file_data));
    return !textures_.empty();
}

bool AnmLoader::load_section(const uint8_t* data, size_t data_size,
                             uint32_t section_off) {
    const AnmSprite06* hdr = (const AnmSprite06*)(data + section_off);
    uint32_t count = hdr->sprite_count;

    if (section_off + sizeof(AnmSprite06) > data_size)
        return false;
    if (count == 0 || count > 16384)
        return false;

    AnmTexture tex;

    uint32_t table_off = section_off + 0x40;
    if (table_off + count * 4 > data_size)
        return false;

    const uint32_t* offsets = (const uint32_t*)(data + table_off);

    std::vector<AnmSpriteEntry> entries;
    entries.reserve(count);

    for (uint32_t i = 0; i < count; i++) {
        uint32_t entry_off = offsets[i];
        if (entry_off + sizeof(AnmSpriteEntry) > data_size)
            break;
        const AnmSpriteEntry* entry = (const AnmSpriteEntry*)(data + entry_off);
        entries.push_back(*entry);
    }

    tex.frames.resize(entries.size());
    for (size_t i = 0; i < entries.size(); i++) {
        tex.frames[i].id = entries[i].frame_index;
    }

    if (!hdr->has_data || hdr->texture_offset == 0) {
        textures_.push_back(tex);
        return true;
    }

    uint32_t tex_off = section_off + hdr->texture_offset;
    if (tex_off + THTX_HEADER_SIZE > data_size) {
        textures_.push_back(tex);
        return true;
    }

    const ThtxHeader* thtx = (const ThtxHeader*)(data + tex_off);
    if (std::memcmp(thtx->magic, "THTX", 4) != 0) {
        textures_.push_back(tex);
        return true;
    }

    int w = thtx->width;
    int h = thtx->height;
    int fmt = (int)(thtx->format_info & 0xFFFF);
    uint32_t pixel_data_size = thtx->data_size;

    if (w <= 0 || h <= 0 || w > 4096 || h > 4096) {
        textures_.push_back(tex);
        return true;
    }
    if (pixel_data_size > data_size - tex_off - THTX_HEADER_SIZE) {
        textures_.push_back(tex);
        return true;
    }

    tex.width  = w;
    tex.height = h;

    const uint8_t* pixel_data = data + tex_off + THTX_HEADER_SIZE;
    TextureFormat gl_fmt = thtx_format_to_gl(fmt);
    const uint8_t* upload_pixels = pixel_data;
    uint8_t* decoded_pixels = nullptr;

    if (fmt == 8) {
        uint32_t pal_sz = 1024;
        if (pixel_data_size > pal_sz) {
            const uint8_t* idx_data = pixel_data;
            const uint8_t* pal_data = pixel_data + pixel_data_size - pal_sz;
            decoded_pixels = decode_indexed_bgra(idx_data, w, h, pal_data, 256);
            upload_pixels = decoded_pixels;
            gl_fmt = TextureFormat::A8R8G8B8;
        }
    }

    tex.gl_texture_id = renderer_->load_texture(upload_pixels, w, h, gl_fmt);
    delete[] decoded_pixels;

    float tw = (float)w;
    float th = (float)h;
    normalize_uvs(tex.frames, entries.data(), entries.size(), tw, th);

    textures_.push_back(tex);
    return true;
}

} // namespace th10
