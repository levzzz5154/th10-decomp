// 0x00404420: drop the two animations an owner holds and clear its active
// count. Native LTCG passes the owner in ESI.
struct AnimationLookupContext;
struct AnimationScriptId {
    int value;
};

void* __fastcall AnimationManager_SetFlag_004492a0(AnimationLookupContext* context,
                                                   AnimationScriptId id);

extern "C" AnimationLookupContext* g_sprt_ctrl;

struct AnimationPairOwner_00404420 {
    unsigned char reserved_0000[0x1EE4];
    int active_count;                       // +0x1EE4
    unsigned char reserved_1ee8[0x2A38 - 0x1EE8];
    AnimationScriptId primary;              // +0x2A38
    AnimationScriptId secondary;            // +0x2A3C

    __declspec(noinline) void ReleaseAnimations();
};

#pragma code_seg(".text$00fn")
void AnimationPairOwner_00404420::ReleaseAnimations() {
    AnimationLookupContext* context = g_sprt_ctrl;
    active_count = 0;
    AnimationManager_SetFlag_004492a0(context, primary);
    AnimationManager_SetFlag_004492a0(context, secondary);
}
#pragma code_seg()
