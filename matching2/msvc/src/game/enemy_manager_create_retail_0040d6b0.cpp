// 0x0040D6B0..0x0040D70E: create and publish an enemy manager.
// Native LTCG keeps the manager in EBX for initialization, and teardown receives
// it in EAX. The initializer still runs when allocation returned null.
#include <string.h>
#include "th10/game/enemy_manager_factory_0040d6b0.hpp"

void *__cdecl operator new(unsigned int size);
extern "C" void __cdecl entry_free_004524a1(void *memory);
extern "C" void *data_00477704;

#pragma code_seg(".text$04b")
extern "C" __declspec(noinline) EnemyManager_0040d530 *__stdcall
EnemyManager_CreateRetail_0040d6b0(int script_name) {
    EnemyManager_0040d530 *fresh = new EnemyManager_0040d530;
    EnemyManager_0040d530 *manager;
    if (fresh) {
        // Retail touches the existing timer flags before the complete wipe.
        unsigned int *timer_flags = (unsigned int *)((char *)fresh + 0x50);
        *timer_flags &= ~1u;
        memset(fresh, 0, sizeof(EnemyManager_0040d530));
        fresh->lifecycle_flags_000 |= 2u;
        data_00477704 = fresh;
        manager = fresh;
    } else {
        manager = 0;
    }

    if (asm_MessageHost_InitRetail_0040d280(
            (MessageHost_0040d280 *)manager, script_name) != 0) {
        if (manager) {
            manager->Destroy();
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()

#include "../unidentified/FUN_0040a350_0040a350.cpp"
#include "../unidentified/FUN_0040a340_0040a340.cpp"
#include "../../layout/ltcg/enemy_factory_dependencies/message_host_init.cpp"
#include "../../layout/ltcg/enemy_factory_dependencies/scheduler_tasks.cpp"
#include "../../layout/ltcg/enemy_factory_dependencies/bullet_entity_release_resource_0040d680.cpp"
#include "../../layout/ltcg/enemy_factory_dependencies/fun_00447810_00447810.cpp"
#include "../../layout/ltcg/enemy_factory_dependencies/animation_manager_mark_resource_for_removal_004493e0.cpp"
#include "fun_0040d530_0040d530.cpp"
#include "../../layout/ltcg/enemy_factory_dependencies/menu_advance.cpp"
