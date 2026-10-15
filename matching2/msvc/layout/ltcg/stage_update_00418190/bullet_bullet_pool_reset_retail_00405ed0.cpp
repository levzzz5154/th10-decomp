#define data_00491c10 stage_bullet_data_00491c10
#define data_0047770c stage_bullet_data_0047770c
#define data_00474c40 stage_bullet_data_00474c40
#define g_ascii_manager stage_bullet_data_004776e0
#define data_00477704 stage_bullet_data_00477704
#define g_player stage_bullet_data_00477834
#define data_00477838 stage_bullet_data_00477838
#define data_0047783c stage_bullet_data_0047783c
#define data_00476f78 stage_bullet_data_00476f78
#define data_00491fc4 stage_bullet_data_00491fc4
#define data_00491fb8 stage_bullet_data_00491fb8
#define data_00492590 stage_bullet_data_00492590
// 0x00405ED0 - Re-arm the bullet pool: retire the pool's animation resource,
// zero the whole slot array, rewind the free-slot cursor, and set the state
// word back to 5.
#include <string.h>

#include "th10/render/animation_resource_removal.hpp"

extern "C" AnimationManager* data_00491c10;

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
    AnimationManager* manager = data_00491c10;
    manager->MarkResourceForRemoval(animation);
    memset(slots, 0, sizeof(slots));
    cursor = slots;
    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(this) + 0x3E07A6) = 5;
}
#pragma code_seg()
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
