// The replay save routine 0x00429B60 as its original translation unit, with
// the compiler context it was recovered against: the byte cipher it calls
// (an anchor at its retail address, so the whole-program pass gives both
// calls the key in AL), the score counters as one object whose address
// escapes in the whole program, and a synthetic caller. Not recovered code
// apart from the save routine.
#include "../../../src/game/replay/replay_save.cpp"

// The byte cipher compiled into this cluster so the whole-program pass gives
// both calls their retail AL key register. Anchor body, not recovered code.
#include "replay_save/encrypt.cpp"

// A real (never executed) function taking the score counters' address. The
// escape lets stores through pointers alias the score, which keeps the save
// routine's summary stores in retail order. Parked after the synthetic caller.
#pragma inline_depth(0)
#pragma code_seg(".text$rsave05")
extern "C" __declspec(noinline) int __fastcall ReplaySaveScoreEscape(int counters) {
    return (counters * 0x52504A45 ^ (counters << 3) - counters) * (counters | 0x41) ^ counters;
}
#pragma code_seg()

// Synthetic caller: it only roots the native /LTCG link and calls the save
// routine through a volatile function pointer, which holds the routine to
// its declared manager/file-name/name register split against the
// whole-program pass.
#pragma code_seg(".text$rsave04")
int __stdcall ReplaySaveCompilerContext_00429b60(
    ReplaySaveManager* manager, const char* file_name, const char* name) {
    int (__fastcall ReplaySaveManager::*volatile save)(const char*, const char*) =
        &ReplaySaveManager::Save;
    int (__fastcall *volatile escape)(int) = &ReplaySaveScoreEscape;
    return (manager->*save)(file_name, name) + escape((int)&g_globals_score);
}
#pragma code_seg()
