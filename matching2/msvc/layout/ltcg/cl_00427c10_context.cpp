// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00427c10.cpp"

#pragma code_seg(".text$03context")
int __stdcall ScaleContext_00427c10(IntPair_00427c10* out, const FloatPair_00427c10* in,
                                    int count) {
    for (int i = 0; i < count; ++i)
        ScaleToHundredths_00427c10(out++, in++);
    return 0;
}
#pragma code_seg()
