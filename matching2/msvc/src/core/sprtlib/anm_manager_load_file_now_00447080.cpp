// 0x00447080 (50 bytes): load an ANM file and all of its entries in one go.
// Returns the file, or null when the file itself could not be opened.
//
// Native LTCG passes the manager in ESI, the slot in ECX and the name in EAX.
// Nothing in the retail image calls it.
#include "th10/render/anm_file_004470c0.hpp"

#pragma code_seg(".text$04xnow")
AnmFile* __stdcall AnmManager_LoadFileNow(AnmManager_004470c0* manager, int slot,
                                                            const char* name) {
    AnmFile* file = AnmManager_LoadFile(manager, slot, name);
    if (file) {
        file->cursor = 1;
        while (file->cursor) {
            AnmUploadTag tag = { reinterpret_cast<int>(manager) };
            file = AnmManager_LoadNextEntry(tag, file);
        }
    }
    return file;
}
#pragma code_seg()
