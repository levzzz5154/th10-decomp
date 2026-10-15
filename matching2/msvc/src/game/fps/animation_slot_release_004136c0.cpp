// 0x004136C0 (97 bytes): hand the six animations a slot holds back to the
// animation manager (marking each as script owned so it removes itself) and
// forget their ids. Native LTCG passes the slot in ESI.
struct AnimationLookupContext;
struct AnimationScriptId {
    int value;
};

void* __fastcall AnimationManager_SetFlag_004492a0(AnimationLookupContext* context,
                                                   AnimationScriptId id);

extern "C" AnimationLookupContext* data_00491c10;

// An animation a game object owns, named by its id.
struct OwnedAnimation_004136c0 {
    AnimationScriptId id;

    // Let the manager dispose of the animation and forget it.
    void Release() {
        AnimationManager_SetFlag_004492a0(data_00491c10, id);
        id.value = 0;
    }
};

struct AnimationSlot_004136c0 {
    enum { ANIMATION_COUNT = 6 };

    unsigned char reserved_00[0x40];
    OwnedAnimation_004136c0 animations[ANIMATION_COUNT];   // +0x40

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$00fn")
void AnimationSlot_004136c0::Release() {
    animations[0].Release();
    animations[1].Release();
    animations[2].Release();
    animations[3].Release();
    animations[4].Release();
    animations[5].Release();
}
#pragma code_seg()
