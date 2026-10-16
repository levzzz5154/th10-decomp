// Compiler context only; never selected as recovered game code.
#include "../../../src/game/eclview/set_input_mode.cpp"

extern "C" InputState g_application;   // 0x00491C28, the object retail callers pass in EAX

#pragma code_seg(".text$03context")
void __stdcall SetInputModeCompilerContext(int count) {
    for (int index = 0; index < count; ++index) {
        SetInputMode(&g_application, 3);
    }
}
#pragma code_seg()
