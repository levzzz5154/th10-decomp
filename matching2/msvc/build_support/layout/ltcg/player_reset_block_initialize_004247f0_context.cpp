// Compiler context only for the PlayerResetBlock::Initialize recovery
// (0x004247F0).  Mirrors the large_player translation unit so the ABI
// anchors' bodies and the factory caller bake the same private register
// conventions the equivalent model measured.  Not recovered game code.
#include "../../contexts/legacy/game/player_reset.cpp"
#include "large_player_dependencies/configure.cpp"
#include "large_player_dependencies/runtime.cpp"
#include "../../../src/game/player/recovery_create_large_resource_state.cpp"
#include "large_player_dependencies/script.cpp"
#include "large_player_dependencies/parameter.cpp"
#include "large_player_dependencies/archive.cpp"
#include "large_player_dependencies/logger.cpp"
#include "large_player_dependencies/scheduler.cpp"
#include "large_player_dependencies/callback.cpp"
#include "large_player_dependencies/menu.cpp"
#include "large_player_dependencies/caller.cpp"

// The compiler context: the retail factory caller's chain plus the escaping
// selection words (the equivalent measurement's stub root is the alias
// context; without it the character-table loads fold and the body loses its
// reloads).  Not recovered game code.
#pragma code_seg(".text$a03body")
extern "C" __declspec(noinline) int __stdcall PlayerResetInitializeContext(
        void** escape, FactoryCallerState* state) {
    escape[0] = &g_globals_character.shot_type;
    Create6(); Create3(); Create2();
    Create5(); Create7();
    EnemyCtrl_Create(state->scripts_034[state->script_index_114]);
    Create4();
    void* parser = *(void**)((char*)g_enemy_ctrl + 0x54);
    state->menu_1ec.item_count = *(int*)((char*)parser + 8);
    state->menu_1ec.Advance(1); state->menu_1ec.Advance(-1);
    state->state_030 = 1; return 0;
}
#pragma code_seg()
