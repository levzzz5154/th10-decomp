#include "th10/renderer.h"
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

namespace th10 {

// ============================================================
//  matrix helpers (D3DXMatrixLookAtLH / PerspectiveFovLH)
// ============================================================

static void mat4_identity(float* m) {
    std::memset(m, 0, 16 * sizeof(float));
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

static void mat4_perspective_fov_lh(float* m, float fov, float aspect, float nz, float fz) {
    std::memset(m, 0, 16 * sizeof(float));
    float h = 1.0f / std::tan(fov * 0.5f);
    float w = h / aspect;
    float q = fz / (fz - nz);
    m[0] = w;
    m[5] = h;
    m[10] = q;
    m[11] = 1.0f;
    m[14] = -q * nz;
}

static void mat4_look_at_lh(float* m,
                            float ex, float ey, float ez,
                            float ax, float ay, float az,
                            float ux, float uy, float uz) {
    float zx = ax - ex, zy = ay - ey, zz = az - ez;
    float zl = 1.0f / std::sqrt(zx*zx + zy*zy + zz*zz);
    zx *= zl; zy *= zl; zz *= zl;

    float xx = uy*zz - uz*zy;
    float xy = uz*zx - ux*zz;
    float xz = ux*zy - uy*zx;
    float xl = 1.0f / std::sqrt(xx*xx + xy*xy + xz*xz);
    xx *= xl; xy *= xl; xz *= xl;

    float yx = zy*xz - zz*xy;
    float yy = zz*xx - zx*xz;
    float yz = zx*xy - zy*xx;

    m[0] = xx;  m[1] = yx;  m[2] = zx;   m[3] = 0.0f;
    m[4] = xy;  m[5] = yy;  m[6] = zy;   m[7] = 0.0f;
    m[8] = xz;  m[9] = yz;  m[10] = zz;  m[11] = 0.0f;
    m[12] = -(xx*ex + xy*ey + xz*ez);
    m[13] = -(yx*ex + yy*ey + yz*ez);
    m[14] = -(zx*ex + zy*ey + zz*ez);
    m[15] = 1.0f;
}

// ============================================================
//  texture format helpers
// ============================================================

static inline uint8_t expand5(uint8_t v) { return (v << 3) | (v >> 2); }
static inline uint8_t expand6(uint8_t v) { return (v << 2) | (v >> 4); }
static inline uint8_t expand4(uint8_t v) { return (v << 4) | v; }

static uint8_t* convert_a4r4g4b4(const uint8_t* src, int w, int h) {
    int count = w * h;
    uint8_t* dst = new uint8_t[count * 4];
    for (int i = 0; i < count; i++) {
        uint16_t px = ((uint16_t)src[i*2]) | ((uint16_t)src[i*2+1] << 8);
        uint8_t b = expand4(px & 0xF);
        uint8_t g = expand4((px >> 4) & 0xF);
        uint8_t r = expand4((px >> 8) & 0xF);
        uint8_t a = expand4((px >> 12) & 0xF);
        dst[i*4+0] = r;
        dst[i*4+1] = g;
        dst[i*4+2] = b;
        dst[i*4+3] = a;
    }
    return dst;
}

static uint8_t* convert_a1r5g5b5(const uint8_t* src, int w, int h) {
    int count = w * h;
    uint8_t* dst = new uint8_t[count * 4];
    for (int i = 0; i < count; i++) {
        uint16_t px = ((uint16_t)src[i*2]) | ((uint16_t)src[i*2+1] << 8);
        uint8_t b = expand5(px & 0x1F);
        uint8_t g = expand5((px >> 5) & 0x1F);
        uint8_t r = expand5((px >> 10) & 0x1F);
        uint8_t a = (px & 0x8000) ? 0xFF : 0x00;
        dst[i*4+0] = r;
        dst[i*4+1] = g;
        dst[i*4+2] = b;
        dst[i*4+3] = a;
    }
    return dst;
}

// --- BC1 (DXT1) decompression ------------------------------------------------

static void decode_bc1_block(const uint8_t* block, uint8_t* out, int stride) {
    uint8_t c0_lo = block[0], c0_hi = block[1];
    uint8_t c1_lo = block[2], c1_hi = block[3];
    uint16_t c0 = c0_lo | (c0_hi << 8);
    uint16_t c1 = c1_lo | (c1_hi << 8);
    uint32_t idx = (uint32_t)block[4] | ((uint32_t)block[5] << 8)
                 | ((uint32_t)block[6] << 16) | ((uint32_t)block[7] << 24);

    uint8_t pal[4][4];
    pal[0][0] = expand5((c0 >> 11) & 0x1F);
    pal[0][1] = expand6((c0 >> 5) & 0x3F);
    pal[0][2] = expand5(c0 & 0x1F);
    pal[0][3] = 255;

    pal[1][0] = expand5((c1 >> 11) & 0x1F);
    pal[1][1] = expand6((c1 >> 5) & 0x3F);
    pal[1][2] = expand5(c1 & 0x1F);
    pal[1][3] = 255;

    if (c0 > c1) {
        pal[2][0] = (2*pal[0][0] + pal[1][0]) / 3;
        pal[2][1] = (2*pal[0][1] + pal[1][1]) / 3;
        pal[2][2] = (2*pal[0][2] + pal[1][2]) / 3;
        pal[2][3] = 255;
        pal[3][0] = (pal[0][0] + 2*pal[1][0]) / 3;
        pal[3][1] = (pal[0][1] + 2*pal[1][1]) / 3;
        pal[3][2] = (pal[0][2] + 2*pal[1][2]) / 3;
        pal[3][3] = 255;
    } else {
        pal[2][0] = (pal[0][0] + pal[1][0]) / 2;
        pal[2][1] = (pal[0][1] + pal[1][1]) / 2;
        pal[2][2] = (pal[0][2] + pal[1][2]) / 2;
        pal[2][3] = 255;
        pal[3][0] = 0;
        pal[3][1] = 0;
        pal[3][2] = 0;
        pal[3][3] = 0;
    }

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int bit = (y * 4 + x) * 2;
            int c = (idx >> bit) & 3;
            uint8_t* p = out + y * stride + x * 4;
            p[0] = pal[c][0];
            p[1] = pal[c][1];
            p[2] = pal[c][2];
            p[3] = pal[c][3];
        }
    }
}

