#pragma once
#include <stddef.h>
#include "th10/render/quad_batch.hpp"
#include "th10/render/animation_byte_interpolator.hpp"
#include "th10/game/player.hpp"

// One 0x44-byte sprite record of a loaded animation file.
struct FloatingTextGlyph_0042b780 {
    unsigned char reserved_00[0x34];
    float width;
    unsigned char reserved_38[0x44 - 0x38];
};
struct FloatingTextResource_0042b780 {
    unsigned char reserved_000[0x118];
    FloatingTextGlyph_0042b780* sprites;
};

// The pool's shared glyph entity, as far as the draw writes it.
struct FloatingTextSprite_0042b780 {
    unsigned char reserved_000[0x4C];
    float sprite_width;
    unsigned char reserved_050[0x2FC - 0x50];
    unsigned char blue, green, red, alpha;
    unsigned char reserved_300[0x340 - 0x300];
    float x, y;
    unsigned char reserved_348[0x35C - 0x348];
    unsigned int flags;
    unsigned char reserved_360[0x394 - 0x360];
    FloatingTextGlyph_0042b780* glyph;
    unsigned char reserved_398[0x3AC - 0x398];
    // Resize the entity and mark its vertices stale.
    void SetWidth(float width) {
        sprite_width = width;
        flags |= 8;
    }
    unsigned int& Color() { return *reinterpret_cast<unsigned int*>(&blue); }
};

struct FloatingTextPosition_0042b780 { float x, y, z; };

// One floating number: its glyph indices are stored least significant first.
struct FloatingText_0042b780 {
    unsigned char glyphs[12];
    FloatingTextPosition_0042b780 position;
    unsigned int color;
    FrameTimer timer;
    unsigned char reserved_30[8];
    unsigned char active;
    unsigned char length;
    unsigned char reserved_3a[6];
};
typedef char FloatingTextSize_0042b780[sizeof(FloatingText_0042b780) == 0x40 ? 1 : -1];

struct SmollScoreDrawView {
    unsigned char reserved_000[0x10];
    FloatingTextResource_0042b780* resource;
    int next_text;
    FloatingTextSprite_0042b780 sprite;
    FloatingText_0042b780 texts[0x2D3];

    __declspec(noinline) int Draw();
    // 0x0042B9C0: start a floating number; a negative value shows the "max" glyph.
    __declspec(noinline) void Spawn(int value, const FloatingTextPosition_0042b780* position, unsigned int color);
    __forceinline void DrawGlyphs(const FloatingText_0042b780* text, float advance, int alpha);
};
typedef char SmollScoreTexts_0042b780[offsetof(SmollScoreDrawView, texts) == 0x3C4 ? 1 : -1];

// The game-wide render state at 0x00491C28, as far as the draw reads it.
// Reading the flags through the modelled state keeps retail's store order.
struct FloatingTextRenderState_0042b780 {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                // +0x008
    unsigned char reserved_00C[0x150 - 0x0C];
    unsigned char options;               // +0x150, bit 2 = fog disabled
    unsigned char reserved_151[0x750 - 0x151];
    int fog_dirty;                       // +0x750
};

extern "C" {
extern FloatingTextRenderState_0042b780 data_00491c28;
// 0x00443080: draw one entity; the manager is on the stack and the entity
// arrives in ESI.
__declspec(noinline) int __stdcall FloatingText_DrawEntity_00443080(AnimationManager_00442F50* manager, FloatingTextSprite_0042b780* entity);
}
int __fastcall SmollScore_DrawTask_0042b9b0(SmollScoreDrawView* pool);
