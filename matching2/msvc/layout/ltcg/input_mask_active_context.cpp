// Compiler context only; never selected as recovered game code.
#include "../../src/game/eclview/input_mask_active_0040ace0.cpp"

#pragma code_seg(".text$03context")
int __stdcall InputMaskActiveCompilerContext(unsigned short* masks, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        total += data_00474e30.InputMaskActive(masks[index]);
    }
    return total;
}
#pragma code_seg()
