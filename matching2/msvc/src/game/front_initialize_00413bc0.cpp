#include "th10/game/front_initialize_00413bc0.hpp"
static __forceinline Entity *AllocateFrontObject(void *resource, int script, int offset = 0) {
    Entity *object = reinterpret_cast<FrontAnimationPool *>(data_00491c10)->Allocate();
    unsigned int flags = object->flags_35C | 0x40000000;
    script += offset;
    object->render_bucket = 15;
    object->flags_35C = flags;
    reinterpret_cast<FrontAnimationResource *>(resource)->InitializeObject(object, script);
    return object;
}
#pragma code_seg(".text$00413bc0_fn")
void FrontInitialization_00413bc0::Initialize() {
    if (update_task)
        update_task->flags |= 2;
    if (draw_task)
        draw_task->flags |= 2;
    if (!persistent_a.value) {
        Entity *object = AllocateFrontObject(captions, 0);
        FrontAnimationId id =
            reinterpret_cast<FrontAnimationLists *>(data_00491c10)->RegisterPrimaryBack(object);
        persistent_a = id;
    }
    if (!persistent_b.value) {
        Entity *object = AllocateFrontObject(captions, 1);
        // Retail registers this object without writing the second handle slot.
        reinterpret_cast<FrontAnimationLists *>(data_00491c10)->RegisterPrimaryBack(object);
    }
    if (!(animations[0].flags_35C & 1)) {
        int script = 20;
        for (int count = 10; count; --count, ++script) {
            Entity *score = &animations[script - 10];
            LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710 *>(captions),
                                reinterpret_cast<AnimationObject_0043e710 *>(score - 10),
                                script - 10);
            LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710 *>(captions),
                                reinterpret_cast<AnimationObject_0043e710 *>(score), script);
        }
        for (int i = 0; i < 9; ++i)
            LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710 *>(captions),
                                reinterpret_cast<AnimationObject_0043e710 *>(&animations[20 + i]),
                                30 + i);
        for (int i = 0; i < 4; ++i)
            LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710 *>(captions),
                                reinterpret_cast<AnimationObject_0043e710 *>(&animations[29 + i]),
                                47 + i);
        for (int i = 0; i < 2; ++i)
            LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710 *>(captions),
                                reinterpret_cast<AnimationObject_0043e710 *>(&animations[33 + i]),
                                80 + i);
        for (int i = 0; i < 7; ++i)
            LoadScript_0043e710(reinterpret_cast<AnimationResource_0043e710 *>(captions),
                                reinterpret_cast<AnimationObject_0043e710 *>(&animations[35 + i]),
                                51 + i);
    }
    SetLifeIcons(data_00474c40.lives);
    // Split the signed power word into its whole value and two decimal digits.
    int whole = data_00474c40.power_units / 20;
    int fraction = (data_00474c40.power_units % 20) * 100 / 20;
    reinterpret_cast<Resource_0043e5a0 *>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject_0043e5a0 *>(&animations[29]), whole + 8);
    int digit = fraction % 10;
    reinterpret_cast<Resource_0043e5a0 *>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject_0043e5a0 *>(&animations[31]), fraction / 10 + 8);
    reinterpret_cast<Resource_0043e5a0 *>(captions)->ConfigureObject(
        reinterpret_cast<AnimationObject_0043e5a0 *>(&animations[32]), digit + 8);
    if (data_00491fb8 != 8) {
        if (!(data_00474c40.flags.bytes[0] & 0x20)) {
            Entity *object = AllocateFrontObject(alternate_resource, 0);
            RegisterFrontInline(reinterpret_cast<FrontAnimationLists *>(data_00491c10), object);
            object = AllocateFrontObject(alternate_resource, 1);
            RegisterFrontInline(reinterpret_cast<FrontAnimationLists *>(data_00491c10), object);
        }
    }
    if (data_00474c40.flags.bytes[0] & 0x20) {
        Entity *object = AllocateFrontObject(captions, 113);
        RegisterFrontInline(reinterpret_cast<FrontAnimationLists *>(data_00491c10), object);
    }
    LoadScript_0043e710(
        reinterpret_cast<AnimationResource_0043e710 *>(g_ascii_manager->title_resource),
        reinterpret_cast<AnimationObject_0043e710 *>(&animations[42]), 0);
    if (data_00474c40.stage == 1 && !data_00477810->stage_one_gate && !data_00474c40.continues) {
        Entity *object = AllocateFrontObject(captions, 79);
        RegisterFrontInline(reinterpret_cast<FrontAnimationLists *>(data_00491c10), object);
    }
    if (data_00491fc4) {
        Entity *object = AllocateFrontObject(captions, data_00474c40.difficulty, 102);
        FrontAnimationLists *lists = reinterpret_cast<FrontAnimationLists *>(data_00491c10);
        RegisterFrontInline(lists, object);
        difficulty_caption.value = lists->next_id.value;
        data_00491c10->SetFrame3Inline(difficulty_caption);
    }
    Entity *object = AllocateFrontObject(captions, data_00474c40.difficulty, 107);
    FrontAnimationLists *lists = reinterpret_cast<FrontAnimationLists *>(data_00491c10);
    RegisterFrontInline(lists, object);
    FrontAnimationId caption_id = difficulty_caption;
    difficulty_label = lists->next_id;
    // The final tree operation deliberately uses the caption's handle again.
    data_00491c10->SetFrame3Inline(caption_id);
    field_9e90 = 0;
}
#pragma code_seg()
