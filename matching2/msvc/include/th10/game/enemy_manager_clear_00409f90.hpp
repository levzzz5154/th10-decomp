#pragma once
#include "th10/render/animation_resource_removal.hpp"

// A scheduler task, as far as the manager touches it: bit 1 of the flags
// suspends the task.
struct EnemyTask_00409f90 {
    int priority;
    unsigned int flags;
};

// An enemy; only its deleting entry in slot 5 is called.
struct Enemy_00409f90 {
    virtual void Slot00() = 0;
    virtual void Slot04() = 0;
    virtual void Slot08() = 0;
    virtual void Slot0C() = 0;
    virtual void Slot10() = 0;
    virtual void Destroy(int release) = 0;
};
struct EnemyNode_00409f90 {
    Enemy_00409f90* enemy;
    EnemyNode_00409f90* next;
};

// The enemy manager at 0x00477704, as far as its clear touches it.
struct EnemyCtrlClearView {
    unsigned char reserved_000[8];
    EnemyTask_00409f90* update_task;
    EnemyTask_00409f90* draw_task;
    int field_10;
    unsigned char reserved_014[0x58 - 0x14];
    EnemyNode_00409f90* first;       // +0x58
    unsigned char reserved_05c[8];
    int spawn_count;                 // +0x64

    __declspec(noinline) void Clear();
};

// The animation manager's loaded-file slots; the enemy scripts use 9 to 12.
struct AnimationSlots_00409f90 {
    unsigned char reserved_000[0x3AD06C];
    void* slots[0x21];
};

extern "C" SprtCtrl* g_sprt_ctrl;
