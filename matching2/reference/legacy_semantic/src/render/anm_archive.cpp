// =============================================================================
// anm_archive.cpp - ANM archive mount + per-entry texture creation
// =============================================================================
#include "th10/render/anm_archive.hpp"

// 0x004470C0 - AnmArchive_Mount: load one .anm archive through the shared
// file loader, walk the entry chain, register every sprite and script, and
// create each entry's texture. The raw image stays resident in the manager
// slot table (mgr+0x3AD06C) because sprites reference it directly.
int AnmArchive_Mount(const char* name, int slot,
                     const AnmArchiveHooks* hooks) {
    unsigned int size = 0;
    void* image = hooks->load_file(hooks->context, name, &size);
    if (image == 0)
        return -1;

    int entry_index = 0;
    unsigned int offset = 0;
    for (;;) {
        AnmEntryView view;
        if (hooks->decode_entry(hooks->context, offset, &view) != 0) {
            hooks->release(hooks->context, image);
            return -1;
        }
        hooks->register_sprites(hooks->context, entry_index, &view);
        hooks->register_scripts(hooks->context, entry_index, &view);
        if (hooks->create_entry_texture(hooks->context, entry_index) != 0) {
            hooks->release(hooks->context, image);
            return -1;
        }
        entry_index += 1;
        if (view.next_offset == 0)
            break;
        offset += view.next_offset;
    }
    hooks->store_slot(hooks->context, slot, image);
    return entry_index;
}

// 0x004472E0 - AnmEntry_CreateTexture: create the D3D texture for one ANM
// entry. Embedded payloads decode from memory; otherwise the named sibling
// file is loaded. When an alpha companion name is present, its channel is
// merged into the created texture.
int AnmEntry_CreateTexture(const AnmEntryView* view,
                           const AnmTextureHooks* hooks) {
    int status;
    if (view->texture_offset != 0)
        status = hooks->create_from_memory(hooks->context, view);
    else
        status = hooks->create_from_named_file(hooks->context, view);
    if (status != 0) {
        hooks->log_failure(hooks->context, view);
        return -1;
    }
    if (view->alt_name_offset != 0 &&
        hooks->merge_alpha_texture(hooks->context, view) != 0) {
        hooks->log_failure(hooks->context, view);
        return -1;
    }
    return 0;
}
