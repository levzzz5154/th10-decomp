#ifndef TH10_PLAYER_WRAP_HPP
#define TH10_PLAYER_WRAP_HPP
#include "th10/math/timer.hpp"
#include "th10/platform/sound_queue.hpp"

extern "C" float flt_neg192;
extern "C" float flt_192;
extern "C" float flt_384;

struct PlayfieldPoint {
    float x;
    float y;
    __declspec(noinline) int OutsidePlayfield(float width, float height) const;
    __declspec(noinline) int OutsidePlayfieldInclusive(float width, float height) const;
};

struct PlayerWrapBounds {
    unsigned char reserved_000[0x30];
    float extent_30;
    float extent_34;
};

struct PlayerWrapHorizontalState {
    unsigned char reserved_000[0x39C];
    PlayerWrapBounds* bounds_39C;
    unsigned char reserved_3A0[0x14];
    PlayfieldPoint position_3B4;
    unsigned char reserved_3BC[0x80];
    unsigned int flags_43C;
    unsigned char reserved_440[0x18];
    int effect_slot_458;
    unsigned char reserved_45C[0x2F0];
    FrameTimer wrap_timer_74C;
    unsigned char reserved_760[0x20];
    FrameTimer vertical_timer_780;

    __declspec(noinline) void WrapHorizontal();
    __declspec(noinline) void WrapVertical();
};

#endif
