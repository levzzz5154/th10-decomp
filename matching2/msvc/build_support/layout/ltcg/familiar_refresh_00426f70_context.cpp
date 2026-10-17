// Compiler context only; never selected as recovered game code.
#include "../../../src/game/player/familiar_refresh.cpp"

// The counters block escapes through this helper: its address taken here is
// what keeps the stores before the character/shot-type switches ahead of
// their reloads. It is also the link's entry.
#pragma code_seg(".text$00401000_ctx")
extern "C" void* __stdcall FamiliarRefreshEscape() {
    return &g_globals_score;
}
#pragma code_seg()
