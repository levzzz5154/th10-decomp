// 0x00447080 (50 bytes): load an ANM file and all of its entries in one go.
// Returns the file, or null when the file itself could not be opened.
//
// Native LTCG passes the manager in ESI, the slot in ECX and the name in EAX.
// Nothing in the retail image calls it.
#include "th10/render/anm_file_004470c0.hpp"

#pragma code_seg(".text$04xnow")
AnmFile_004470c0* __stdcall AnmManager_LoadFileNow_00447080(AnmManager_004470c0* manager, int slot,
                                                            const char* name) {
    AnmFile_004470c0* file = AnmManager_LoadFile_004470c0(manager, slot, name);
    if (file) {
        file->cursor = 1;
        while (file->cursor) {
            AnmUploadTag_00446c70 tag = { reinterpret_cast<int>(manager) };
            file = AnmManager_LoadNextEntry_004473c0(tag, file);
        }
    }
    return file;
}
#pragma code_seg()
