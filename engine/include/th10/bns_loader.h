/*
 * TH10 BNS Background Scene Loader
 * Based on Ghidra RE: background layers use ANM textures with
 * scrolling parallax.  BNS data is embedded in stageXX.std
 * or derived from stageXX.anm texture layout.
 *
 * Architecture: game maps stageXX.anm sub-textures to layers
 * at fixed z-depths, each with independent scroll coefficients.
 */
#pragma once
#include "th10/types.h"
#include <vector>
#include <string>

namespace th10 {

struct BnsLayer {
    int     texture_id;       // OpenGL texture handle (loaded from ANM)
    float   scroll_speed_x;   // pixels per frame horizontal
    float   scroll_speed_y;   // pixels per frame vertical
    float   offset_x;         // current scroll offset
    float   offset_y;
    int     width;            // texture pixel width
    int     height;           // texture pixel height
    float   depth_z;          // 3D depth for fog (higher = farther)
    float   origin_x;         // screen-relative origin
    float   origin_y;
    int     repeat;           // 0=once, 1=repeat tile
};

struct BnsScene {
    std::string   stage_name;        // e.g. "stage01"
    int           stage_id;
    std::vector<BnsLayer> layers;    // back-to-front ordered
    uint32_t       clear_color;      // D3DCOLOR background clear
    bool           has_fog;
    float          fog_start;
    float          fog_end;
    uint32_t       fog_color;
};

class BnsLoader {
public:
    BnsLoader() = default;
    ~BnsLoader() = default;

    bool load_stage_scene(BnsScene* out, int stage_id);

    const BnsScene* current_scene() const { return current_ ? &current_scene_ : nullptr; }

    void update_layer(BnsLayer* layer, float speed_factor = 1.0f);

    void reset_offsets(BnsScene* scene);

    void set_scene(const BnsScene& scene) { current_scene_ = scene; current_ = true; }

    bool is_loaded() const { return current_; }

private:
    BnsScene current_scene_;
    bool     current_ = false;
};

const BnsScene* GetDefaultStageScene(int stage_id);

} // namespace th10