static uint8_t* convert_bc1(const uint8_t* src, int w, int h) {
    int bw = (w + 3) / 4, bh = (h + 3) / 4;
    int stride = w * 4;
    uint8_t* dst = new uint8_t[w * h * 4];
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            int out_x = bx * 4, out_y = by * 4;
            const uint8_t* block = src + (by * bw + bx) * 8;
            uint8_t block_out[4 * 4 * 4];
            decode_bc1_block(block, block_out, 16);
            for (int y = 0; y < 4 && (out_y + y) < h; y++) {
                int copy_w = (out_x + 4 <= w) ? 16 : (w - out_x) * 4;
                std::memcpy(dst + (out_y + y) * stride + out_x * 4,
                            block_out + y * 16, copy_w);
            }
        }
    }
    return dst;
}

// --- BC2 (DXT3) decompression ------------------------------------------------

static void decode_bc2_block(const uint8_t* block, uint8_t* out, int stride) {
    // Bytes 0-7: explicit 4-bit alpha (16 nibbles)
    // Bytes 8-15: BC1 color (with color0 > color1 implied)
    uint64_t alpha_bits =
        (uint64_t)block[0]       | ((uint64_t)block[1] << 8) |
        ((uint64_t)block[2] << 16) | ((uint64_t)block[3] << 24) |
        ((uint64_t)block[4] << 32) | ((uint64_t)block[5] << 40) |
        ((uint64_t)block[6] << 48) | ((uint64_t)block[7] << 56);

    uint8_t alphas[16];
    for (int i = 0; i < 16; i++) {
        alphas[i] = expand4((alpha_bits >> (i * 4)) & 0xF);
    }

    uint8_t c0_lo = block[8], c0_hi = block[9];
    uint16_t c0 = c0_lo | (c0_hi << 8);
    uint8_t c1_lo = block[10], c1_hi = block[11];
    uint16_t c1 = c1_lo | (c1_hi << 8);
    uint32_t idx = (uint32_t)block[12] | ((uint32_t)block[13] << 8)
                 | ((uint32_t)block[14] << 16) | ((uint32_t)block[15] << 24);

    uint8_t pal[4][3];
    pal[0][0] = expand5((c0 >> 11) & 0x1F);
    pal[0][1] = expand6((c0 >> 5) & 0x3F);
    pal[0][2] = expand5(c0 & 0x1F);
    pal[1][0] = expand5((c1 >> 11) & 0x1F);
    pal[1][1] = expand6((c1 >> 5) & 0x3F);
    pal[1][2] = expand5(c1 & 0x1F);
    pal[2][0] = (2*pal[0][0] + pal[1][0]) / 3;
    pal[2][1] = (2*pal[0][1] + pal[1][1]) / 3;
    pal[2][2] = (2*pal[0][2] + pal[1][2]) / 3;
    pal[3][0] = (pal[0][0] + 2*pal[1][0]) / 3;
    pal[3][1] = (pal[0][1] + 2*pal[1][1]) / 3;
    pal[3][2] = (pal[0][2] + 2*pal[1][2]) / 3;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int bit = (y * 4 + x) * 2;
            int c = (idx >> bit) & 3;
            uint8_t* p = out + y * stride + x * 4;
            p[0] = pal[c][0];
            p[1] = pal[c][1];
            p[2] = pal[c][2];
            p[3] = alphas[y * 4 + x];
        }
    }
}

