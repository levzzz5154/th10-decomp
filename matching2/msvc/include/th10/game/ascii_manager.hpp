#pragma once
// The ASCII manager (ascii.anm, text.anm, capture.anm): two queues of
// positioned strings that the frame's code appends to, cleared by the update
// task and printed with the ASCII font by two draw tasks.
#include <stddef.h>

#include "th10/render/camera_batch.hpp"

// One queued string.
struct AsciiString {
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
struct AsciiFontSprite {
    unsigned char reserved_00[0x30];
    float height;                           // +30
    float width;                            // +34
    unsigned char reserved_38[0x0C];
};
struct AsciiFont {
    unsigned char reserved_000[0x118];
    AsciiFontSprite* sprites;          // +118, 0x62 per font, from ' '
};

struct AsciiManager {
    unsigned char reserved_0000[0x14];
    RenderEntity glyph;                     // +0014, the sprite every character is drawn with
    unsigned char reserved_03ac[0x76C - 0x14 - sizeof(RenderEntity)];
    AsciiString records[0x100];    // +076C
    AsciiString late_records[0x40]; // +6F6C
    int record_count;                       // +896C
    int late_record_count;                  // +8970
    unsigned char reserved_8974[0x18];
    int glyph_advance;                      // +898C, pixels between characters at scale 1
    int update_count;                       // +8990
    AsciiFont* font;                   // +8994

    // 0x004014F0: the update task; empties both queues.
    int OnUpdate();

    // 0x00401A50: prints the late text queue. Retail receiver EBX.
    __declspec(noinline) int DrawLateRecords();
};

typedef char AsciiManagerGlyphFlags[(offsetof(AsciiManager, glyph) + offsetof(RenderEntity, flags) == 0x370) ? 1 : -1];
typedef char AsciiManagerRecords[(offsetof(AsciiManager, records) == 0x76C) ? 1 : -1];
typedef char AsciiManagerLateRecords[(offsetof(AsciiManager, late_records) == 0x6F6C) ? 1 : -1];
typedef char AsciiManagerCount[(offsetof(AsciiManager, record_count) == 0x896C) ? 1 : -1];
typedef char AsciiManagerAdvance[(offsetof(AsciiManager, glyph_advance) == 0x898C) ? 1 : -1];
typedef char AsciiManagerFont[(offsetof(AsciiManager, font) == 0x8994) ? 1 : -1];
typedef char AsciiManagerRecordSize[(sizeof(AsciiString) == 0x68) ? 1 : -1];
typedef char AsciiFontSpriteSize[(sizeof(AsciiFontSprite) == 0x44) ? 1 : -1];

// The game-wide render state at 0x00491C28: the device, the two render stage
// records (a camera padded to 0x118 bytes), and which of them is active.
struct GameThreadRenderStage {
    RenderCamera camera;
    unsigned char reserved_0F0[0xFC - sizeof(RenderCamera)];
    unsigned int fog_start;                 // +0FC, float bits for the device
    unsigned int fog_end;                   // +100
    unsigned char reserved_104[0x114 - 0x104];
    unsigned int fog_color;                 // +114
};
typedef char AsciiRenderStageSize[(sizeof(GameThreadRenderStage) == 0x118) ? 1 : -1];
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
extern "C" GameThreadRenderState g_application;

extern "C" __declspec(noinline) int EntityDraw(RenderEntity* entity,
                                                       SprtCtrlBatchView* manager);
extern "C" __declspec(noinline) int EntityDraw2(RenderEntity* entity,
                                                       SprtCtrlBatchView* manager);

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
__declspec(noinline) int __stdcall AsciiManager_DrawStrings(AsciiManager* thread);
