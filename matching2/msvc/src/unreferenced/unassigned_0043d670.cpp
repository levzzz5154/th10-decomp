#include "th10/platform/archive_file.hpp"

// Publish the cached music metadata image, including a failed (null) load.
#pragma code_seg(".text$03zrc_music")
extern "C" __declspec(noinline) int __stdcall Sound_LoadMusicTable(
        const char* filename, void* owner) {
    char* loaded = Archive_LoadFile(filename, 0, 0);
    unsigned int address = reinterpret_cast<unsigned int>(owner) + 0x1f84u;
    *reinterpret_cast<char* volatile*>(address) = loaded;
    return loaded ? 0 : -1;
}
#pragma code_seg()
