// Compiler context only; no context bytes count as recovered game code.
#include "../../src/game/asset_buffer.cpp"
#include "th10/platform/stage_ecl_load_00403850.hpp"

// The manager object 0x0043A9B0 works on.  Only the fields the modelled body
// reaches are named; the synthetic caller below is what establishes the
// private entry convention (manager in EAX, index in ESI, name on the stack).
struct SoundManager_0043a9b0 {
    unsigned char reserved_000[0x10];
    int active_track;
    void* playing_blocks[32];
    int released_count;
    char* tracks[32];
    void MidiStop();
    int LoadTrack(int index, const char* name);
};

extern "C" int __stdcall Sound_LoadMusicTable_0043d670(
        const char* filename, void* owner);

struct SoundPendingSlots_0043d640 {
    int LoadPendingSlot(const char* filename, int index);
};

#pragma code_seg(".text$07context")
int __stdcall ArchiveCallersContext(AssetBuffer** buffers, const char** names, MapResource** maps, ParameterLoader** parameters, SoundManager_0043a9b0** managers, const char* track_name, int count, StageEclLoader_00403850** stages) {
    for (int i = 0; i < count; ++i) {
        LoadAsset(names[i], buffers[i]);
        maps[i]->LoadMap(names[i]);
        parameters[i]->Load(names[i]);
        managers[i]->LoadTrack(i, track_name);
        stages[i]->Load(names[i]);
        Sound_LoadMusicTable_0043d670(track_name, managers[i]);
        reinterpret_cast<SoundPendingSlots_0043d640*>(managers[i])->LoadPendingSlot(track_name, i);
    }
    return count;
}
#pragma code_seg()

// Complete real archive closure, supplying the actual internal reader contract.
#define ARCHIVE_READ_SECTION ".text$03aread"
#define ARCHIVE_FIND_SECTION ".text$03bfind"
#define ARCHIVE_DECRYPT_SECTION ".text$04zdecrypt"
#define ARCHIVE_LOAD_SECTION ".text$05load"
#include "native_archive_read/read.cpp"
#include "native_archive_read/find.cpp"
#include "native_archive_read/decrypt.cpp"
#include "native_archive_read/load.cpp"
