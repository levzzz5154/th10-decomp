#include "th10/game/large_player_native.hpp"
struct EnemyCtrl;
extern "C" EnemyCtrl* __stdcall EnemyCtrl_Create(int);
extern "C" void* g_enemy_ctrl;
PlayerResetBlock* __cdecl Create6();
extern "C" void *__cdecl Create3();
extern "C" void *__cdecl Create2();
extern "C" void *__cdecl Create5();
extern "C" void *__cdecl Create7();
extern "C" void *__cdecl Create4();
#include "th10/game/menu_cursor.hpp"
struct FactoryCallerState {
 unsigned char reserved_000[0x30]; int state_030; int *scripts_034;
 unsigned char reserved_038[0x114-0x38]; int script_index_114;
 unsigned char reserved_118[0x1ec-0x118]; MenuCursor menu_1ec;
};
#pragma code_seg(".text$a03body")
extern "C" __declspec(noinline) int __stdcall EnemyFactoryCaller_0040a350(FactoryCallerState *state) {
 Create6(); Create3(); Create2();
 Create5(); Create7();
 EnemyCtrl_Create(state->scripts_034[state->script_index_114]);
 Create4();
 void *parser = *(void **)((char *)g_enemy_ctrl + 0x54);
 state->menu_1ec.item_count = *(int *)((char *)parser + 8);
 state->menu_1ec.Advance(1); state->menu_1ec.Advance(-1);
 state->state_030=1; return 0;
}
#pragma code_seg()
