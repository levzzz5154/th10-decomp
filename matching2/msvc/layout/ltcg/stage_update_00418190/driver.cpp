// Complete StageUpdate callback and its existing fastcall wrapper.
#include "../../../src/game/stage_update.cpp"
#pragma code_seg(".text$004187c0_context")
void __fastcall StageUpdateCompilerCaller_004187c0(void* context) {
    StageUpdate(reinterpret_cast<StageUpdateContext*>(context));
}
#pragma code_seg()
