#define TH10_ENDING_TEXT_LAYOUT_ONLY
#define TH10_ENDING_TEXT_WORKER_SECTION ".text$88worker"
#define TH10_ENDING_TEXT_CONSTRUCTOR_SECTION ".text$05ctor"
#include "../../src/game/ending_text_constructor_0040ba90.cpp"
#include "../../src/game/message_manager_initialize_0040b560.cpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall MessageManagerContext(MessageManager* state) { return state->Initialize(); }
#pragma code_seg()
