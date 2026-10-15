#include "../../../src/game/stage_entry.cpp"

// Complete genuine worker at 0x00417C70; only stage startup is selected here.
struct StageStartup_00417870;
extern "C" StageStartup_00417870* data_00477810;
extern "C" __declspec(noinline) int __stdcall StageStartup(StageStartup_00417870*);
#pragma code_seg(".text$00417c70_fn")
extern "C" void __cdecl Stage_StartupThread() {
    StageStartup(data_00477810);
}
#pragma code_seg()
