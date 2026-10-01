// 0x004473C0 (174 bytes): load the next pending entry of an ANM file. The
// entry chain is walked from the start, accumulating the sprite and script
// table bases, until the entry numbered `cursor - 1` has been loaded; the
// cursor then advances, or drops to zero when the chain ends. Returns the
// file, or null when the entry failed to load.
//
// Both arguments stay on the stack.
#include "th10/render/anm_file_004470c0.hpp"

#pragma code_seg(".text$05r1next")
AnmFile_004470c0* __stdcall AnmManager_LoadNextEntry_004473c0(AnmUploadTag_00446c70 manager,
                                                              AnmFile_004470c0* file) {
    AnmEntryHeader_00446c70* entry = file->header;
    int position = 0;
    int script_base = 0;
    int sprite_base = 0;
    int index = 0;
    int loaded = 0;
    do {
        if (position == file->cursor - 1) {
            if (AnmFile_LoadEntry_00447470(manager, file, sprite_base, script_base, entry, index) < 0) {
                file->cursor = 0;
                return 0;
            }
            loaded = 1;
        }
        sprite_base += entry->sprite_count;
        script_base += entry->script_count;
        ++index;
        if (!entry->next_offset) {
            file->cursor = 0;
            return file;
        }
        entry = entry->Next();
        ++position;
    } while (position != file->cursor && !loaded);
    int next = file->cursor + 1;
    file->cursor = next;
    return file;
}
#pragma code_seg()
