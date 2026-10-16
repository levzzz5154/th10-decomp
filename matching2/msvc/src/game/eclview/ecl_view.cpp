// 0x0040A350: recreate the player, bullet, bomb, item, effect, enemy and HUD
// managers for the ECL viewer's selected script, then reset its menu.
#include "th10/game/startup_managers.hpp"
#include "th10/game/enemy_ctrl.hpp"
extern "C" void *g_enemy_ctrl;
extern "C" void *__cdecl Create6();
extern "C" void *__cdecl Create3();
extern "C" void *__cdecl Create2();
extern "C" void *__cdecl Create5();
extern "C" void *__cdecl Create7();
extern "C" void *__cdecl Create4();

// Complete 101-byte original: member receiver ESI, result EAX, plain RET.
#pragma code_seg(".text$00b")
int FactoryCallerState::InitializeManagers() {
    Create6();
    Create3();
    Create2();
    Create5();
    Create7();
    EnemyCtrl_Create(scripts_034[script_index_114]);
    Create4();
    void *parser = *(void **)((char *)g_enemy_ctrl + 0x54);
    menu_1ec.item_count = *(int *)((char *)parser + 8);
    menu_1ec.Advance(1);
    menu_1ec.Advance(-1);
    state_030 = 1;
    return 0;
}
#pragma code_seg()


// 0x0040A340: the ECL viewer's loader-thread entry; recreates the game
// managers for the selected script file (0x0040A350).
#include "th10/game/startup_managers.hpp"

// Complete original startup callback; loads the state for the private member ABI.
#pragma code_seg(".text$00ab")
extern "C" __declspec(noinline) int __cdecl EclView_LoadThread() {
    g_ecl_view->InitializeManagers();
    return 0;
}
#pragma code_seg()

