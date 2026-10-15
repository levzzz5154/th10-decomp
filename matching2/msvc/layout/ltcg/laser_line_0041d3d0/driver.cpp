// Complete public laser callback and actual existing link-entry wrapper.
#include "../../../src/game/laser/laser_line.cpp"
struct StageUpdateContext;
extern "C" int __stdcall StageUpdate(StageUpdateContext* context);
#pragma code_seg(".text$00entry")
void __fastcall StageUpdateCompilerCaller_004187c0(void* context) {
    StageUpdate(reinterpret_cast<StageUpdateContext*>(context));
}
#pragma code_seg()
