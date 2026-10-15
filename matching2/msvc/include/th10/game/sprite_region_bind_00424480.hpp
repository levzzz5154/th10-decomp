#ifndef TH10_GAME_SPRITE_REGION_BIND_00424480_HPP
#define TH10_GAME_SPRITE_REGION_BIND_00424480_HPP

// A handle to a running animation; zero when there is none.
struct AnimationHandle_00424480 {
    unsigned int value;
};

// The sprite an animation currently shows.
struct AnimationSprite {
    unsigned char reserved_00[0x08];
    float left;                          // +0x08
    float top;                           // +0x0C
    unsigned char reserved_10[0x20];
    float height;                        // +0x30
    float width;                         // +0x34
};

// A running animation as this code sees it.
struct AnimationObject_00424480 {
    AnimationObject_00424480* object;    // +0x000: list nodes point at the animation
    AnimationObject_00424480* next;      // +0x004
    unsigned char reserved_008[0x300];
    int* texture;                        // +0x308
    unsigned char reserved_30c[0x88];
    AnimationSprite* sprite;    // +0x394
};

// The animation manager's two running lists.
struct AnimationLists_00424480 {
    unsigned char reserved_000[0x72DAD4];
    AnimationObject_00424480* primary;   // +0x72DAD4
    int reserved_72dad8;
    AnimationObject_00424480* secondary; // +0x72DADC

    // 0x004491C0: find a running animation by handle.
    __declspec(noinline) AnimationObject_00424480* Find(AnimationHandle_00424480 handle);
};

extern "C" AnimationLists_00424480* g_sprt_ctrl;

// A screen rectangle filled from a region of a texture.
struct SpriteRegion {
    int reserved_00;
    int texture;                         // +0x04: negative while unbound
    int left;                            // +0x08
    int top;                             // +0x0C
    int width;                           // +0x10
    int height;                          // +0x14
    int source_left;                     // +0x18
    int source_top;                      // +0x1C
    int source_width;                    // +0x20
    int source_height;                   // +0x24
    int state;                           // +0x28

    // Take a texture region; fails once a texture is bound.
    int Set(int new_texture, int new_left, int new_top, int new_width, int new_height,
            int new_source_left, int new_source_top, int new_source_width,
            int new_source_height) {
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

    // 0x00424480: bind to the sprite an animation currently shows.
    __declspec(noinline) int BindToAnimation(AnimationHandle_00424480 handle,
        int new_left, int new_top, int new_width, int new_height);
};

#endif
