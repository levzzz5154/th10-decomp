// Compiler context only; never selected as recovered game code.
#include "../../src/render/anm_propagate.cpp"

// 0x00449210, a separate translation unit of this link.
void __fastcall AnimationManager_SetStopFrame(unsigned short frame, AnimationLookupContext* context,
                                              AnimationScriptId id);

struct AnimationChild_00449820;
struct AnimationHandle_00449820 {
    __declspec(noinline) AnimationChild_00449820* FindChild(int script_id);
};

struct AnimationRef_004497d0 {
    int value;
    AnimationRef_004497d0(int value) : value(value) {}
};
struct AnimationHandle_004497d0 {
    __declspec(noinline) AnimationRef_004497d0 FindChildRef(int script_id);
};

struct AnimationHandle_004243f0 {
    __declspec(noinline) void StopAtFrame6();
};

struct AnimationHandle_00449470 {
    __declspec(noinline) void SetStopFrame(unsigned short frame);
};

// The timed recovery record the added function initialises.  Declared here so
// this driver can call the member without defining it: its body is compiled
// separately and the whole-program pass still sees it.
struct RecoveryTimedState_00423510 {
    unsigned char unknown[0x2C4];
    __declspec(noinline) void InitializeTimedState();
};

#pragma code_seg(".text$80context")
int __stdcall StopAtFrameCompilerContext(AnimationHandle* handles, int count,
                                         RecoveryTimedState_00423510* states) {
    while (count--) {
        handles->StopAtFrame1();
        handles->StopAtFrame2();
        handles->StopAtFrame3();
        reinterpret_cast<AnimationHandle_00449470*>(handles)->SetStopFrame(
            *reinterpret_cast<unsigned short*>(states));
        AnimationManager_SetStopFrame(*reinterpret_cast<unsigned short*>(states),
            reinterpret_cast<AnimationLookupContext*>(states),
            *reinterpret_cast<AnimationScriptId*>(handles));
        reinterpret_cast<AnimationHandle_004243f0*>(handles)->StopAtFrame6();
        reinterpret_cast<AnimationHandle_00449820*>(handles)->FindChild(count);
        reinterpret_cast<AnimationHandle_004497d0*>(handles)->FindChildRef(count);
        handles++;
        states->InitializeTimedState();
        states++;
    }
    return 0;
}
#pragma code_seg()
