#include "th10/platform/archive_file.hpp"

// 0x0043D640 (37 bytes): load a sound file from the archive into pending slot
// `index` of the sound manager, publishing a failed (null) load too. The slot
// is neither range-checked nor freed first.
//
// Native LTCG passes the filename in EAX; owner and index stay on the stack.
struct SoundPendingSlots_0043d640 {
    unsigned char reserved_0000[0x5230];
    char* pending[1];                                  // +0x5230

    __declspec(noinline) int LoadPendingSlot(const char* filename, int index);
};

#pragma code_seg(".text$03zr5_slot")
int SoundPendingSlots_0043d640::LoadPendingSlot(const char* filename, int index) {
    char* loaded = Archive_LoadFile(filename, 0, 0);
    pending[index] = loaded;
    return loaded ? 0 : -1;
}
#pragma code_seg()
