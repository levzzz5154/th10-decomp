// Complete 0x00424480: bind a screen region to an animation's current sprite.
#include "th10/game/pause_result_open_004231d0/descriptor.hpp"

#pragma code_seg(".text$00424480_fn")
int SpriteRegion_00424480::BindToAnimation(AnimationHandle_00424480 handle,
        int new_left, int new_top, int new_width, int new_height) {
    AnimationScriptId id(static_cast<int>(handle.value));
    AnimationObject_00424480* animation =
        static_cast<AnimationObject_00424480*>(AnimationManager_Find_004491c0(
            static_cast<AnimationLookupContext*>(data_00491c10), id));
    AnimationSprite_00424480* sprite = animation->sprite;
    return Set(*animation->texture, new_left, new_top, new_width, new_height,
        static_cast<int>(sprite->left), static_cast<int>(sprite->top),
        static_cast<int>(sprite->width), static_cast<int>(sprite->height));
}
#pragma code_seg()
