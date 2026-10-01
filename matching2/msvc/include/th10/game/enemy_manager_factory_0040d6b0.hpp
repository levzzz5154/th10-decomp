#pragma once
#include <stddef.h>
#include "th10/game/scheduler.hpp"

// The same 0x68-byte manager passed to the message-host initializer at 0x0040D280.
// The tail list fields are not used by this factory or its teardown.
class EnemyManager_0040d530 {
public:
    unsigned int lifecycle_flags_000;
    unsigned char reserved_004[4];
    SchedulerTask *node_008;
    SchedulerTask *node_00C;
    unsigned char reserved_010[0x30];
    int timer_previous_040;
    int timer_current_044;
    float timer_elapsed_048;
    const float *timer_speed_04C;
    unsigned int timer_flags_050;
    void **blocks_054;
    unsigned char reserved_058[0x10];

    __declspec(noinline) void Destroy();
};

typedef char EnemyManager_size_is_68[sizeof(EnemyManager_0040d530) == 0x68 ? 1 : -1];
typedef char EnemyManager_first_node_is_08[offsetof(EnemyManager_0040d530, node_008) == 8 ? 1 : -1];
typedef char EnemyManager_second_node_is_0c[offsetof(EnemyManager_0040d530, node_00C) == 12 ? 1 : -1];
typedef char EnemyManager_timer_flags_are_50[offsetof(EnemyManager_0040d530, timer_flags_050) == 0x50 ? 1 : -1];
typedef char EnemyManager_blocks_are_54[offsetof(EnemyManager_0040d530, blocks_054) == 0x54 ? 1 : -1];

struct MessageHost_0040d280;
extern "C" int __stdcall asm_MessageHost_InitRetail_0040d280(
    MessageHost_0040d280 *host, int script_name);
extern "C" EnemyManager_0040d530 *__stdcall EnemyManager_CreateRetail_0040d6b0(int script_name);
