#pragma once

// ANM script cursor advance and texture create/upload (retail 0x004473C0, 0x00446F40, 0x00446C70).
#include "th10/util/scalars.hpp"

// ANM entry header fields walked by the cursor leaf. The leading two fields
// are the entry's sprite and script counts, which is what the cursor walk
// accumulates into the per-entry table bases passed to the loader
// (0x00447470).
struct AnmArchiveEntry {
    int sprite_count;      // retail +0x00
    int script_count;      // retail +0x04
    int reserved[12];      // retail +0x08..+0x37
    int next_offset;       // retail +0x38: byte offset to the next entry, 0 ends
};

struct AnmCursorOwner {
    AnmArchiveEntry* entries;   // retail +0x108
    int cursor;                // retail +0x124
};

AnmCursorOwner* AnmArchive_AdvanceScriptCursor(
    void* context, AnmCursorOwner* owner,
    int (*load_entry)(void* context, AnmCursorOwner* owner, int entry_index,
                      int sprite_base, int script_base,
                      AnmArchiveEntry* entry));

// ANM image header fields used by the texture upload leaves.
struct AnmImage {
    short reserved_00[3];      // retail +0x00..+0x05
    short format;              // retail +0x06: index into the format tables
    short width;               // retail +0x08
    short height;              // retail +0x0A
    short reserved_0c[2];      // retail +0x0C..+0x0F
    // pixel data follows at retail +0x10
};

int AnmTexture_CreateAndUpload(const AnmImage* image,
                               const Byte* pixels, int format_index,
                               int force_sixteen_bit,
                               const unsigned int* format_table,
                               const unsigned int* pitch_table,
                               unsigned int* slot_pitch_out,
                               int (*create_texture)(unsigned int format),
                               int (*get_surface)(void** surface_out),
                               int (*load_surface)(void* surface,
                                                   const Byte* pixels,
                                                   unsigned int source_format,
                                                   unsigned int pitch),
                               void (*release_surface)(void* surface),
                               void (*release_texture)(void));

int AnmTexture_UploadSurface(const AnmImage* image,
                             const Byte* pixels, int format_index,
                             int from_file_in_memory, int force_sixteen_bit,
                             const unsigned int* format_table,
                             const unsigned int* pitch_table,
                             unsigned int* slot_pitch_out,
                             int (*get_surface)(void** surface_out),
                             int (*load_surface_from_file)(void* surface),
                             int (*load_surface)(void* surface,
                                                 const Byte* pixels,
                                                 unsigned int source_format,
                                                 unsigned int pitch),
                             void (*release_surface)(void* surface),
                             void (*repair_borders)(void));
