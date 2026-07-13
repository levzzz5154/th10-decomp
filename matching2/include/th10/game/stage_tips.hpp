#pragma once

#include "th10/game/entity.hpp"

// One parsed entry from the stage Tips sections. The parser allocates these
// as 0x88-byte records and links them through the pointers below.
struct StageTip {
    float x;                    // +0x00
    float y;                    // +0x04
    uint32_t field_008;
    StageTip* owner;            // +0x0C, self after construction
    StageTip* next;             // +0x10
    StageTip* previous;         // +0x14
    uint8_t data_018[0x6C - 0x18];
    int32_t duration;           // +0x6C, defaults to 300 frames
    int32_t selection;          // +0x70, defaults to -1
    uint8_t data_074[0x7C - 0x74];
    float scale;                // +0x7C, defaults to 1.0
    uint32_t rendered_width;    // +0x80
    int32_t state;              // +0x84, defaults to -1
};
// sizeof(StageTip) == 0x88

StageTip* __fastcall StageTip_Initialize(void* unused, StageTip* tip);
