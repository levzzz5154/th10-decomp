// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_004423a0_004423a0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall H3601_004423a0_Context(
        Source_004423a0** sources, Destination_004423a0** destinations,
        int count) {
    while (count--)
        (*sources++)->CopyTo(*destinations++);
    return 0;
}
#pragma code_seg()
