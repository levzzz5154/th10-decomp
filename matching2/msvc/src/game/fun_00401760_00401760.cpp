// 0x00401760: render the owner's text records and restore the second camera.
//
// The retail entry takes one pointer on the stack, returns 1 in EAX, and uses
// RET 4.  This source must be compiled in the native-LTCG render batch with
// camera_apply.cpp and anm_batch_flush.cpp: their retail receivers are EDI and
// ESI respectively, although these calls are ordinary typed C++ here.
// The raw Flush/Apply aliases remain needed by other renderer callers.  The
// raw 0x00443080 alias remains needed by 0x00401a50, 0x0040a940, and 0x0042b780;
// 0x004451c0 has its own C++ entry declaration at that address.  This function
// inlines only its own anchored-quad effects.
#include "th10/render/camera_batch.hpp"
#include "th10/render/quad_batch.hpp"

// These data aliases are used by the surrounding retail renderer.
extern "C" RenderCamera data_00491d7c;
extern "C" RenderCamera data_00491e94;
extern "C" float data_00470b08; // 2.0f outline displacement
extern "C" float data_00470b0c; // 0.5f anchor midpoint
extern "C" unsigned int data_00491fb0;

// The centered anchors use the retail CRT floor dispatcher through its normal
// double-argument cdecl ABI.  This alias remains raw in the other callers too.
extern "C" double __cdecl asm_FUN_00452ff0_00452ff0(double value);

struct TextOverlayRecord_00401760 {
    unsigned char text[0x40];
    float base_x;
    float base_y;
    float base_z;
    unsigned int color;
    float scale_x;
    float scale_y;
    unsigned int reserved_058;
    unsigned int camera_mode;
    unsigned int font_index;
    unsigned int outlined;
};

struct TextOverlayGlyph_00401760 {
    unsigned char reserved_000[0x30];
    float height;
    float width;
};

struct TextOverlayFont_00401760 {
    unsigned char reserved_000[0x118];
    TextOverlayGlyph_00401760* glyphs;
};

