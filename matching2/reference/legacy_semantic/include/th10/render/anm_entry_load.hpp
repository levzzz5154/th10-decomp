// =============================================================================
// anm_entry_load.hpp - ANM archive entry loader
// Retail function: 0x00447470
//
// One entry of an ANM archive describes a single texture plus the sprite and
// script tables that index into it. The loader validates the entry, builds the
// texture through one of three creation paths, publishes it, and then fills
// the owner's sprite-record and script-pointer tables.
// =============================================================================
#ifndef TH10_RENDER_ANM_ENTRY_LOAD_HPP
#define TH10_RENDER_ANM_ENTRY_LOAD_HPP

#include "th10/render/animation_manager.hpp"

// Raw entry header as it appears in the archive image. All offsets stored in
// the header are relative to the entry itself, not to the archive base.
struct AnmLoadEntry {
    int sprite_count;      // +0x00
    int script_count;      // +0x04
    int reserved_08;       // +0x08
    int width;             // +0x0C: declared image width
    int height;            // +0x10: declared image height
    int format;            // +0x14: format table index
    int color_key;         // +0x18
    int name_offset;       // +0x1C: entry-relative name string
    int reserved_20[2];    // +0x20
    int version;           // +0x28: must be 4
    int texture_priority;  // +0x2C
    int payload_offset;    // +0x30: entry-relative embedded image
    unsigned char has_payload;  // +0x34
    unsigned char reserved_35[3];
    int next_offset;       // +0x38
    int reserved_3c;       // +0x3C
    // +0x40: sprite offset table, one dword per sprite, followed by the
    // script table of {id, offset} dword pairs.
};

// Surface description returned by the level-0 query. Retail reads only the
// width and height, at dword 6 and dword 7 of the D3D structure.
struct AnmSurfaceDesc {
    unsigned int format;
    unsigned int type;
    unsigned int usage;
    unsigned int pool;
    unsigned int multi_sample_type;
    unsigned int multi_sample_quality;
    unsigned int width;
    unsigned int height;
};

// The owner fields the loader writes into, with their retail offsets.
struct AnmEntryLoadOwner {
    unsigned int header_word;              // +0x000: copied into record slot 0
    float* sprite_records;                 // +0x118: 17 floats per sprite
    const void** script_table;             // +0x11C
    AnimationTextureRecord* textures;      // +0x120: 16 bytes per record
};

// The retail callees, threaded through so the loader stays testable.
struct AnmEntryLoadHooks {
    void* context;
    // 0x00446F40: build a texture from the entry's embedded payload.
    int (*create_from_payload)(void* context, AnimationTextureRecord* record,
                               int format, const void* payload, int width,
                               int height);
    // 0x00446EB0: build a texture from the archive image plus a color key.
    int (*create_from_file_image)(void* context, AnimationTextureRecord* record,
                                  int format, const void* image, int color_key,
                                  int width, int height);
    // 0x00447050: allocate a blank managed texture.
    void (*create_blank)(void* context, AnimationTextureRecord* record,
                         int format, int width, int height);
    void (*set_priority)(void* context, AnimationTextureRecord* record,
                         int priority);
    void (*preload)(void* context, AnimationTextureRecord* record);
    void (*get_level_desc)(void* context, AnimationTextureRecord* record,
                           int level, AnmSurfaceDesc* desc_out);
    void (*log_error)(void* context, const char* text);
};

// Retail Shift-JIS diagnostics at 0x00470274, 0x00470254, 0x0047016C and
// 0x004701B0 respectively.
extern const char kAnmEntryMissingText[];
extern const char kAnmEntryBadVersionText[];
extern const char kAnmEntryPayloadFailText[];
extern const char kAnmEntryFileFailText[];

// The sprite offset table begins at +0x40; the script table follows it.
const int* AnmEntry_SpriteTable(const AnmLoadEntry* entry);
const int* AnmEntry_ScriptTable(const AnmLoadEntry* entry);

// The arithmetic half shared with the animation manager's copy path
// (0x00447940): derives the normalized coordinates and unscaled extents from
// the corner and scale slots of an already-populated 17-float record.
void AnmSprite_DeriveRecord(float* record);

// 0x00447470. Returns 1 on success and -1 after a reported failure.
int AnmEntry_Load(int texture_index, const void* image,
                  AnmEntryLoadOwner* owner, int sprite_base, int script_base,
                  const AnmLoadEntry* entry, const AnmEntryLoadHooks* hooks);

#endif  // TH10_RENDER_ANM_ENTRY_LOAD_HPP
