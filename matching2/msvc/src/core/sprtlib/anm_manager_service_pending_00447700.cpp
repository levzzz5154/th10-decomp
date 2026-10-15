// 0x00447700 (135 bytes): one background-loading step over the manager's ANM
// files. A file flagged for release is released and its slot cleared; the
// first file that still has entries to load gets its next entry loaded, and
// that ends the step (0, or -1 when the entry failed). Returns 0 when nothing
// was left to load.
//
// The manager stays on the stack; RET 4.
#include "th10/render/anm_file_004470c0.hpp"

// 0x00447810, with the file in EDI.
struct AnimationResource_00447810 {
    __declspec(noinline) void Release();
};
extern "C" void __cdecl entry_free_004524a1(void* memory);

// 0x004477D0 without its null test: the caller has already seen the file.
static inline void ClearFileSlot(AnmManager_004470c0* manager, int slot) {
    if (slot < 0)
        return;
    if ((unsigned)slot >= 33u)
        return;
    reinterpret_cast<AnimationResource_00447810*>(manager->files[slot])->Release();
    entry_free_004524a1(manager->files[slot]);
    manager->files[slot] = 0;
}

#pragma code_seg(".text$05service")
extern "C" int __stdcall AnmManager_ServicePending_00447700(AnmManager_004470c0* manager) {
    for (unsigned int slot = 0; slot < 33; ++slot) {
        AnmFile_004470c0* file = manager->files[slot];
        if (!file)
            continue;
        if (file->release_pending) {
            ClearFileSlot(manager, slot);
            manager->files[slot]->release_pending = 0;
            continue;
        }
        if (file->cursor) {
            AnmUploadTag_00446c70 tag = { reinterpret_cast<int>(manager) };
            return AnmManager_LoadNextEntry_004473c0(tag, manager->files[slot]) ? 0 : -1;
        }
    }
    return 0;
}
#pragma code_seg()
