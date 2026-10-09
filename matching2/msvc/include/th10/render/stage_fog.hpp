#ifndef TH10_RENDER_STAGE_FOG_HPP
#define TH10_RENDER_STAGE_FOG_HPP

// Fog settings of a stage: the range, the colour as four float channels so a
// script can blend it, and the same colour packed for the device.
struct StageFog {
    float start, end;
    float blue, green, red, alpha;
    union {
        unsigned int packed;               // the colour as the device takes it
        struct {
            unsigned char packed_blue, packed_green, packed_red, packed_alpha;
        };
    };

    StageFog() {}
    StageFog(float fog_start, float fog_end, float b, float g, float r, float a);

    __declspec(noinline) StageFog operator+(const StageFog& v) const;
    __declspec(noinline) StageFog operator-(const StageFog& v) const;
    __declspec(noinline) StageFog operator*(float f) const;
};
typedef char StageFogSize[sizeof(StageFog) == 0x1C ? 1 : -1];

// 0x00405040: the constructor, where it is not expanded in place.
#pragma code_seg(push, ".text$00405040_fn")
inline StageFog::StageFog(float fog_start, float fog_end, float b, float g, float r, float a) {
    start = fog_start;
    end = fog_end;
    blue = b;
    green = g;
    red = r;
    alpha = a;
    packed_blue = (unsigned char)b;
    packed_green = (unsigned char)g;
    packed_red = (unsigned char)r;
    packed_alpha = (unsigned char)a;
}
#pragma code_seg(pop)

#endif
