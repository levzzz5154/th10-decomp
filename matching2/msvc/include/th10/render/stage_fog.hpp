#ifndef TH10_RENDER_STAGE_FOG_HPP
#define TH10_RENDER_STAGE_FOG_HPP

// Fog settings of a stage: the range, the colour as four float channels so a
// script can blend it, and the same colour packed for the device.
struct StageFog {
    float start, end;
    float blue, green, red, alpha;
    unsigned char packed_blue, packed_green, packed_red, packed_alpha;

    StageFog() {}
    StageFog(float fog_start, float fog_end, float b, float g, float r, float a) {
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

    __declspec(noinline) StageFog operator+(const StageFog& v) const;
    __declspec(noinline) StageFog operator-(const StageFog& v) const;
    __declspec(noinline) StageFog operator*(float f) const;
};
typedef char StageFogSize[sizeof(StageFog) == 0x1C ? 1 : -1];

#endif
