// Existing public laser callback plus a complete actual fastcall wrapper.
// The 4187C0 wrapper is only the native link entry and earns no new credit.
#include "../../../src/game/laser/laser_grow_update.cpp"
struct StageUpdateContext;
extern "C" int __stdcall StageUpdate(StageUpdateContext* context);
#pragma code_seg(".text$10entry")
void __fastcall StageUpdateCompilerCaller_004187c0(void* context) {
    StageUpdate(reinterpret_cast<StageUpdateContext*>(context));
}
#pragma code_seg()
