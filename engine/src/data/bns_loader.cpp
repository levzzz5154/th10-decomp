#include "th10/bns_loader.h"
#include <cstdio>
#include <cmath>

namespace th10 {

static void init_scene(BnsScene& s, const char* name, int id,
                       uint32_t clear_clr, float fog_s, float fog_e, uint32_t fog_clr,
                       const std::vector<BnsLayer>& ls) {
    s.stage_name  = name;
    s.stage_id    = id;
    s.clear_color = clear_clr;
    s.has_fog     = true;
    s.fog_start   = fog_s;
    s.fog_end     = fog_e;
    s.fog_color   = fog_clr;
    s.layers      = ls;
}

const BnsScene* GetDefaultStageScene(int stage_id) {
    static BnsScene scenes[7];
    static bool initialized = false;

    if (!initialized) {
        // Stage 1 - Mountain Valley
        init_scene(scenes[0], "stage01", 0, 0xFF204060, 600.0f, 3500.0f, 0xFF6080C0, {
            {0, 0.00f, 0.00f, 0, 0, 256, 256, -4000.0f, 0, 0, 1},
            {0, 0.25f, 0.00f, 0, 0, 256, 256, -3000.0f, 0, 0, 1},
            {0, 0.50f, 0.00f, 0, 0, 256, 256, -2000.0f, 0, 0, 1},
            {0, 1.00f, 0.00f, 0, 0, 256, 256, -1000.0f, 0, 0, 1},
        });

        // Stage 2 - Forest Trail
        init_scene(scenes[1], "stage02", 1, 0xFF002040, 800.0f, 4000.0f, 0xFF408060, {
            {0, 0.00f, 0.00f, 0, 0, 256, 384, -4000.0f, 0, 0, 1},
            {0, 0.30f, 0.00f, 0, 0, 256, 384, -3000.0f, 0, 0, 1},
            {0, 0.60f,-0.05f, 0, 0, 256, 384, -2000.0f, 0, 0, 1},
            {0, 1.20f, 0.00f, 0, 0, 256, 384, -1000.0f, 0, 0, 1},
        });

        // Stage 3 - Lake Shrine
        init_scene(scenes[2], "stage03", 2, 0xFF001030, 800.0f, 4000.0f, 0xFF6080A0, {
            {0, 0.00f, 0.00f, 0, 0, 256, 256, -5000.0f, 0, 0, 1},
            {0, 0.20f, 0.00f, 0, 0, 256, 256, -3500.0f, 0, 0, 1},
            {0, 0.45f, 0.00f, 0, 0, 256, 256, -2500.0f, 0, 0, 1},
            {0, 0.90f, 0.00f, 0, 0, 256, 256, -1200.0f, 0, 0, 1},
        });

        // Stage 4 - Autumn Hills
        init_scene(scenes[3], "stage04", 3, 0xFF402010, 800.0f, 4000.0f, 0xFFC08060, {
            {0, 0.00f, 0.00f, 0, 0, 256, 256, -4000.0f, 0, 0, 1},
            {0, 0.35f, 0.00f, 0, 0, 256, 256, -2800.0f, 0, 0, 1},
            {0, 0.70f,-0.10f, 0, 0, 256, 256, -1800.0f, 0, 0, 1},
            {0, 1.10f, 0.00f, 0, 0, 256, 256, -900.0f,  0, 0, 1},
        });

        // Stage 5 - Wind God Corridor
        init_scene(scenes[4], "stage05", 4, 0xFF102040, 800.0f, 4000.0f, 0xFF80A0C0, {
            {0, 0.00f, 0.00f, 0, 0, 256, 256, -5000.0f, 0, 0, 1},
            {0, 0.40f, 0.00f, 0, 0, 256, 256, -3500.0f, 0, 0, 1},
            {0, 0.75f, 0.05f, 0, 0, 256, 256, -2000.0f, 0, 0, 1},
            {0, 1.00f, 0.00f, 0, 0, 256, 256, -1000.0f, 0, 0, 1},
        });

        // Stage 6 - Final Shrine
        init_scene(scenes[5], "stage06", 5, 0xFF000008, 800.0f, 4000.0f, 0xFF4040A0, {
            {0, 0.00f, 0.00f, 0, 0, 256, 256, -5000.0f, 0, 0, 1},
            {0, 0.50f, 0.00f, 0, 0, 256, 256, -3000.0f, 0, 0, 1},
            {0, 0.80f,-0.15f, 0, 0, 256, 256, -2000.0f, 0, 0, 1},
            {0, 1.30f, 0.00f, 0, 0, 256, 256, -800.0f,  0, 0, 1},
        });

        // Extra Stage
        init_scene(scenes[6], "stage07", 6, 0xFF004040, 800.0f, 4000.0f, 0xFF408080, {
            {0, 0.00f, 0.00f, 0, 0, 256, 256, -5000.0f, 0, 0, 1},
            {0, 0.35f, 0.00f, 0, 0, 256, 256, -3000.0f, 0, 0, 1},
            {0, 0.70f, 0.00f, 0, 0, 256, 256, -1800.0f, 0, 0, 1},
            {0, 1.05f, 0.00f, 0, 0, 256, 256, -900.0f,  0, 0, 1},
        });

        initialized = true;
    }

    if (stage_id < 0 || stage_id >= 7) return &scenes[0];
    return &scenes[stage_id];
}

bool BnsLoader::load_stage_scene(BnsScene* out, int stage_id) {
    if (!out) return false;

    const BnsScene* default_scene = GetDefaultStageScene(stage_id);
    if (!default_scene) return false;

    *out = *default_scene;
    return true;
}

void BnsLoader::update_layer(BnsLayer* layer, float speed_factor) {
    if (!layer) return;

    layer->offset_x += layer->scroll_speed_x * speed_factor;
    layer->offset_y += layer->scroll_speed_y * speed_factor;

    if (layer->repeat && layer->width > 0) {
        float w = static_cast<float>(layer->width);
        while (layer->offset_x < 0) layer->offset_x += w;
        while (layer->offset_x >= w) layer->offset_x -= w;
    }
    if (layer->repeat && layer->height > 0) {
        float h = static_cast<float>(layer->height);
        while (layer->offset_y < 0) layer->offset_y += h;
        while (layer->offset_y >= h) layer->offset_y -= h;
    }
}

void BnsLoader::reset_offsets(BnsScene* scene) {
    if (!scene) return;
    for (auto& layer : scene->layers) {
        layer.offset_x = 0.0f;
        layer.offset_y = 0.0f;
    }
}

} // namespace th10
