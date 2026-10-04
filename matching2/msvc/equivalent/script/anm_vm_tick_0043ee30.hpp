// Types for the 0x0043EE30 equivalent recovery (ANM VM tick).
#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

extern "C" float g_game_speed;      // 0x00476F78
extern "C" float data_00470b04;     // 0.0f
struct Float3 {
    float x, y, z;
    Float3() {}
    Float3(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
};
struct Rgb {
    unsigned char b, g, r;
    Rgb() {}
    Rgb(unsigned char r_, unsigned char g_, unsigned char b_) : b(b_), g(g_), r(r_) {}
};
struct Float2 {
    float x, y;
    Float2() {}
    Float2(float x_, float y_) { x = x_; y = y_; }
};
extern "C" Float3 g_zero_vector;    // 0x00491C14
extern "C" Float3 g_scroll_step;    // 0x00491E6C

struct FrameTimer {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;

    __declspec(noinline) void Set(int value);       // 0x00405410
    __declspec(noinline) void Advance(float delta); // 0x0044BF40
    __declspec(noinline) void Decrement(int count); // 0x00428DD0
    __forceinline void Tick() {
        previous = current;
        if (*speed > 0.99f && *speed < 1.01f) {
            ++current;
            elapsed += 1.0f;
        } else {
            current = int(elapsed += *speed);
        }
    }
};

struct RngState {
    unsigned short seed;
    unsigned short reserved;
    unsigned int generation;
    __declspec(noinline) unsigned int NextModulo(unsigned int modulus); // 0x0043CB80
    __declspec(noinline) float NextFloat();                             // 0x0044BB20
};
extern "C" RngState g_replay_rng;   // 0x004918A8
extern "C" RngState g_effect_rng;   // 0x004918B0

float __stdcall Angle_NormalizeSum(float angle, float delta);           // 0x0044BC10

struct Float3Interp {
    Float3 initial;
    Float3 goal;
    Float3 control_1;
    Float3 control_2;
    FrameTimer timer;
    int end_time;
    int mode;
    __declspec(noinline) void Restart();                 // 0x004050D0
    __declspec(noinline) Float3 Evaluate();  // 0x00404610
};
struct Int3 {
    int r, g, b;
    Int3() {}
    Int3(int r_, int g_, int b_) : r(r_), g(g_), b(b_) {}
    Int3 operator*(float t) const;                       // 0x00441E50
    explicit Int3(const unsigned char* bytes) {
        b = bytes[2];
        g = bytes[1];
        r = bytes[0];
    }
};
struct ColorInterp {
    Int3 initial, goal, control_1, control_2;
    FrameTimer timer;
    int end_time;
    int mode;
    __declspec(noinline) Int3 Evaluate();      // 0x00441600
};
struct IntInterp {
    int initial, goal, control_1, control_2;
    FrameTimer timer;
    int end_time;
    int mode;
    __declspec(noinline) int Evaluate();                 // 0x00441950
};
struct Float2Interp {
    Float2 initial, goal, control_1, control_2;
    FrameTimer timer;
    int end_time;
    int mode;
    __declspec(noinline) Float2 Evaluate();  // 0x00441AD0
};

struct AnmInstr {
    short id;
    unsigned short size;
    short time;
    unsigned short var_mask;
    union {
        int i[6];
        float f[6];
        unsigned char b[24];
        unsigned short w[12];
    };
};

struct AnmSprite {
    unsigned char unknown_00[0x20];
    float u0;      // +0x20
    float unknown_24;
    float u1;      // +0x28
};

struct AnmVertex {
    Float2 position_xy;
    float z;
    float w;
    unsigned int color;
    float u, v;
    __declspec(noinline) AnmVertex* SetPolar(float angle, float radius); // 0x00441EF0
};

struct ListNode {
    void* owner;
    ListNode* next;
    ListNode* previous;
};
__declspec(noinline) void __stdcall List_InsertAfter(ListNode* position, ListNode* node); // 0x00413200

struct AnmHandle { unsigned int value; };
struct AnmLoaded;
struct AnmVm;
AnmHandle* __stdcall Anm_CreatePrimaryBack(AnmLoaded* anm, AnmHandle* out, int script, int layer);    // 0x00448D00
AnmHandle* __stdcall Anm_CreatePrimaryFront(AnmLoaded* anm, AnmHandle* out, int script, int layer);   // 0x00448E30
AnmHandle* __stdcall Anm_CreateSecondaryBack(AnmLoaded* anm, AnmHandle* out, int script, int layer);  // 0x00448F60
AnmHandle* __stdcall Anm_CreateSecondaryFront(AnmLoaded* anm, AnmHandle* out, int script, int layer); // 0x00449090
__declspec(noinline) AnmVm* __stdcall Anm_Resolve(AnmHandle* handle);                                  // 0x00449450
struct AnmLoaded {
    __declspec(noinline) int SetSprite(AnmVm* vm, int sprite);  // 0x0043E5A0
};

struct AnmVm {
    unsigned char unknown_000[0x10];
    ListNode node;              // +0x010
    unsigned char unknown_01c[4];
    int layer;                  // +0x020
    Float3 rotation;            // +0x024
    Float3 angular_velocity;    // +0x030
    Float2 scale;               // +0x03C
    Float2 scale_growth;        // +0x044
    unsigned char unknown_04c[8];
    Float2 uv_scroll;           // +0x054
    FrameTimer time;            // +0x05C
    Float3Interp position_interp;   // +0x070
    ColorInterp color_interp;       // +0x0BC
    IntInterp alpha_interp;         // +0x108
    Float3Interp rotation_interp;   // +0x134
    Float2Interp scale_interp;      // +0x180
    ColorInterp color2_interp;      // +0x1BC
    IntInterp alpha2_interp;        // +0x208
    Float2 uv_scroll_speed;     // +0x234
    unsigned char unknown_23c[0x2FC - 0x23C];
    unsigned char blue, green, red, alpha;      // +0x2FC
    unsigned char blue2, green2, red2, alpha2;  // +0x300
    short pending_interrupt;    // +0x304
    AnmLoaded* anm;             // +0x308
    int int_vars[4];            // +0x30C
    float float_vars[4];        // +0x31C
    int int_vars2[2];           // +0x32C
    Float3 position;            // +0x334
    Float3 offset;              // +0x340
    Float3 position2;           // +0x34C
    AnmVertex* strip;           // +0x358
    union {
        unsigned int flags;     // +0x35C
        struct {
            unsigned int visible : 1;       // 0
            unsigned int f1 : 1;
            unsigned int rotated : 1;       // 2
            unsigned int scaled : 1;        // 3
            unsigned int blend : 2;         // 4
            unsigned int f6 : 2;
            unsigned int alt_position : 1;  // 8
            unsigned int flip_x : 1;        // 9
            unsigned int flip_y : 1;        // 10
            unsigned int f11 : 1;           // 11
            unsigned int stopped : 1;       // 12
            unsigned int f13 : 1;           // 13
            unsigned int f14 : 1;
            unsigned int f15 : 1;           // 15
            unsigned int f16 : 1;
            unsigned int paused : 1;        // 17
            unsigned int scroll_x_mode : 2; // 18
            unsigned int scroll_y_mode : 2; // 20
            unsigned int type : 4;          // 22
            unsigned int f26 : 1;
            unsigned int f27 : 1;           // 27
            unsigned int f28 : 1;           // 28
            unsigned int f29 : 1;           // 29
            unsigned int f30 : 1;           // 30
            unsigned int f31 : 1;           // 31
        };
    };
    unsigned char unknown_360[8];
    FrameTimer saved_time;      // +0x368
    AnmInstr* saved_pc;         // +0x37C
    int sprite_time;            // +0x380
    unsigned char unknown_384[8];
    AnmInstr* script;           // +0x38C
    AnmInstr* pc;               // +0x390
    AnmSprite* sprite;          // +0x394