// Each record in this routine's local view occupies 0x68 bytes.  The outer
// object has no shared typed view yet; its count, scale, resource and record
// table are reached at the offsets confirmed in the live disassembly.
extern "C" __declspec(noinline) int __stdcall
asm_FUN_00401760_00401760(void* owner_pointer) {
    unsigned char* owner = static_cast<unsigned char*>(owner_pointer);
    RenderEntity* entity = reinterpret_cast<RenderEntity*>(owner + 0x14);

    entity->flags = (entity->flags & 0xFFD7FFFFu) | 0x00140001u;

    TextOverlayRecord_00401760* records =
        reinterpret_cast<TextOverlayRecord_00401760*>(owner + 0x76C);
    int record_count = *reinterpret_cast<int*>(owner + 0x896C);
    int line_width_factor = *reinterpret_cast<int*>(owner + 0x898C);
    TextOverlayFont_00401760* font =
        *reinterpret_cast<TextOverlayFont_00401760**>(owner + 0x8994);
    int last_camera_mode = 1;

    for (int record_index = 0; record_index < record_count; ++record_index) {
        TextOverlayRecord_00401760* record = records + record_index;

        entity->base_position.x = record->base_x;
        entity->base_position.y = record->base_y;
        entity->base_position.z = record->base_z;
        entity->scale_x = record->scale_x;
        entity->scale_y = record->scale_y;
        entity->flags |= 8;

        float character_advance;
        float line_advance;
        if (record->font_index == 1) {
            character_advance = 7.0f;
            line_advance = 9.0f;
        } else {
            character_advance =
                static_cast<float>(line_width_factor) * record->scale_x;
            line_advance = 14.0f;
        }

        if (last_camera_mode != static_cast<int>(record->camera_mode)) {
            // Keep the unconditional retail flush here; Apply also performs
            // its own guarded flush, which is normally empty after this one.
            data_00491c10->Flush();

            RenderCamera* camera = record->camera_mode != 0
                ? &data_00491d7c
                : &data_00491e94;
            data_00491fac = reinterpret_cast<RenderTargetViewport*>(camera);
            camera->Apply();
            data_00491c30->Viewport(&camera->viewport_x);
            data_00491fb0 = record->camera_mode == 0 ? 1u : 0u;
            last_camera_mode = static_cast<int>(record->camera_mode);
        }

        const unsigned char* character = record->text;
        while (*character != 0) {
            unsigned char code = *character;
            if (code == 0x0A) {
                entity->base_position.y += line_advance * record->scale_y;
                entity->base_position.x = record->base_x;
            } else if (code != 0x20) {
                unsigned int glyph_index =
                    record->font_index * 0x62u + static_cast<unsigned int>(code) - 0x20u;
                unsigned char* glyph_address =
                    reinterpret_cast<unsigned char*>(font->glyphs) + glyph_index * 0x44u;
                TextOverlayGlyph_00401760* glyph =
                    reinterpret_cast<TextOverlayGlyph_00401760*>(glyph_address);

                entity->texture = reinterpret_cast<RenderTexture*>(glyph);
                entity->sprite_height = glyph->height;
                entity->sprite_width = glyph->width;
                entity->flags |= 8;

                // The outline and ordinary pass share one geometry body.  The
                // first pass draws at +2,+2 with half alpha, then restores the
                // base position before drawing the ordinary color.
                int pass_count = record->outlined != 0 ? 2 : 1;
                for (int pass = 0; pass < pass_count; ++pass) {
                    if (record->outlined != 0 && pass == 0) {
                        entity->color = record->color & 0xFF000000u;
                        reinterpret_cast<unsigned char*>(&entity->color)[3] =
                            static_cast<unsigned char>(record->color >> 25);
                        entity->base_position.x += data_00470b08;
                        entity->base_position.y += data_00470b08;
                    } else {
                        if (record->outlined != 0) {
                            entity->base_position.x -= data_00470b08;
                            entity->base_position.y -= data_00470b08;
                        }
                        entity->color = record->color;
                    }

                    float width = entity->sprite_width * entity->scale_x;
                    float height = entity->sprite_height * entity->scale_y;
                    float half_width = width * data_00470b0c;
                    float half_height = height * data_00470b0c;

                    switch ((entity->flags >> 18) & 3) {
                    case 0: {
                        float left = asm_FUN_00452ff0_00452ff0(
                            static_cast<double>((entity->base_position.x
                                + entity->position.x + entity->render_offset.x)
                                - half_width));
                        data_004978c0[0].x = data_004978c0[2].x = left;
                        data_004978c0[1].x = data_004978c0[3].x = left + width;
                        break;
                    }
                    case 1: {
                        float left = (entity->base_position.x + entity->position.x)
                            + entity->render_offset.x;
                        float right = ((entity->base_position.x + entity->position.x)
                            + width) + entity->render_offset.x;
                        data_004978c0[0].x = data_004978c0[2].x = left;
                        data_004978c0[1].x = data_004978c0[3].x = right;
                        break;
                    }
                    case 2: {
                        float right = (entity->base_position.x + entity->position.x)
                            + entity->render_offset.x;
                        data_004978c0[0].x = data_004978c0[2].x = right - width;
                        data_004978c0[1].x = data_004978c0[3].x = right;
                        break;
                    }
                    case 3:
                        // Retail deliberately preserves the previous shared
                        // x coordinates for anchor value 3.
                        break;
                    }

                    switch ((entity->flags >> 20) & 3) {
                    case 0: {
                        float top = static_cast<float>(asm_FUN_00452ff0_00452ff0(
                            static_cast<double>((entity->render_offset.y
                                + entity->position.y + entity->base_position.y)
                                - half_height)));
                        float bottom = top + height;
                        data_004978c0[0].y = data_004978c0[1].y = top;
                        data_004978c0[2].y = data_004978c0[3].y = bottom;
                        break;
                    }
                    case 1: {
                        float top = (entity->position.y + entity->render_offset.y)
                            + entity->base_position.y;
                        float bottom = ((entity->position.y + entity->render_offset.y)
                            + entity->base_position.y) + height;
                        data_004978c0[0].y = data_004978c0[1].y = top;
                        data_004978c0[2].y = data_004978c0[3].y = bottom;
                        break;
                    }
                    case 2: {
                        float bottom = (entity->position.y + entity->render_offset.y)
                            + entity->base_position.y;
                        data_004978c0[0].y = data_004978c0[1].y = bottom - height;
                        data_004978c0[2].y = data_004978c0[3].y = bottom;
                        break;
                    }
                    case 3:
                        // As on x, anchor value 3 leaves the shared y values.
                        break;
                    }

                    float depth = (entity->render_offset.z + entity->position.z)
                        + entity->base_position.z;
                    data_004978c0[0].z = depth;
                    data_004978c0[1].z = depth;
                    data_004978c0[2].z = depth;
                    data_004978c0[3].z = depth;

                    data_00491c10->SubmitSpriteQuad(entity, 1);
                }

                entity->base_position.x += character_advance;
            } else {
                entity->base_position.x += character_advance;
            }

            ++character;
        }
    }

    if (record_count > 0 && last_camera_mode == 0) {
        return 1;
    }

    data_00491c10->Flush();
    data_00491fac = reinterpret_cast<RenderTargetViewport*>(&data_00491e94);
    data_00491e94.Apply();
    data_00491c30->Viewport(&data_00491e94.viewport_x);
    data_00491fb0 = 1;
    return 1;
}
