#pragma once
// The game thread's on-screen text: two queues of positioned strings that the
// frame's code appends to and two draw tasks print with the ASCII font.
#include <stddef.h>

#include "th10/render/camera_batch.hpp"

// One queued string.
struct GameThreadTextRecord {
    char text[0x40];
    RenderVec3 position;                    // +40
    unsigned int color;                     // +4C
    float scale_x;                          // +50
    float scale_y;                          // +54
    int reserved_58;
    int in_game_view;                       // +5C, nonzero: drawn with the first render stage
    int font;                               // +60, 0: the 14-pixel font, 1: the small 9-pixel font
    int shadow;                             // +64, nonzero: drawn twice, first as a dark offset copy
};

// One character's sprite in the font animation file.
struct GameThreadFontSprite {
    unsigned char reserved_00[0x30];
    float height;                           // +30
    float width;                            // +34
    unsigned char reserved_38[0x0C];
};
struct GameThreadFont {
    unsigned char reserved_000[0x118];
    GameThreadFontSprite* sprites;          // +118, 0x62 per font, from ' '
};

struct GameThreadText {
    unsigned char reserved_0000[0x14];
    RenderEntity glyph;                     // +0014, the sprite every character is drawn with
    unsigned char reserved_03ac[0x76C - 0x14 - sizeof(RenderEntity)];
    GameThreadTextRecord records[0x100];    // +076C
    GameThreadTextRecord late_records[0x40]; // +6F6C
    int record_count;                       // +896C
    int late_record_count;                  // +8970
    unsigned char reserved_8974[0x18];
    int glyph_advance;                      // +898C, pixels between characters at scale 1
    int reserved_8990;
    GameThreadFont* font;                   // +8994

    // 0x00401A50: prints the late text queue. Retail receiver EBX.
    __declspec(noinline) int DrawLateRecords();
};

typedef char GameThreadTextGlyphFlags[(offsetof(GameThreadText, glyph) + offsetof(RenderEntity, flags) == 0x370) ? 1 : -1];
typedef char GameThreadTextRecords[(offsetof(GameThreadText, records) == 0x76C) ? 1 : -1];
typedef char GameThreadTextLateRecords[(offsetof(GameThreadText, late_records) == 0x6F6C) ? 1 : -1];
typedef char GameThreadTextCount[(offsetof(GameThreadText, record_count) == 0x896C) ? 1 : -1];
typedef char GameThreadTextAdvance[(offsetof(GameThreadText, glyph_advance) == 0x898C) ? 1 : -1];
typedef char GameThreadTextFont[(offsetof(GameThreadText, font) == 0x8994) ? 1 : -1];
typedef char GameThreadTextRecordSize[(sizeof(GameThreadTextRecord) == 0x68) ? 1 : -1];
typedef char GameThreadFontSpriteSize[(sizeof(GameThreadFontSprite) == 0x44) ? 1 : -1];

// The game-wide render state at 0x00491C28: the device, the two render stage
// records (a camera padded to 0x118 bytes), and which of them is active.
struct GameThreadRenderStage {
    RenderCamera camera;
    unsigned char reserved_0F0[0x118 - sizeof(RenderCamera)];
};
struct GameThreadRenderState {
    unsigned char reserved_000[0x08];
    RenderDevice* device;                   // +008
    unsigned char reserved_00C[0x154 - 0x0C];
    GameThreadRenderStage stages[2];        // +154
    GameThreadRenderStage* active_stage;    // +384
    int stage_index;                        // +388
    unsigned char reserved_38C[0x750 - 0x38C];
    int fog_enabled;                        // +750, the device's cached fog switch

    __forceinline void SelectStage(int index) {
        active_stage = &stages[index];
        active_stage->camera.Apply();
        device->Viewport(&active_stage->camera.viewport_x);
        stage_index = index;
    }
};
extern "C" GameThreadRenderState data_00491c28;

extern "C" __declspec(noinline) int EntityDraw_00443080(RenderEntity* entity,
                                                       AnimationManager_00442F50* manager);
extern "C" __declspec(noinline) int EntityDraw_00443290(RenderEntity* entity,
                                                       AnimationManager_00442F50* manager);

static __forceinline void GlyphSetScale(RenderEntity* entity, float x, float y) {
    entity->scale_x = x;
    entity->scale_y = y;
    entity->flags |= 8;
}
static __forceinline void GlyphSetSpriteSize(RenderEntity* entity, float width, float height) {
    entity->sprite_width = width;
    entity->sprite_height = height;
    entity->flags |= 8;
}

// 0x00401760: prints the main text queue. Retail takes the thread on the stack.
__declspec(noinline) int __stdcall GameThreadText_DrawRecords_00401760(GameThreadText* thread);
