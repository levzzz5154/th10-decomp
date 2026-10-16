// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_427c10.cpp"

#pragma code_seg(".text$03context")
int __stdcall ScaleContext_00427c10(IntPair* out, const FloatPair* in,
                                    int count) {
    for (int i = 0; i < count; ++i)
        ScaleToHundredths(out++, in++);
    return 0;
}
#pragma code_seg()
