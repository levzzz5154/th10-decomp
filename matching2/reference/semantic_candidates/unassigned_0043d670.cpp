#include "th10/platform/archive_file.hpp"
#include "sound_wave_types.hpp"

// Semantic model of the 0x0043D670 retail routine. Its private entry ABI has
// the filename in EAX and the owner as one stack argument. This ordinary C++
// signature names both inputs explicitly; it does not encode that register /
// stack split or the retail RET 4.
extern "C" int __stdcall Sound_LoadMusicTable_0043d670(
        const char* file_name, WaveSoundManager* owner) {
    unsigned char* data = reinterpret_cast<unsigned char*>(Archive_LoadFile(file_name, 0, 0));

    owner->loaded_music_data = data;
    return data ? 0 : -1;
}
