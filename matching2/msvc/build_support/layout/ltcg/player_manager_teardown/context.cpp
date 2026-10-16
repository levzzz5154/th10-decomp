// Compiler context only; never selected as recovered game code.
#include "../../../../src/game/card/card_destructor.cpp"
#include "../animation_lookup_anchors.cpp"
#define TH10_SCHEDULER_REMOVE_ONLY
#include "../manager_teardown_native/scheduler.cpp"

#pragma code_seg(".text$01b_context")
void __stdcall CardTeardownCompilerContext(Card2* manager) {
    delete manager;
}
#pragma code_seg()
