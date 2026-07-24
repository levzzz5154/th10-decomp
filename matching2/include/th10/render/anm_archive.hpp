// =============================================================================
// anm_archive.hpp - ANM archive mount + per-entry texture creation
// Retail functions: 0x004470C0, 0x004472E0
// =============================================================================
#ifndef TH10_RENDER_ANM_ARCHIVE_HPP
#define TH10_RENDER_ANM_ARCHIVE_HPP

// One ANM entry header as it appears inside the archive image.
struct AnmEntryView {
    unsigned int sprite_count;    // +0x00
    unsigned int script_count;    // +0x04
    unsigned int width;           // +0x08 block
    unsigned int height;
    unsigned int format;
    unsigned int name_offset;     // texture name
    unsigned int alt_name_offset; // alpha texture name (0 when absent)
    unsigned int texture_offset;  // embedded pixel payload (0 => named file)
    unsigned int next_offset;     // 0 terminates the chain
};

struct AnmArchiveHooks {
    void* context;
    void* (*load_file)(void* context, const char* name,
                       unsigned int* size_out);        // 0x0044B360
    void (*release)(void* context, void* memory);
    // Parse one entry header out of the raw image at `offset`.
    int (*decode_entry)(void* context, unsigned int offset,
                        AnmEntryView* view_out);
    // Register sprites/scripts for one entry (retail inline loops).
    void (*register_sprites)(void* context, int entry_index,
                             const AnmEntryView* view);
    void (*register_scripts)(void* context, int entry_index,
                             const AnmEntryView* view);
    // 0x004472E0 per-entry texture creation.
    int (*create_entry_texture)(void* context, int entry_index);
    void (*store_slot)(void* context, int slot, void* image);
};

// Returns the number of entries mounted, or -1 on load failure.
int AnmArchive_Mount(const char* name, int slot,
                     const AnmArchiveHooks* hooks);

struct AnmTextureHooks {
    void* context;
    // Create the texture from an embedded payload (D3DXCreateTextureFromFileInMemoryEx path).
    int (*create_from_memory)(void* context, const AnmEntryView* view);
    // Create the texture from a named sibling file inside the archive.
    int (*create_from_named_file)(void* context, const AnmEntryView* view);
    // Optional alpha-channel merge from the alt-name payload.
    int (*merge_alpha_texture)(void* context, const AnmEntryView* view);
    void (*log_failure)(void* context, const AnmEntryView* view);
};

int AnmEntry_CreateTexture(const AnmEntryView* view,
                           const AnmTextureHooks* hooks);

#endif // TH10_RENDER_ANM_ARCHIVE_HPP
