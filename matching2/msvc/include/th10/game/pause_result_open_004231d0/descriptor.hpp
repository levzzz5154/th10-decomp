#ifndef TH10_PAUSE_RESULT_DESCRIPTOR_00424480_HPP
#define TH10_PAUSE_RESULT_DESCRIPTOR_00424480_HPP

#include <stddef.h>
#include "th10/game/pause_result_open_004231d0/open_animation.hpp"

// This handle is the same four-byte animation identifier used by the lookup.
struct AnimationHandle_00424480 {
    unsigned int value;
};

struct AnimationSprite_00424480 {
    unsigned char reserved_00[0x08];
    float left;                          // +0x08
    float top;                           // +0x0C
    unsigned char reserved_10[0x20];
    float height;                        // +0x30
    float width;                         // +0x34
};

struct AnimationObject_00424480 {
    unsigned char reserved_000[0x308];
    int* texture;                        // +0x308
    unsigned char reserved_30c[0x88];
    AnimationSprite_00424480* sprite;     // +0x394
};

// The descriptor passed to BindToAnimation is also the manager's leading
// screen-region record in the real pause/result opening callers.
struct SpriteRegion_00424480 {
    int reserved_00;
    int texture;                         // +0x04: negative while unbound
    int left;                            // +0x08
    int top;                             // +0x0C
    int width;                           // +0x10
    int height;                          // +0x14
    int source_left;                      // +0x18
    int source_top;                       // +0x1C
    int source_width;                     // +0x20
    int source_height;                    // +0x24
    int state;                           // +0x28

    int Set(int new_texture, int new_left, int new_top, int new_width,
            int new_height, int new_source_left, int new_source_top,
            int new_source_width, int new_source_height) {
        if (texture >= 0)
            return -1;
        texture = new_texture;
        left = new_left;
        top = new_top;
        width = new_width;
        height = new_height;
        source_left = new_source_left;
        source_top = new_source_top;
        source_width = new_source_width;
        source_height = new_source_height;
        state = 0;
        return 0;
    }

    __declspec(noinline) int BindToAnimation(AnimationHandle_00424480 handle,
        int new_left, int new_top, int new_width, int new_height);
};

typedef char DescriptorSizeCheck[(sizeof(SpriteRegion_00424480) == 0x2C) ? 1 : -1];
typedef char DescriptorTextureOffsetCheck[(offsetof(SpriteRegion_00424480, texture) == 4) ? 1 : -1];
typedef char AnimationTextureOffsetCheck[(offsetof(AnimationObject_00424480, texture) == 0x308) ? 1 : -1];
typedef char AnimationSpriteOffsetCheck[(offsetof(AnimationObject_00424480, sprite) == 0x394) ? 1 : -1];
typedef char SpriteHeightOffsetCheck[(offsetof(AnimationSprite_00424480, height) == 0x30) ? 1 : -1];
typedef char SpriteWidthOffsetCheck[(offsetof(AnimationSprite_00424480, width) == 0x34) ? 1 : -1];

#endif