static uint8_t* convert_bc2(const uint8_t* src, int w, int h) {
    int bw = (w + 3) / 4, bh = (h + 3) / 4;
    int stride = w * 4;
    uint8_t* dst = new uint8_t[w * h * 4];
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            int out_x = bx * 4, out_y = by * 4;
            const uint8_t* block = src + (by * bw + bx) * 16;
            uint8_t block_out[4 * 4 * 4];
            decode_bc2_block(block, block_out, 16);
            for (int y = 0; y < 4 && (out_y + y) < h; y++) {
                int copy_w = (out_x + 4 <= w) ? 16 : (w - out_x) * 4;
                std::memcpy(dst + (out_y + y) * stride + out_x * 4,
                            block_out + y * 16, copy_w);
            }
        }
    }
    return dst;
}

// --- BC3 (DXT5) decompression ------------------------------------------------

static void decode_bc3_block(const uint8_t* block, uint8_t* out, int stride) {
    // Alpha: bytes 0-7
    uint8_t a0 = block[0], a1 = block[1];
    // 6 bytes of 3-bit indices: bytes 2-7, packed
    uint64_t alpha_idx = 0;
    for (int i = 0; i < 6; i++)
        alpha_idx |= ((uint64_t)block[2 + i]) << (i * 8);

    uint8_t alphas[8];
    alphas[0] = a0;
    alphas[1] = a1;
    if (a0 > a1) {
        alphas[2] = (6*a0 + 1*a1) / 7;
        alphas[3] = (5*a0 + 2*a1) / 7;
        alphas[4] = (4*a0 + 3*a1) / 7;
        alphas[5] = (3*a0 + 4*a1) / 7;
        alphas[6] = (2*a0 + 5*a1) / 7;
        alphas[7] = (1*a0 + 6*a1) / 7;
    } else {
        alphas[2] = (4*a0 + 1*a1) / 5;
        alphas[3] = (3*a0 + 2*a1) / 5;
        alphas[4] = (2*a0 + 3*a1) / 5;
        alphas[5] = (1*a0 + 4*a1) / 5;
        alphas[6] = 0;
        alphas[7] = 255;
    }

    uint8_t tex_alpha[16];
    for (int i = 0; i < 16; i++) {
        int shift = i * 3;
        int byte_off = shift / 8;
        int bit_off  = shift % 8;
        uint32_t raw = (uint32_t)(alpha_idx >> (byte_off * 8));
        int idx = (raw >> bit_off) & 7;
        tex_alpha[i] = alphas[idx];
    }

    // Color: bytes 8-15 (same as BC1 with c0 > c1)
    uint8_t c0_lo = block[8], c0_hi = block[9];
    uint16_t c0 = c0_lo | (c0_hi << 8);
    uint8_t c1_lo = block[10], c1_hi = block[11];
    uint16_t c1 = c1_lo | (c1_hi << 8);
    uint32_t cidx = (uint32_t)block[12] | ((uint32_t)block[13] << 8)
                  | ((uint32_t)block[14] << 16) | ((uint32_t)block[15] << 24);

    uint8_t pal[4][3];
    pal[0][0] = expand5((c0 >> 11) & 0x1F);
    pal[0][1] = expand6((c0 >> 5) & 0x3F);
    pal[0][2] = expand5(c0 & 0x1F);
    pal[1][0] = expand5((c1 >> 11) & 0x1F);
    pal[1][1] = expand6((c1 >> 5) & 0x3F);
    pal[1][2] = expand5(c1 & 0x1F);
    pal[2][0] = (2*pal[0][0] + pal[1][0]) / 3;
    pal[2][1] = (2*pal[0][1] + pal[1][1]) / 3;
    pal[2][2] = (2*pal[0][2] + pal[1][2]) / 3;
    pal[3][0] = (pal[0][0] + 2*pal[1][0]) / 3;
    pal[3][1] = (pal[0][1] + 2*pal[1][1]) / 3;
    pal[3][2] = (pal[0][2] + 2*pal[1][2]) / 3;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            int bit = (y * 4 + x) * 2;
            int c = (cidx >> bit) & 3;
            uint8_t* p = out + y * stride + x * 4;
            p[0] = pal[c][0];
            p[1] = pal[c][1];
            p[2] = pal[c][2];
            p[3] = tex_alpha[y * 4 + x];
        }
    }
}

