#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cstdint>

namespace th10 {

static constexpr int MAX_SPRITES = 2048;

#pragma pack(push, 1)
struct RenderVertex {
    float    x, y, z;      // 12 bytes - screen-space (D3DFVF_XYZRHW)
    float    rhw;           //  4 bytes - reciprocal homogeneous w
    uint32_t color;         //  4 bytes - RGBA byte order in memory (GL native)
    float    u, v;          //  8 bytes - texture coordinates
};
#pragma pack(pop)
static_assert(sizeof(RenderVertex) == 28, "RenderVertex must be 28 bytes");

enum class BlendMode {
    Normal,    // SRCALPHA / INVSRCALPHA
    Additive,  // SRCALPHA / ONE
};

enum class FilterMode {
    Linear,
    Point,
};

enum class TextureFormat {
    A8R8G8B8,
    A4R4G4B4,
    A1R5G5B5,
    DXT1,
    DXT3,
    DXT5,
};

enum class CullMode {
    None = 0,
    CW   = 1,
    CCW  = 2,
};

class Renderer {
public:
    bool init(int width, int height, const char* title);
    void shutdown();

    void begin_frame();
    void end_frame();
    void clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);

    void draw_sprite(int texture_id,
                     float x, float y, float w, float h,
                     float u0, float v0, float u1, float v1,
                     uint32_t color = 0xFFFFFFFF,
                     BlendMode blend = BlendMode::Normal,
                     FilterMode filter = FilterMode::Linear);

    void flush();
    int  sprite_count() const { return sprite_count_; }

    int  load_texture(const uint8_t* pixels, int w, int h,
                      TextureFormat format = TextureFormat::A8R8G8B8);

    void set_camera(float eye_x, float eye_y, float eye_z,
                    float fov, float aspect, float near_z, float far_z);
    void get_view_matrix(float* out16) const;
    void get_proj_matrix(float* out16) const;

    void set_fog_enabled(bool enable);
    void set_fog_params(float start, float end, uint32_t color);

    void set_alpha_test(bool enable, uint8_t ref = 1);
    void set_cull_mode(CullMode mode);
    void set_depth_test(bool enable);
    void set_viewport(int x, int y, int w, int h);

    int  width()  const { return width_; }
    int  height() const { return height_; }

private:
    void apply_gl_states();

    SDL_Window*   window_ = nullptr;
    SDL_GLContext gl_ctx_ = nullptr;
    int width_  = 640;
    int height_ = 480;

    RenderVertex vertices_[MAX_SPRITES * 6];
    int          sprite_count_ = 0;

    int         current_texture_ = -1;
    BlendMode   current_blend_   = BlendMode::Normal;
    FilterMode  current_filter_  = FilterMode::Linear;

    bool     fog_enabled_       = true;
    float    fog_start_         = 1000.0f;
    float    fog_end_           = 5000.0f;
    uint32_t fog_color_         = 0xFFA0A0A0;

    bool     alpha_test_enabled_ = true;
    uint8_t  alpha_ref_          = 1;

    CullMode cull_mode_         = CullMode::CW;
    bool     depth_test_enabled_ = true;

    float    cam_eye_[3] = {0, 0, 0};
    float    cam_fov_    = 0.314f;
    float    cam_aspect_ = 1.333f;
    float    cam_near_   = 1.0f;
    float    cam_far_    = 5000.0f;

    float    view_matrix_[16];
    float    proj_matrix_[16];
};

} // namespace th10
