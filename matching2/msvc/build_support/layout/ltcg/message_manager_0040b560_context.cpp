#define TH10_ENDING_TEXT_LAYOUT_ONLY
#define TH10_ENDING_TEXT_WORKER_SECTION ".text$88worker"
#define TH10_ENDING_TEXT_CONSTRUCTOR_SECTION ".text$05ctor"
#include "../../../src/game/ending/ending_text_construct.cpp"
#include "../../../src/game/ending/ending_initialize.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall EndingContext(Ending* state, GameCounters_0040b560** counters) {
    *counters = &g_globals_score;
    return state->Initialize();
}
#pragma code_seg()
