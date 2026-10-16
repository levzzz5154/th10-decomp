// Compiler context only; never selected as recovered game code.
#include "../../../src/game/card/anm_propagate.cpp"
#include "th10/game/playback_state.hpp"

// 0x00449210, a separate translation unit of this link.
void __fastcall AnimationManager_SetStopFrame(unsigned short frame, AnimationLookupContext* context,
                                              AnimationScriptId id);

struct AnimationChild2;
struct AnimationHandle16 {
    __declspec(noinline) AnimationChild2* FindChild(int script_id);
};

struct AnimationRef2 {
    int value;
    AnimationRef2(int value) : value(value) {}
};
struct AnimationHandle15 {
    __declspec(noinline) AnimationRef2 FindChildRef(int script_id);
};

struct AnimationHandle7 {
    __declspec(noinline) void StopAtFrame6();
};

// The timed recovery record the added function initialises.  Declared here so
// this driver can call the member without defining it: its body is compiled
// separately and the whole-program pass still sees it.
struct RecoveryTimedState {
    unsigned char unknown[0x2C4];
    __declspec(noinline) void InitializeTimedState();
};

struct AnimationRunHandle {
    AnimationScriptId value;
    __declspec(noinline) void SetStopFrameAndRun(unsigned short frame);
};
struct Title;
void __fastcall Title_DispatchAnimationSlot(int slot, Title* state);
void __fastcall Title_DispatchAnimationSlotSecondary(int slot, Title* state);
AnimationRef2 __fastcall Title_FindAnimationSlotChild(int slot, Title* state,
                                                                int script_id);

#pragma code_seg(".text$80context")
int __stdcall StopAtFrameCompilerContext(AnimationHandle* handles, int count,
                                         RecoveryTimedState* states) {
    while (count--) {
        handles->StopAtFrame1();
        handles->StopAtFrame2();
        handles->StopAtFrame3();
        reinterpret_cast<AnimationHandle11*>(handles)->SetStopFrame(
            *reinterpret_cast<unsigned short*>(states));
        AnimationManager_SetStopFrame(*reinterpret_cast<unsigned short*>(states),
            reinterpret_cast<AnimationLookupContext*>(states),
            *reinterpret_cast<AnimationScriptId*>(handles));
        reinterpret_cast<AnimationHandle7*>(handles)->StopAtFrame6();
        reinterpret_cast<AnimationHandle16*>(handles)->FindChild(count);
        reinterpret_cast<AnimationHandle15*>(handles)->FindChildRef(count);
        Title_DispatchAnimationSlot(count, reinterpret_cast<Title*>(states));
        Title_DispatchAnimationSlotSecondary(count, reinterpret_cast<Title*>(states));
        reinterpret_cast<AnimationRunHandle*>(handles)->SetStopFrameAndRun(
            *reinterpret_cast<unsigned short*>(states));
        Title_FindAnimationSlotChild(count, reinterpret_cast<Title*>(states), count);
        handles++;
        reinterpret_cast<PlaybackState*>(states)->SwitchPlaybackState();
        states->InitializeTimedState();
        states++;
    }
    return 0;
}
#pragma code_seg()
