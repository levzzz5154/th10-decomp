#define g_sprt_ctrl stage_bullet_g_sprt_ctrl
#define g_front stage_bullet_g_front
#define g_globals stage_bullet_data_00474c40
#define g_ascii_manager stage_bullet_data_004776e0
#define g_enemy_ctrl stage_bullet_g_enemy_ctrl
#define g_player stage_bullet_data_00477834
#define data_00477838 stage_bullet_data_00477838
#define data_0047783c stage_bullet_data_0047783c
#define g_game_speed stage_bullet_data_00476f78
#define data_00491fc4 stage_bullet_data_00491fc4
#define data_00491fb8 stage_bullet_data_00491fb8
#define g_sound_manager stage_bullet_data_00492590
// 0x00405ED0 - Re-arm the bullet pool: retire the pool's animation resource,
// zero the whole slot array, rewind the free-slot cursor, and set the state
// word back to 5.
#include <string.h>

#include "th10/render/animation_resource_removal.hpp"

extern "C" SprtCtrl* g_sprt_ctrl;

struct BulletPool {
    unsigned char reserved_000[0x10];
    unsigned int* cursor;
    unsigned char reserved_014[0x60 - 0x14];
    unsigned int slots[0xF82BC];
    void* animation;

    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$00405ed0_fn")
void BulletPool::Reset() {
    SprtCtrl* manager = g_sprt_ctrl;
    manager->MarkResourceForRemoval(animation);
    memset(slots, 0, sizeof(slots));
    cursor = slots;
    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this) + 0x3E07A6) = 5;
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef g_game_speed
#undef data_00491fc4
#undef data_00491fb8
#undef g_sound_manager
