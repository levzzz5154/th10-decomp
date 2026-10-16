// 0x004470C0 (433 bytes): load an ANM file from the archive into manager slot
// `slot`. The file is a chain of entries; their sprite and script counts are
// summed to size the tables, one texture record is made per entry, and each
// entry's external image file (if any) is loaded up front. Returns the file,
// or null after a failure (the half-built record stays in the slot).
//
// All three arguments stay on the stack.
#include "th10/render/anm_file.hpp"
#include "th10/platform/archive_file.hpp"

#pragma code_seg(".text$04zaload")
AnmFile* __stdcall AnmManager_LoadFile(AnmManager2* manager, int slot,
                                                         const char* name) {
    char path[260];
    if (slot >= 33) {
        g_log.AppendLine(str_texture_slots_full);
        return 0;
    }
    sprintf(path, str_string_format, name);
    AnmEntryHeader2* header =
        reinterpret_cast<AnmEntryHeader2*>(Archive_LoadFile(path, 0, 0));
    int index = 0;
    AnmFile* file = new AnmFile;
    manager->files[slot] = file;
    if (!header)
        return 0;
    file->slot = slot;
    file->header = header;
    strcpy(file->name, name);

    AnmEntryHeader2* entry = header;
    int entries = 1;
    int sprites = header->sprite_count;
    int scripts = header->script_count;
    while (entry->next_offset) {
        entry = entry->Next();
        scripts += entry->script_count;
        sprites += entry->sprite_count;
        ++entries;
    }
    file->entry_count = entries;
    file->textures = static_cast<AnmTexture*>(
        asm_malloc_00452706(entries * sizeof(AnmTexture)));
    memset(file->textures, 0, entries * sizeof(AnmTexture));
    file->sprites = static_cast<AnimationPositionRecord*>(
        asm_malloc_00452706(sprites * sizeof(AnimationPositionRecord)));
    file->scripts = static_cast<const void**>(asm_malloc_00452706(scripts * sizeof(void*)));
    file->script_count = scripts;
    file->sprite_count = sprites;

    for (;;) {
        if (AnmFile_PreloadEntryImage(file, header, index) < 0)
            return 0;
        int next = header->next_offset;
        ++index;
        if (!next)
            break;
        header = reinterpret_cast<AnmEntryHeader2*>(
            reinterpret_cast<unsigned char*>(header) + next);
    }
    return file;
}
#pragma code_seg()
