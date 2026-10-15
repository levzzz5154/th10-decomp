#pragma once
#include <stddef.h>
#include "th10/core/func_ctrl.hpp"

// The same 0x68-byte manager passed to the message-host initializer at 0x0040D280.
// The tail list fields are not used by this factory or its teardown.
struct MessageParser_0040d280;
class EnemyCtrl {
public:
    unsigned int lifecycle_flags_000;
    unsigned char reserved_004[4];
    union { SchedulerTask *node_008; SchedulerTask *volatile update_node_008; };
    union { SchedulerTask *node_00C; SchedulerTask *volatile draw_node_00C; };
    unsigned char reserved_010[0x20];
    void* animation_archive_030;
    unsigned char reserved_034[0x0C];
    int timer_previous_040;
    int timer_current_044;
    float timer_elapsed_048;
    const float *timer_speed_04C;
    volatile unsigned int timer_flags_050;
    union { void **blocks_054; MessageParser_0040d280* parser_054; };
    unsigned char reserved_058[0x10];

    __declspec(noinline) void Destroy();
};

typedef char EnemyCtrl_size_is_68[sizeof(EnemyCtrl) == 0x68 ? 1 : -1];
typedef char EnemyCtrl_first_node_is_08[offsetof(EnemyCtrl, node_008) == 8 ? 1 : -1];
typedef char EnemyCtrl_second_node_is_0c[offsetof(EnemyCtrl, node_00C) == 12 ? 1 : -1];
typedef char EnemyCtrl_timer_flags_are_50[offsetof(EnemyCtrl, timer_flags_050) == 0x50 ? 1 : -1];
typedef char EnemyCtrl_blocks_are_54[offsetof(EnemyCtrl, blocks_054) == 0x54 ? 1 : -1];

struct EnemyCtrl;
extern "C" int __stdcall EnemyCtrl_Initialize(
    EnemyCtrl *host, int script_name);
extern "C" EnemyCtrl *__stdcall EnemyCtrl_Create(int script_name);
