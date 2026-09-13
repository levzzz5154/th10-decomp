#ifndef TH10_QUAD_BATCH_HPP
#define TH10_QUAD_BATCH_HPP
struct AnimationManager_00442F50 {
    unsigned char unknown_00000000[0x58];
    int draw_calls;
    unsigned char unknown_0000005C[0x3ADAC8 - 0x5C];
    int quad_count;
    unsigned char unknown_003ADACC[0x72DACC - 0x3ADACC];
    void* cursor;
    void* batch_start;

    __declspec(noinline) int Flush();
};

struct ScreenRect { float left, top, right, bottom; };
__declspec(noinline) int __stdcall DrawSolidQuad(const ScreenRect*, unsigned int);
extern "C" AnimationManager_00442F50* data_00491c10;
struct RenderDevice {
    void** vtable;
    long Stage(unsigned int stage, unsigned int state, unsigned int value) {
        typedef long (__stdcall *Call)(void*, unsigned int, unsigned int, unsigned int);
        return ((Call)vtable[0x10C / 4])(this, stage, state, value);
    }
    long State(unsigned int state, unsigned int value) {
        typedef long (__stdcall *Call)(void*, unsigned int, unsigned int);
        return ((Call)vtable[0xE4 / 4])(this, state, value);
    }
    long Format(unsigned int format) {
        typedef long (__stdcall *Call)(void*, unsigned int);
        return ((Call)vtable[0x164 / 4])(this, format);
    }
    long Draw(unsigned int type, unsigned int count, const void* vertices, unsigned int stride) {
        typedef long (__stdcall *Call)(void*, unsigned int, unsigned int, const void*, unsigned int);
        return ((Call)vtable[0x14C / 4])(this, type, count, vertices, stride);
    }
    long Clear(unsigned int count, const void* rects, unsigned int flags,
               unsigned int color, float depth, unsigned int stencil) {
        typedef long (__stdcall *Call)(void*, unsigned int, const void*, unsigned int, unsigned int, float, unsigned int);
        return ((Call)vtable[0xAC / 4])(this, count, rects, flags, color, depth, stencil);
    }
    long Present(const void* source, const void* dest, void* window, const void* dirty) {
        typedef long (__stdcall *Call)(void*, const void*, const void*, void*, const void*);
        return ((Call)vtable[0x44 / 4])(this, source, dest, window, dirty);
    }
    long Reset(void* parameters) {
        typedef long (__stdcall *Call)(void*, void*);
        return ((Call)vtable[0x40 / 4])(this, parameters);
    }
    long Viewport(const void* viewport) {
        typedef long (__stdcall *Call)(void*, const void*);
        return ((Call)vtable[0xBC / 4])(this, viewport);
    }
};
extern "C" RenderDevice* data_00491c30;
struct DeviceViewport { unsigned int x, y, width, height; float min_z, max_z; };
extern "C" DeviceViewport data_00491cf4;
extern "C" char data_00491d0c[];
__declspec(noinline) int __stdcall ClearAndPresentTwice(unsigned int color);
struct SolidPosition {
    float x, y, z;
    SolidPosition(float px, float py, float pz) : x(px), y(py), z(pz) {}
    SolidPosition() {}
};
struct SolidVertex {
    SolidPosition position;
    float rhw;
    unsigned int color;
};
__declspec(noinline) int __stdcall DrawGradientQuad(const ScreenRect*, unsigned int, unsigned int, unsigned int, unsigned int);
#endif
