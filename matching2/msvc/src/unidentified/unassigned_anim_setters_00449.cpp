// Three one-call wrappers on an animation node. The node arrives in EAX and the
// callee takes its value in ECX, its manager in EDX and the key on the stack, a
// pair of private /LTCG choices no declaration fixes, so the wrappers are
// compiled as one cluster with an array-walking compiler context.
extern "C" void* data_00491c10;

struct AnimationNode_00449 {
    AnimationNode_00449* field_000;  // +0x0000
    __declspec(noinline) void SetStopFrameAndRun();
    __declspec(noinline) void SetPosition();
    __declspec(noinline) void SetTranslatedPosition();
};

extern "C" void __fastcall AnimationManager_SetStopFrameAndRun_00449250(
    void* value, void* manager, int unused);
extern "C" void __fastcall AnimationManager_SetPosition_004492f0(
    void* value, void* manager, int unused);
extern "C" void __fastcall AnimationManager_SetTranslatedPosition_00449350(
    void* value, void* manager, int unused);
#pragma code_seg(".text$01")
void AnimationNode_00449::SetStopFrameAndRun() {
    AnimationManager_SetStopFrameAndRun_00449250(field_000, data_00491c10, (int)field_000);
}
#pragma code_seg()

#pragma code_seg(".text$03")
void AnimationNode_00449::SetPosition() {
    AnimationManager_SetPosition_004492f0(field_000, data_00491c10, (int)field_000);
}
#pragma code_seg()

#pragma code_seg(".text$05")
void AnimationNode_00449::SetTranslatedPosition() {
    AnimationManager_SetTranslatedPosition_00449350(field_000, data_00491c10, (int)field_000);
}
#pragma code_seg()

