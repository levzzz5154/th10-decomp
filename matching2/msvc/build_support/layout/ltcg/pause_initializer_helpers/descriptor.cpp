// 0x00424480: bind a screen rectangle to the sprite an animation shows.
//
// The source region is the sprite's rectangle in whole pixels. The region
// arrives in ESI and everything else on the stack.
#include "th10/game/pause_initializer.hpp"

#pragma code_seg(".text$07descriptor")
int SpriteRegion::BindToAnimation(AnimationHandle8 handle,
        int new_left, int new_top, int new_width, int new_height) {
    AnimationScriptId id; id.value = (int)handle.value;
    AnimationObject2* animation = reinterpret_cast<AnimationObject2*>(AnimationManager_Find(g_sprt_ctrl, id));
    AnimationSprite* sprite = animation->sprite;
    return Set(*animation->texture, new_left, new_top, new_width, new_height,
        static_cast<int>(sprite->left), static_cast<int>(sprite->top),
        static_cast<int>(sprite->width), static_cast<int>(sprite->height));
}
#pragma code_seg()
