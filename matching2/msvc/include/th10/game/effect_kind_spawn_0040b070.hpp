#ifndef TH10_GAME_EFFECT_KIND_SPAWN_0040B070_HPP
#define TH10_GAME_EFFECT_KIND_SPAWN_0040B070_HPP

// A handle to a running animation; zero when there is none. Its constructor
// makes functions return it through a hidden pointer.
struct AnimationHandle_0040b070 {
    unsigned int value;

    AnimationHandle_0040b070() {}
};

// A running animation, as far as the spawners touch it.
struct AnimationNode_0040b070 {
    AnimationNode_0040b070* object;      // +0x000: list nodes point at the animation
    AnimationNode_0040b070* next;        // +0x004
    unsigned char reserved_008[0x18];
    int render_bucket;                   // +0x020
    unsigned char reserved_024[0x338];
    unsigned int flags;                  // +0x35C
    unsigned char reserved_360[0x38];
    int kind_value_a;                    // +0x398
    int kind_value_b;                    // +0x39C
};

// An animation file: 0x00449870 starts one of its scripts on an object.
struct AnimationBank {
    void* InitializeObject(void* object, int index);
};

// The animation manager's two running lists.
struct AnimationLists_0040b070 {
    unsigned char reserved_000[0x72DAD4];
    AnimationNode_0040b070* primary;     // +0x72DAD4
    int reserved_72dad8;
    AnimationNode_0040b070* secondary;   // +0x72DADC

    // 0x004491C0: find a running animation by handle.
    __declspec(noinline) AnimationNode_0040b070* Find(AnimationHandle_0040b070 handle);
};

// The animation manager's object pool.
struct AnimationPool_0040b070 {
    // 0x00449950: take a free animation object (heap-allocated when the pool
    // is full). It has to be a member: the callee-cleans-stack call is what
    // orders the entry of 0x0040B110.
    __declspec(noinline) AnimationNode_0040b070* Allocate();
};

extern "C" AnimationLists_0040b070* g_sprt_ctrl;
extern "C" void** __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0(
    void* manager, void** out, void* entity);

// One kind of effect: its script, an optional setup step and two values
// copied into the new animation.
struct EffectKind_0040b070 {
    short script;                                            // +0x00
    void (__fastcall* setup)(AnimationNode_0040b070* node, void* argument);  // +0x04
    int value_a;                                             // +0x08
    int value_b;                                             // +0x0C
};

extern "C" EffectKind_0040b070 g_effect_kinds[];

// The owner of an animation file.
struct EffectSpawnView {
    unsigned char reserved_00[0x10];
    AnimationBank* file;    // +0x10

    // 0x0040B070: start an effect of a kind from the owner's file.
    AnimationHandle_0040b070 __stdcall SpawnEffect(void* argument, int kind);
};

// 0x0040B110: the same for an animation file given directly.
AnimationHandle_0040b070 __stdcall SpawnEffectFromFile(
    int kind, AnimationBank* file, void* argument);

#endif
