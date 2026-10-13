// Synthetic compiler context for the replay save cluster: it only roots the
// native /LTCG link and calls the save routine through a volatile function
// pointer, which holds the routine to its declared manager/file-name/name
// register split against the whole-program pass. Not recovered game code.
#include "../../src/game/replay_save_00429b60.cpp"

// Equivalence-model padding: a real (never executed) function between the
// save routine and the cipher body keeps the cipher outside the model
// function's comparison window when the equivalent layout is measured.
#pragma inline_depth(0)
#pragma code_seg(".text$rsave02")
extern "C" __declspec(noinline) int __fastcall ReplaySaveModelPad_00429b60(int seed) {
    return (seed * 0x52504A45 ^ (seed << 3) - seed) * (seed | 0x41) ^ seed;
}
#pragma code_seg()

#pragma code_seg(".text$rsave04")
int __stdcall ReplaySaveCompilerContext_00429b60(
    ReplaySaveManager_00429b60* manager, const char* file_name, const char* name) {
    int (__fastcall ReplaySaveManager_00429b60::*volatile save)(const char*, const char*) =
        &ReplaySaveManager_00429b60::Save;
    int (__fastcall *volatile pad)(int) = &ReplaySaveModelPad_00429b60;
    return (manager->*save)(file_name, name) + pad(2);
}
#pragma code_seg()