static uint8_t* convert_bc3(const uint8_t* src, int w, int h) {
    int bw = (w + 3) / 4, bh = (h + 3) / 4;
    int stride = w * 4;
    uint8_t* dst = new uint8_t[w * h * 4];
    for (int by = 0; by < bh; by++) {
        for (int bx = 0; bx < bw; bx++) {
            int out_x = bx * 4, out_y = by * 4;
            const uint8_t* block = src + (by * bw + bx) * 16;
            uint8_t block_out[4 * 4 * 4];
            decode_bc3_block(block, block_out, 16);
            for (int y = 0; y < 4 && (out_y + y) < h; y++) {
                int copy_w = (out_x + 4 <= w) ? 16 : (w - out_x) * 4;
                std::memcpy(dst + (out_y + y) * stride + out_x * 4,
                            block_out + y * 16, copy_w);
            }
        }
    }
    return dst;
}

// ============================================================
//  Renderer implementation
// ============================================================

bool Renderer::init(int w, int h, const char* title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    width_ = w; height_ = h;
    window_ = SDL_CreateWindow(title,
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window_) {
        fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        return false;
    }

    gl_ctx_ = SDL_GL_CreateContext(window_);
    if (!gl_ctx_) {
        fprintf(stderr, "SDL_GL_CreateContext: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetSwapInterval(1);

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -100000, 100000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 1);

    // D3D defaults matching FUN_00439d20
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);       // D3DSHADE_GOURAUD

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 1.0f / 255.0f);

    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, fog_start_);
    glFogf(GL_FOG_END, fog_end_);
    {
        GLfloat fc[4] = {
            ((fog_color_ >> 16) & 0xFF) / 255.0f,
            ((fog_color_ >> 8) & 0xFF) / 255.0f,
            (fog_color_ & 0xFF) / 255.0f,
            1.0f
        };
        glFogfv(GL_FOG_COLOR, fc);
    }

    // Default camera matrices
    mat4_identity(view_matrix_);
    mat4_perspective_fov_lh(proj_matrix_, cam_fov_, cam_aspect_, cam_near_, cam_far_);

    fprintf(stdout, "[renderer] OpenGL %s | %dx%d | fog+alpha+depth enabled\n",
            glGetString(GL_VERSION), w, h);
    return true;
}

void Renderer::shutdown() {
    if (gl_ctx_) SDL_GL_DeleteContext(gl_ctx_);
    if (window_) SDL_DestroyWindow(window_);
    SDL_Quit();
    gl_ctx_ = nullptr;
    window_ = nullptr;
}

void Renderer::begin_frame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    sprite_count_ = 0;
    current_texture_ = -1;
    current_blend_ = BlendMode::Normal;
    current_filter_ = FilterMode::Linear;
}

void Renderer::end_frame() {
    flush();
    SDL_GL_SwapWindow(window_);
}

void Renderer::clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void Renderer::draw_sprite(int tex, float x, float y, float w, float h,
                           float u0, float v0, float u1, float v1,
                           uint32_t color, BlendMode blend, FilterMode filter) {
    if (tex != current_texture_ || sprite_count_ >= MAX_SPRITES ||
        blend != current_blend_ || filter != current_filter_) {
        flush();
    }

    current_texture_ = tex;
    current_blend_   = blend;
    current_filter_  = filter;

    // Convert ARGB → RGBA byte order in memory
    uint32_t rgba = (color & 0xFF00FF00) |
                    ((color >> 16) & 0xFF) |
                    ((color & 0xFF) << 16);

    float rhw = 1.0f;
    float z   = 0.0f;

    int vi = sprite_count_ * 6;
    float x1 = x + w, y1 = y + h;

    // Triangle 1: TL → TR → BL
    vertices_[vi+0] = {x,  y,  z, rhw, rgba, u0, v0};
    vertices_[vi+1] = {x1, y,  z, rhw, rgba, u1, v0};
    vertices_[vi+2] = {x,  y1, z, rhw, rgba, u0, v1};
    // Triangle 2: TR → BR → BL
    vertices_[vi+3] = {x1, y,  z, rhw, rgba, u1, v0};
    vertices_[vi+4] = {x1, y1, z, rhw, rgba, u1, v1};
    vertices_[vi+5] = {x,  y1, z, rhw, rgba, u0, v1};

    sprite_count_++;
}

