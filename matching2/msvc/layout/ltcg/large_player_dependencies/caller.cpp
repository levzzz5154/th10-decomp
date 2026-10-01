#include "th10/game/large_player_native.hpp"
struct EnemyManager_0040d6b0;
extern "C" EnemyManager_0040d6b0* __stdcall EnemyManager_CreateRetail_0040d6b0(int);
extern "C" void* data_00477704;
PlayerResetBlock* __cdecl Create_00425020();
extern "C" void *__cdecl Create_00406060();
extern "C" void *__cdecl Create_004056b0();
extern "C" void *__cdecl Create_0041aed0();
extern "C" void *__cdecl Create_0042b660();
extern "C" void *__cdecl Create_00414830();
#include "th10/game/menu_cursor.hpp"
struct FactoryCallerState {
 unsigned char reserved_000[0x30]; int state_030; int *scripts_034;
 unsigned char reserved_038[0x114-0x38]; int script_index_114;
 unsigned char reserved_118[0x1ec-0x118]; MenuCursor menu_1ec;
};
#pragma code_seg(".text$a03body")
extern "C" __declspec(noinline) int __stdcall EnemyFactoryCaller_0040a350(FactoryCallerState *state) {
 Create_00425020(); Create_00406060(); Create_004056b0();
 Create_0041aed0(); Create_0042b660();
 EnemyManager_CreateRetail_0040d6b0(state->scripts_034[state->script_index_114]);
 Create_00414830();
 void *parser = *(void **)((char *)data_00477704 + 0x54);
 state->menu_1ec.item_count = *(int *)((char *)parser + 8);
 state->menu_1ec.Advance(1); state->menu_1ec.Advance(-1);
 state->state_030=1; return 0;
}
#pragma code_seg()
