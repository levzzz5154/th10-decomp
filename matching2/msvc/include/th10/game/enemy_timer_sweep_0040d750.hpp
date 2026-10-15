#pragma once
#include <stddef.h>

struct EnemyTimerSweepEntity;

// This link is embedded in the enemy at +0x116C. Its owner points back to the
// containing enemy, followed by the forward and backward manager-list links.
struct EnemyTimerSweepLink {
    EnemyTimerSweepEntity* owner;
    EnemyTimerSweepLink* next;
    EnemyTimerSweepLink* previous;
};

struct EnemyTimerSweepFrame {
    int previous_frame;
    int current_frame;
    float elapsed;
    const float* speed;

    float Speed() const { return *speed; }
    // The usual frame tick; this copy adds the elapsed time to the speed
    // value returned by the accessor, which fixes the x87 operand order.
    void Tick();
};

// One 0x68-byte manager object is allocated at 0x0040D6B0 and initialized by
// 0x0040D280. The same object owns the callback records, frame timer, parser,
// and enemy-list endpoints used by the sweep and teardown paths.
struct EnemyCtrlSweepView {
    unsigned int lifecycle_flags_000;
    unsigned int reserved_004;
    void* primary_callback_record_008;
    void* secondary_callback_record_00c;
    unsigned char reserved_010[0x20];
    void* animation_archive_030;
    unsigned char reserved_034[0x0C];
    EnemyTimerSweepFrame frame_040;
    unsigned int frame_flags_050;
    void* message_parser_054;
    EnemyTimerSweepLink* enemy_list_head_058;
    EnemyTimerSweepLink* enemy_list_tail_05c;
    int enemy_count_060;
    unsigned char reserved_064[4];

    __declspec(noinline) int Sweep();
};

extern "C" {
// 0x0040DC80: one enemy update step over the context at enemy+0x103C;
// nonzero when the enemy has finished.
int __stdcall EnemyUpdate(void* update_context);
}
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;

inline void EnemyTimerSweepFrame::Tick() {
    previous_frame = current_frame;
    if (Speed() > g_frame_timer_normal_lower && Speed() < g_frame_timer_normal_upper) {
        ++current_frame;
        elapsed += 1.0f;
    } else {
        current_frame = int(elapsed = Speed() + elapsed);
    }
}

struct EnemyTimerSweepEntity {
    virtual void UnknownVtable00() = 0;
    virtual void UnknownVtable04() = 0;
    virtual void UnknownVtable08() = 0;
    virtual void UnknownVtable0C() = 0;
    virtual void UnknownVtable10() = 0;
    virtual void RetireFromSweep(int reason) = 0;

    unsigned char reserved_0004[0x1030];
    void* free_list_1034;
    unsigned char reserved_1038[4];
    unsigned char update_context_103c[0x130];
    EnemyTimerSweepLink link_116c;
    unsigned char reserved_1178[0x2480 - 0x1178];
    unsigned int flags_2480;
    unsigned char reserved_2484[8];
    int manager_index_248c;
    unsigned char reserved_2490[0x2518 - 0x2490];
};

typedef char EnemyTimerSweepManager_size_check[
    sizeof(EnemyCtrlSweepView) == 0x68 ? 1 : -1];
typedef char EnemyTimerSweepFrame_size_check[
    sizeof(EnemyTimerSweepFrame) == 0x10 ? 1 : -1];
typedef char EnemyTimerSweepFrame_offset_check[
    offsetof(EnemyCtrlSweepView, frame_040) == 0x40 ? 1 : -1];
typedef char EnemyTimerSweepListHead_offset_check[
    offsetof(EnemyCtrlSweepView, enemy_list_head_058) == 0x58 ? 1 : -1];
typedef char EnemyTimerSweepListTail_offset_check[
    offsetof(EnemyCtrlSweepView, enemy_list_tail_05c) == 0x5C ? 1 : -1];
typedef char EnemyTimerSweepEnemyCount_offset_check[
    offsetof(EnemyCtrlSweepView, enemy_count_060) == 0x60 ? 1 : -1];
typedef char EnemyTimerSweepLink_size_check[
    sizeof(EnemyTimerSweepLink) == 0x0C ? 1 : -1];
typedef char EnemyTimerSweepEntity_link_offset_check[
    offsetof(EnemyTimerSweepEntity, link_116c) == 0x116C ? 1 : -1];
typedef char EnemyTimerSweepEntity_flags_offset_check[
    offsetof(EnemyTimerSweepEntity, flags_2480) == 0x2480 ? 1 : -1];
typedef char EnemyTimerSweepEntity_size_check[
    sizeof(EnemyTimerSweepEntity) == 0x2518 ? 1 : -1];
typedef char EnemyTimerSweep_x86_pointer_check[
    sizeof(void*) == 4 ? 1 : -1];