void Renderer::flush() {
    if (sprite_count_ == 0) return;

    apply_gl_states();

    glBindTexture(GL_TEXTURE_2D, current_texture_);

    GLint filter = (current_filter_ == FilterMode::Point) ? GL_NEAREST : GL_LINEAR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    int stride = sizeof(RenderVertex);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, stride, &vertices_[0].x);
    glColorPointer(4, GL_UNSIGNED_BYTE, stride, &vertices_[0].color);
    glTexCoordPointer(2, GL_FLOAT, stride, &vertices_[0].u);

    glDrawArrays(GL_TRIANGLES, 0, sprite_count_ * 6);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    sprite_count_ = 0;
}

int Renderer::load_texture(const uint8_t* pixels, int w, int h, TextureFormat format) {
    if (!pixels || w <= 0 || h <= 0) return 0;

    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    switch (format) {
    case TextureFormat::A8R8G8B8:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
        break;
    case TextureFormat::A4R4G4B4: {
        uint8_t* rgba = convert_a4r4g4b4(pixels, w, h);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
        delete[] rgba;
        break;
    }
    case TextureFormat::A1R5G5B5: {
        uint8_t* rgba = convert_a1r5g5b5(pixels, w, h);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
        delete[] rgba;
        break;
    }
    case TextureFormat::DXT1: {
        uint8_t* rgba = convert_bc1(pixels, w, h);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
        delete[] rgba;
        break;
    }
    case TextureFormat::DXT3: {
        uint8_t* rgba = convert_bc2(pixels, w, h);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
        delete[] rgba;
        break;
    }
    case TextureFormat::DXT5: {
        uint8_t* rgba = convert_bc3(pixels, w, h);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
        delete[] rgba;
        break;
    }
    }

    return (int)tex;
}

void Renderer::set_camera(float ex, float ey, float ez,
                          float fov, float aspect, float nz, float fz) {
    cam_eye_[0] = ex; cam_eye_[1] = ey; cam_eye_[2] = ez;
    cam_fov_ = fov; cam_aspect_ = aspect; cam_near_ = nz; cam_far_ = fz;

    mat4_perspective_fov_lh(proj_matrix_, fov, aspect, nz, fz);
    mat4_look_at_lh(view_matrix_, ex, ey, ez,
                    ex, ey, 0.0f,   // look toward screen plane
                    0.0f, 1.0f, 0.0f);
}

void Renderer::get_view_matrix(float* out16) const {
    std::memcpy(out16, view_matrix_, 16 * sizeof(float));
}

void Renderer::get_proj_matrix(float* out16) const {
    std::memcpy(out16, proj_matrix_, 16 * sizeof(float));
}

// ============================================================
//  render state setters
// ============================================================

void Renderer::set_fog_enabled(bool enable) {
    fog_enabled_ = enable;
}

void Renderer::set_fog_params(float start, float end, uint32_t color) {
    fog_start_ = start;
    fog_end_   = end;
    fog_color_ = color;
}

void Renderer::set_alpha_test(bool enable, uint8_t ref) {
    alpha_test_enabled_ = enable;
    alpha_ref_ = ref;
}

void Renderer::set_cull_mode(CullMode mode) {
    cull_mode_ = mode;
}

void Renderer::set_depth_test(bool enable) {
    depth_test_enabled_ = enable;
}

void Renderer::set_viewport(int x, int y, int w, int h) {
    glViewport(x, y, w, h);
}

void Renderer::apply_gl_states() {
    if (current_blend_ == BlendMode::Additive) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    } else {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    if (fog_enabled_) {
        glEnable(GL_FOG);
        glFogf(GL_FOG_START, fog_start_);
        glFogf(GL_FOG_END, fog_end_);
        GLfloat fc[4] = {
            ((fog_color_ >> 16) & 0xFF) / 255.0f,
            ((fog_color_ >> 8) & 0xFF) / 255.0f,
            (fog_color_ & 0xFF) / 255.0f,
            1.0f
        };
        glFogfv(GL_FOG_COLOR, fc);
    } else {
        glDisable(GL_FOG);
    }

    if (alpha_test_enabled_) {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GEQUAL, alpha_ref_ / 255.0f);
    } else {
        glDisable(GL_ALPHA_TEST);
    }

    if (depth_test_enabled_) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    switch (cull_mode_) {
    case CullMode::None:
        glDisable(GL_CULL_FACE);
        break;
    case CullMode::CW:
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_FRONT);
        break;
    case CullMode::CCW:
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        break;
    }
}

} // namespace th10
