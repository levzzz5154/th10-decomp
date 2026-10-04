#pragma once
// The game thread's on-screen text: two queues of positioned strings that the
// frame's code appends to and two draw tasks print with the ASCII font.
#include <stddef.h>

#include "th10/render/camera_batch.hpp"

// One queued string.
struct GameThreadTextRecord_00401a50 {
    char text[0x40];
    RenderVec3 position;                    // +40
    unsigned int color;                     // +4C
    float scale_x;                          // +50
    float scale_y;                          // +54
    int reserved_58;
    int in_game_view;                       // +5C, nonzero: drawn with the first render stage
    int reserved_60;
    int reserved_64;
};

struct GameThreadFontSprite_00401a50 {
    unsigned char reserved_00[0x44];
};
struct GameThreadFont_00401a50 {
    unsigned char reserved_000[0x118];
    GameThreadFontSprite_00401a50* sprites; // +118, one per character from ' '
};

struct GameThreadText_00401a50 {
    unsigned char reserved_0000[0x14];
    RenderEntity glyph;                     // +0014, the sprite every character is drawn with
    unsigned char reserved_03ac[0x76C - 0x14 - sizeof(RenderEntity)];
    GameThreadTextRecord_00401a50 records[0x100];      // +076C
    GameThreadTextRecord_00401a50 late_records[0x40];  // +6F6C
    int record_count;                       // +896C
    int late_record_count;                  // +8970
    unsigned char reserved_8974[0x18];
    int glyph_advance;                      // +898C, pixels between characters at scale 1
    int reserved_8990;
    GameThreadFont_00401a50* font;          // +8994

    // 0x00401A50; retail receiver EBX.
    __declspec(noinline) int DrawLateRecords();
};

typedef char GameThreadTextGlyphFlags[(offsetof(GameThreadText_00401a50, glyph) + offsetof(RenderEntity, flags) == 0x370) ? 1 : -1];
typedef char GameThreadTextLateRecords[(offsetof(GameThreadText_00401a50, late_records) == 0x6F6C) ? 1 : -1];
typedef char GameThreadTextLateCount[(offsetof(GameThreadText_00401a50, late_record_count) == 0x8970) ? 1 : -1];
typedef char GameThreadTextAdvance[(offsetof(GameThreadText_00401a50, glyph_advance) == 0x898C) ? 1 : -1];
typedef char GameThreadTextFont[(offsetof(GameThreadText_00401a50, font) == 0x8994) ? 1 : -1];
typedef char GameThreadTextRecordSize[(sizeof(GameThreadTextRecord_00401a50) == 0x68) ? 1 : -1];
