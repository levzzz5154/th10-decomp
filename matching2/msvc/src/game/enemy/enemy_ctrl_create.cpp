// 0x0040D6B0..0x0040D70E: create and publish an enemy manager.
// Native LTCG keeps the manager in EBX for initialization, and teardown receives
// it in EAX. The initializer still runs when allocation returned null.
#include <string.h>
#include "th10/game/enemy_ctrl.hpp"

void *__cdecl operator new(unsigned int size);
extern "C" void __cdecl entry_free_004524a1(void *memory);
extern "C" void *g_enemy_ctrl;

#pragma code_seg(".text$04b")
extern "C" __declspec(noinline) EnemyCtrl *__stdcall
EnemyCtrl_Create(int script_name) {
    EnemyCtrl *fresh = new EnemyCtrl;
    EnemyCtrl *manager;
    if (fresh) {
        // Retail touches the existing timer flags before the complete wipe.
        unsigned int *timer_flags = (unsigned int *)((char *)fresh + 0x50);
        *timer_flags &= ~1u;
        memset(fresh, 0, sizeof(EnemyCtrl));
        fresh->lifecycle_flags_000 |= 2u;
        g_enemy_ctrl = fresh;
        manager = fresh;
    } else {
        manager = 0;
    }

    if (EnemyCtrl_Initialize(
            (EnemyCtrl *)manager, script_name) != 0) {
        if (manager) {
            manager->Destroy();
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()

#include "../eclview/ecl_view_create_managers.cpp"
#include "../eclview/ecl_view_load_thread.cpp"
#include "../../../layout/ltcg/enemy_factory_dependencies/message_host_init.cpp"
#include "../../../layout/ltcg/enemy_factory_dependencies/scheduler_tasks.cpp"
#include "../../../layout/ltcg/enemy_factory_dependencies/bullet_entity_release_resource_0040d680.cpp"
#include "../../../layout/ltcg/enemy_factory_dependencies/fun_00447810_00447810.cpp"
#include "../../../layout/ltcg/enemy_factory_dependencies/animation_manager_mark_resource_for_removal_004493e0.cpp"
#include "../fun_0040d530_0040d530.cpp"
#include "../../../layout/ltcg/enemy_factory_dependencies/menu_advance.cpp"
