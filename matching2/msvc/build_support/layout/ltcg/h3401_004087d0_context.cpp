// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_004087d0_004087d0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __cdecl M3401Context_004087d0(
        H3401ShortField** objects, const unsigned short* values, int count) {
    while (count--)
        (*objects++)->Set(*values++);
    return 0;
}
#pragma code_seg()
