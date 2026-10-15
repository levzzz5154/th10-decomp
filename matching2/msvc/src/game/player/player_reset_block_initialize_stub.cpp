// Context-only stub: the model function (PlayerResetBlock::Initialize) lives in
// the large_player cluster's context sources
// (build_support/layout/ltcg/large_player_dependencies/runtime.cpp).

#include "th10/game/large_player_native.hpp"

// The selection state's address escapes here the way it does throughout the
// game: menus, tips and replays all hold GameSelectionView pointers.  This
// lives in the equivalence stub so the registered cluster build (which never
// compares Initialize) is untouched.
static void* selection_state_escape;
#pragma section(".data$00474c68escape", read, write)
__declspec(allocate(".data$00474c68escape")) struct GameSelectionView { int shot_type, character, unknown_08, difficulty; };
extern "C" GameSelectionView g_globals_character;
extern "C" __declspec(noinline) void* __stdcall SelectionStateRef(void) {
    return &g_globals_character.shot_type;
}
