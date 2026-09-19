// Compiler context only; never selected as recovered game code.
#include "../../src/render/anm_propagate.cpp"

// The timed recovery record the added function initialises.  Declared here so
// this driver can call the member without defining it: its body is compiled
// separately and the whole-program pass still sees it.
struct RecoveryTimedState_00423510 {
    unsigned char unknown[0x2C4];
    __declspec(noinline) void InitializeTimedState();
};

#pragma code_seg(".text$70context")
int __stdcall StopAtFrameCompilerContext(AnimationHandle* handles, int count,
                                         RecoveryTimedState_00423510* states) {
    while (count--) {
        handles->StopAtFrame1();
        handles->StopAtFrame2();
        handles->StopAtFrame3();
        handles++;
        states->InitializeTimedState();
        states++;
    }
    return 0;
}
#pragma code_seg()
