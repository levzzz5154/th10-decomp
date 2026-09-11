// Compiler context only; never selected as recovered game code.
#include "../../src/game/set_input_mode_0040ac90.cpp"

extern "C" InputState data_00491c28;   // 0x00491C28, the object retail callers pass in EAX

#pragma code_seg(".text$03context")
void __stdcall SetInputModeCompilerContext(int count) {
    for (int index = 0; index < count; ++index) {
        SetInputMode(&data_00491c28, 3);
    }
}
#pragma code_seg()
