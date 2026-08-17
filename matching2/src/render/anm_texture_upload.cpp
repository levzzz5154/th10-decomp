#include "th10/render/anm_texture_upload.hpp"
#include "th10/util/scalars.hpp"


// 0x004473C0 - Advance the ANM script cursor one entry per call. The walk
// accumulates each entry's sprite/script counts; when it reaches the entry
// just before the cursor, the entry is loaded with the accumulated table
// bases (retail 0x00447470) and a failed load resets the cursor and stops
// the walk. Reaching the cursor position (or having just loaded) advances
// the cursor and reports the owner; running off the chain end resets the
// cursor to the first entry.

AnmCursorOwner* AnmArchive_AdvanceScriptCursor(
    void* context, AnmCursorOwner* owner,
    int (*load_entry)(void* context, AnmCursorOwner* owner, int entry_index,
                      int sprite_base, int script_base,
                      AnmArchiveEntry* entry)) {
    AnmArchiveEntry* entry = owner->entries;
    int loaded = 0;
    // The running totals are the sprite and script table bases for the entry
    // currently under the cursor; AnmEntry_Load publishes its records there.
    int sprite_base = 0;
    int script_base = 0;
    int position = 0;
    for (;;) {
        if (position == owner->cursor - 1) {
            if (load_entry(context, owner, position, sprite_base, script_base,
                           entry) < 0) {
                owner->cursor = 0;
                return 0;
            }
            loaded = 1;
        }
        sprite_base = sprite_base + entry->sprite_count;
        script_base = script_base + entry->script_count;
        if (entry->next_offset == 0) break;
        entry = (AnmArchiveEntry*)((char*)entry + entry->next_offset);
        position = position + 1;
        if (position == owner->cursor || loaded != 0) {
            owner->cursor = owner->cursor + 1;
            return owner;
        }
    }
    owner->cursor = 0;
    return owner;
}

// 0x00446F40 - Create one texture for an ANM image and upload its pixels.
// When the 16-bit fallback flag is armed (retail DAT_00491D78 bit 0),
// formats 0x15 and 0 downgrade to 5 and format 0x14 downgrades to 3. A
// failed texture creation releases the caller's surface argument and
// reports -1. On success the level-0 surface is fetched (vtable +0x48), the
// pixels upload with the source format and pitch from the shared format
// tables (retail 0x0046F288/0x0046F2A0), the slot's bytes-per-line word is
// refreshed, and the temporary surface is released.

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
                               void (*release_texture)(void)) {
    int effective_index = format_index;
    if (force_sixteen_bit != 0) {
        unsigned int format = format_table[format_index];
        if (format == 0x15 || format == 0) {
            effective_index = 5;
        } else if (format == 0x14) {
            effective_index = 3;
        }
    }
    if (create_texture(format_table[effective_index]) != 0) {
        if (release_texture != 0) release_texture();
        return -1;
    }
    void* surface = 0;
    get_surface(&surface);
    int source_index = image->format;
    load_surface(surface, pixels, format_table[source_index],
                 (unsigned int)image->width * pitch_table[source_index]);
    *slot_pitch_out = pitch_table[effective_index];
    if (surface != 0 && release_surface != 0) release_surface(surface);
    return 0;
}

// 0x00446C70 - Upload one ANM image into an existing texture. The same
// 16-bit downgrade table applies. The level-0 surface is fetched (vtable
// +0x48); file-backed images upload through D3DXLoadSurfaceFromFileInMemory
// while raw images upload from memory with the format and pitch from the
// shared tables. The surface is then released, the transparent border
// repair pass runs (retail 0x004465B0), and the slot's bytes-per-line word
// is refreshed.
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
                             void (*repair_borders)(void)) {
    int effective_index = format_index;
    if (force_sixteen_bit != 0) {
        unsigned int format = format_table[format_index];
        if (format == 0x15 || format == 0) {
            effective_index = 5;
        } else if (format == 0x14) {
            effective_index = 3;
        }
    }
    void* surface = 0;
    get_surface(&surface);
    if (from_file_in_memory != 0) {
        load_surface_from_file(surface);
    } else {
        int source_index = image->format;
        load_surface(surface, pixels, format_table[source_index],
                     (unsigned int)image->width * pitch_table[source_index]);
    }
    if (release_surface != 0) release_surface(surface);
    if (repair_borders != 0) repair_borders();
    *slot_pitch_out = pitch_table[effective_index];
    return 0;
}
