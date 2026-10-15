#include "th10/source_views/enemy_ctrl_create_c34965_0.hpp"
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
