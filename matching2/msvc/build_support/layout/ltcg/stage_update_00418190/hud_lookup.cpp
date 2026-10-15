#define g_sprt_ctrl stage_hud_g_sprt_ctrl
#define g_front stage_hud_g_front
#define g_globals stage_hud_data_00474c40
#define g_ascii_manager stage_hud_data_004776e0
#define g_enemy_ctrl stage_hud_g_enemy_ctrl
#define g_player stage_hud_data_00477834
#define g_replay stage_hud_data_00477838
#define g_score stage_hud_data_0047783c
#define g_game_speed stage_hud_data_00476f78
#define data_00491fc4 stage_hud_data_00491fc4
#define data_00491fb8 stage_hud_data_00491fb8
#define g_sound_manager stage_hud_data_00492590
#include "hud_view.hpp"
// Compiler-only ABI anchors for the animation lookup (0x004491C0) and the
// flag setter (0x004492A0), placed by clusters whose recovered code precedes
// 0x004491C0. The setter forwards no receiver, so the pass drops ECX from
// every call. Never selected as recovered game code.
//
// The including source declares ResultAnimationId and the setter.
struct ResultAnimationEntry {
    ResultAnimationEntry* object;
    ResultAnimationEntry* next;
    unsigned char reserved_08[0x0C];
    ResultAnimationEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x340];
    unsigned int flags;
};

struct ResultAnimationLookup {
    unsigned char reserved[0x72DAD4];
    ResultAnimationEntry* primary_bucket;
    int reserved_2;
    ResultAnimationEntry* secondary_bucket;
};

#pragma code_seg(".text$004491c0_fn")
__declspec(noinline) void* __fastcall ResultAnimation_Find(
        ResultAnimationLookup* context, ResultAnimationId id) {
    if (!id.value)
        return 0;
    for (ResultAnimationEntry* node = context->primary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (ResultAnimationEntry* node = context->secondary_bucket; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$004492a0_fn")
__declspec(noinline) void* __fastcall ResultAnimation_Retire(
        ResultAnimationLookup* context, ResultAnimationId id) {
    ResultAnimationEntry* entry =
        (ResultAnimationEntry*)ResultAnimation_Find(context, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
    return entry;
}
#pragma code_seg()

#undef g_sprt_ctrl
#undef g_front
#undef g_globals
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef g_replay
#undef g_score
#undef g_game_speed
#undef data_00491fc4
#undef data_00491fb8
#undef g_sound_manager
