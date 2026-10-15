// 0x0040A350: recreate the player, bullet, bomb, item, effect, enemy and HUD
// managers for the sprite viewer's selected script, then reset its menu.
#include "th10/game/startup_managers_0040a350.hpp"
#include "th10/game/enemy_manager_factory_0040d6b0.hpp"
extern "C" void *data_00477704;
extern "C" void *__cdecl Create_00425020();
extern "C" void *__cdecl Create_00406060();
extern "C" void *__cdecl Create_004056b0();
extern "C" void *__cdecl Create_0041aed0();
extern "C" void *__cdecl Create_0042b660();
extern "C" void *__cdecl Create_00414830();

// Complete 101-byte original: member receiver ESI, result EAX, plain RET.
#pragma code_seg(".text$00b")
int FactoryCallerState::InitializeManagers() {
    Create_00425020();
    Create_00406060();
    Create_004056b0();
    Create_0041aed0();
    Create_0042b660();
    EnemyManager_CreateRetail_0040d6b0(scripts_034[script_index_114]);
    Create_00414830();
    void *parser = *(void **)((char *)data_00477704 + 0x54);
    menu_1ec.item_count = *(int *)((char *)parser + 8);
    menu_1ec.Advance(1);
    menu_1ec.Advance(-1);
    state_030 = 1;
    return 0;
}
#pragma code_seg()
