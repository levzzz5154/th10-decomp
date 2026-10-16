#define g_sprt_ctrl stage_front_g_sprt_ctrl
#define g_front stage_front_g_front
#define g_globals stage_front_data
#define g_ascii_manager stage_front_data_004776e0
#define g_enemy_ctrl stage_front_g_enemy_ctrl
#define g_player stage_front_data_00477834
#define g_replay stage_front_data_00477838
#define g_score stage_front_data_0047783c
#define g_game_speed stage_front_data_00476f78
#define g_stage_flags stage_front_data_00491fc4
#define g_main_state stage_front_data_00491fb8
#define g_sound_manager stage_front_data_00492590
#include "front_view.hpp"
static __forceinline Entity *AllocateFrontObject(void *resource, int script, int offset = 0) {
    Entity *object = reinterpret_cast<FrontAnimationPool *>(g_sprt_ctrl)->Allocate();
    unsigned int flags = object->flags_35C | 0x40000000;
    script += offset;
    object->render_bucket = 15;
    object->flags_35C = flags;
    reinterpret_cast<FrontAnimationResource *>(resource)->InitializeObject(object, script);
    return object;
}
#pragma code_seg(".text$00413bc0_fn")
void FrontInitializeView::Initialize() {
    if (update_task)
        update_task->flags |= 2;
    if (draw_task)
        draw_task->flags |= 2;
    if (!persistent_a.value) {
        Entity *object = AllocateFrontObject(captions, 0);
        FrontAnimationId id =
            reinterpret_cast<FrontAnimationLists *>(g_sprt_ctrl)->RegisterPrimaryBack(object);
        persistent_a = id;
    }
    if (!persistent_b.value) {
        Entity *object = AllocateFrontObject(captions, 1);
        // Retail registers this object without writing the second handle slot.
        reinterpret_cast<FrontAnimationLists *>(g_sprt_ctrl)->RegisterPrimaryBack(object);
    }
    if (!(animations[0].flags_35C & 1)) {
        int script = 20;
        for (int count = 10; count; --count, ++script) {
            Entity *score = &animations[script - 10];
            LoadScript2(reinterpret_cast<AnimationResourceFile *>(captions),
                                reinterpret_cast<AnimationObjectFile *>(score - 10),
                                script - 10);
            LoadScript2(reinterpret_cast<AnimationResourceFile *>(captions),
                                reinterpret_cast<AnimationObjectFile *>(score), script);
        }
        for (int i = 0; i < 9; ++i)
            LoadScript2(reinterpret_cast<AnimationResourceFile *>(captions),
                                reinterpret_cast<AnimationObjectFile *>(&animations[20 + i]),
                                30 + i);
        for (int i = 0; i < 4; ++i)
            LoadScript2(reinterpret_cast<AnimationResourceFile *>(captions),
                                reinterpret_cast<AnimationObjectFile *>(&animations[29 + i]),
                                47 + i);
        for (int i = 0; i < 2; ++i)
            LoadScript2(reinterpret_cast<AnimationResourceFile *>(captions),
                                reinterpret_cast<AnimationObjectFile *>(&animations[33 + i]),
                                80 + i);
        for (int i = 0; i < 7; ++i)
            LoadScript2(reinterpret_cast<AnimationResourceFile *>(captions),
                                reinterpret_cast<AnimationObjectFile *>(&animations[35 + i]),
                                51 + i);
    }
    SetLifeIcons(g_globals.lives);
    // Split the signed power word into its whole value and two decimal digits.
    int whole = g_globals.power_units / 20;
    int fraction = (g_globals.power_units % 20) * 100 / 20;
    reinterpret_cast<Resource2 *>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject3 *>(&animations[29]), whole + 8);
    int digit = fraction % 10;
    reinterpret_cast<Resource2 *>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject3 *>(&animations[31]), fraction / 10 + 8);
    reinterpret_cast<Resource2 *>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject3 *>(&animations[32]), digit + 8);
    if (g_main_state != 8) {
        if (!(g_globals.flags.bytes[0] & 0x20)) {
            Entity *object = AllocateFrontObject(alternate_resource, 0);
            RegisterFrontInline(reinterpret_cast<FrontAnimationLists *>(g_sprt_ctrl), object);
            object = AllocateFrontObject(alternate_resource, 1);
            RegisterFrontInline(reinterpret_cast<FrontAnimationLists *>(g_sprt_ctrl), object);
        }
    }
    if (g_globals.flags.bytes[0] & 0x20) {
        Entity *object = AllocateFrontObject(captions, 113);
        RegisterFrontInline(reinterpret_cast<FrontAnimationLists *>(g_sprt_ctrl), object);
    }
    LoadScript2(
        reinterpret_cast<AnimationResourceFile *>(g_ascii_manager->title_resource),
        reinterpret_cast<AnimationObjectFile *>(&animations[42]), 0);
    if (g_globals.stage == 1 && !g_game->stage_one_gate && !g_globals.continues) {
        Entity *object = AllocateFrontObject(captions, 79);
        RegisterFrontInline(reinterpret_cast<FrontAnimationLists *>(g_sprt_ctrl), object);
    }
    if (g_stage_flags) {
        Entity *object = AllocateFrontObject(captions, g_globals.difficulty, 102);
        FrontAnimationLists *lists = reinterpret_cast<FrontAnimationLists *>(g_sprt_ctrl);
        RegisterFrontInline(lists, object);
        difficulty_caption.value = lists->next_id.value;
        g_sprt_ctrl->SetFrame3Inline(difficulty_caption);
    }
    Entity *object = AllocateFrontObject(captions, g_globals.difficulty, 107);
    FrontAnimationLists *lists = reinterpret_cast<FrontAnimationLists *>(g_sprt_ctrl);
    RegisterFrontInline(lists, object);
    FrontAnimationId caption_id = difficulty_caption;
    difficulty_label = lists->next_id;
    // The final tree operation deliberately uses the caption's handle again.
    g_sprt_ctrl->SetFrame3Inline(caption_id);
    field_9e90 = 0;
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
#undef g_stage_flags
#undef g_main_state
#undef g_sound_manager
