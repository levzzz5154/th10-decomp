// Compiler context only; no context bytes count as recovered game code.
#include "../../src/game/asset_buffer.cpp"

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

#pragma code_seg(".text$07context")
int __stdcall ArchiveCallersContext(AssetBuffer** buffers, const char** names, MapResource** maps, ParameterLoader** parameters, SoundManager_0043a9b0** managers, const char* track_name, int count) {
    for (int i = 0; i < count; ++i) {
        LoadAsset(names[i], buffers[i]);
        maps[i]->LoadMap(names[i]);
        parameters[i]->Load(names[i]);
        managers[i]->LoadTrack(i, track_name);
    }
    return count;
}
#pragma code_seg()
