// Complete 0x00424480: bind a screen region to an animation's current sprite.
#include "th10/game/pause_result_open_004231d0/descriptor.hpp"

// The animation lookup at 0x004491C0, as the player cluster declares it.
struct PickupAnimation;
struct AnimationRef {
    unsigned int value;
    AnimationRef(unsigned int value_) : value(value_) {}
};
struct PickupAnimationLists {
    __declspec(noinline) PickupAnimation* Find(AnimationRef handle);
};

#pragma code_seg(".text$f00424480F")
int SpriteRegion_00424480::BindToAnimation(AnimationHandle_00424480 handle,
        int new_left, int new_top, int new_width, int new_height) {
    AnimationObject_00424480* animation = reinterpret_cast<AnimationObject_00424480*>(
        static_cast<PickupAnimationLists*>(data_00491c10)->Find(AnimationRef(handle.value)));
    AnimationSprite_00424480* sprite = animation->sprite;
    return Set(*animation->texture, new_left, new_top, new_width, new_height,
        static_cast<int>(sprite->left), static_cast<int>(sprite->top),
        static_cast<int>(sprite->width), static_cast<int>(sprite->height));
}
#pragma code_seg()
