#include <string.h>
#include "th10/game/enemy_timer_sweep.hpp"

// BLOCKED (D3802): the readable 95-byte model differs in nine register
// identities; retail carries the manager in EBX across 0x0040D280 and passes
// it in EAX to 0x0040D530. See the focused recovery note for the LTCG blocker.
void *__cdecl operator new(unsigned int size);

typedef EnemyTimerSweepManager_0040d750 EnemyManager_0040d6b0;

extern "C" void *data_00477704;
extern "C" int __stdcall FUN_0040d280_0040d280(int script_name);
extern "C" void __fastcall FUN_0040d530_0040d530(
    EnemyManager_0040d6b0 *manager);
extern "C" void __cdecl entry_free_004524a1(void *memory);

// 0x0040D6B0..0x0040D70E: allocate and initialize the enemy manager.
extern "C" __declspec(noinline) EnemyManager_0040d6b0 *__stdcall
asm_EnemyManager_CreateRetail_0040d6b0(int script_name) {
    EnemyManager_0040d6b0 *fresh =
        (EnemyManager_0040d6b0 *)operator new(sizeof(EnemyManager_0040d6b0));
    EnemyManager_0040d6b0 *manager;

    if (fresh) {
        fresh->frame_flags_050 &= ~1u;
        memset(fresh, 0, sizeof(EnemyManager_0040d6b0));
        fresh->lifecycle_flags_000 |= 2u;
        data_00477704 = fresh;
        manager = fresh;
    } else {
        manager = 0;
    }

    if (FUN_0040d280_0040d280(script_name) != 0) {
        if (manager) {
            FUN_0040d530_0040d530(manager);
            entry_free_004524a1(manager);
        }
        return 0;
    }

    return manager;
}
