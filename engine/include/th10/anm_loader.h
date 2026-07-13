/*
 * ANM06 sprite/animation loader for TH10 format.
 * Reads .anm files, decodes THTX textures, and creates OpenGL textures.
 */
#pragma once
#include "th10/anm_types.h"
#include "th10/renderer.h"
#include <string>
#include <vector>
#include <cstdint>

namespace th10 {

class AnmLoader {
public:
    explicit AnmLoader(Renderer* renderer);
    ~AnmLoader();

    bool load(const std::string& path);
    void unload();

    const std::vector<AnmTexture>& textures() const { return textures_; }

private:
    static constexpr int MAX_SECTIONS = 256;

    bool load_section(const uint8_t* data, size_t data_size,
                      uint32_t section_off);

    Renderer* renderer_;
    std::vector<AnmTexture> textures_;
    std::vector<std::vector<uint8_t>> raw_data_;
};

} // namespace th10
