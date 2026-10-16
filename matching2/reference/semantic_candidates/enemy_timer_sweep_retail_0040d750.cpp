#include "th10/game/enemy_timer_sweep.hpp"

extern "C" int __stdcall asm_FUN_0040dc80_0040dc80(void* state);
extern float g_frame_timer_normal_lower;
extern float g_frame_timer_normal_upper;
extern "C" float data_00470afc;

#pragma code_seg(".text$01sweep")
__declspec(noinline) unsigned __int64
__stdcall EnemyTimerSweepRetail(EnemyTimerSweepManager_0040d750* manager) {
    EnemyTimerSweepLink_0040d750* node = manager->enemy_list_head_058;
    while (node != 0) {
        EnemyTimerSweepLink_0040d750* next = node->next;
        EnemyTimerSweepEntity_0040d750* enemy = node->owner;

        if ((enemy->flags_2480 & 0x20000u) == 0 &&
            asm_FUN_0040dc80_0040dc80(enemy->update_context_103c) == 0) {
            enemy->flags_2480 &= 0xFFFFFBFFu;
        } else if (enemy != 0) {
            enemy->RetireFromSweep(1);
        }

        node = next;
    }

    EnemyTimerSweepFrame_0040d750* frame = &manager->frame_040;
    const float* speed = frame->speed;
    frame->previous_frame = frame->current_frame;
    if (*speed > g_frame_timer_normal_lower && *speed < g_frame_timer_normal_upper) {
        const int current = ++frame->current_frame;
        frame->elapsed += 1.0f;
        return (static_cast<unsigned __int64>(
                    static_cast<unsigned int>(current)) << 32) | 1u;
    }

    frame->elapsed += *speed;
    const __int64 converted = static_cast<__int64>(frame->elapsed);
    frame->current_frame = static_cast<int>(converted);
    return (static_cast<unsigned __int64>(converted) &
            0xFFFFFFFF00000000ULL) | 1u;
}
#pragma code_seg()
