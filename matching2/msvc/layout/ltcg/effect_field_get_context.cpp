// Compiler context only; never selected as recovered game code.
#include "../../src/core/sprtanim/fun_0043eac0_0043eac0.cpp"

#pragma code_seg(".text$03context")
float __stdcall EffectFieldGetCompilerContext(EffectFieldStore_0043eac0* stores, int count,
                                              float index) {
    float total = 0.0f;
    for (int slot = 0; slot < count; ++slot)
        total += stores[slot].Get(index);
    return total;
}
#pragma code_seg()