    __declspec(noinline) int IntVar(int id);                 // 0x0043EC70
    __declspec(noinline) float FloatVar(float id);           // 0x0043EAC0
    __declspec(noinline) void StartAlpha(int end_time, unsigned char mode, unsigned char initial, unsigned char goal);   // 0x00442300
    __declspec(noinline) void StartAlpha2(int end_time, unsigned char mode, unsigned char initial, unsigned char goal);  // 0x00441F50
    __declspec(noinline) void StartColor(const unsigned char* initial, const unsigned char* goal, int end_time, unsigned char mode);   // 0x00442220
    __declspec(noinline) void StartColor2(const unsigned char* initial, const unsigned char* goal, int end_time, unsigned char mode);  // 0x00442050
    __declspec(noinline) void StartScale(const Float2* initial, const Float2* goal, int end_time, unsigned char mode);                // 0x0041AB70
    __declspec(noinline) void InitRing();                    // 0x004452F0

    static int __stdcall Tick(AnmVm* vm);                    // 0x0043EE30
};

__declspec(noinline) int* __stdcall Anm_IntRef(int* value, AnmVm* vm, int index, unsigned short mask);       // 0x0043EDA0
__declspec(noinline) float* __stdcall Anm_FloatRef(AnmVm* vm, int index, float* value, unsigned short mask); // 0x0043ED00

typedef char AnmVm_pc_check[offsetof(AnmVm, pc) == 0x390 ? 1 : -1];
typedef char AnmVm_flags_check[offsetof(AnmVm, flags) == 0x35C ? 1 : -1];
typedef char AnmVm_uvs_check[offsetof(AnmVm, uv_scroll_speed) == 0x234 ? 1 : -1];
typedef char AnmVm_col_check[offsetof(AnmVm, blue) == 0x2FC ? 1 : -1];
