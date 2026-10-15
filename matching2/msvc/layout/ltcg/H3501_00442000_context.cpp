// Synthetic compiler context only; it is not recovered game code.
#include "../../src/unreferenced/FUN_00442000_00442000.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall CopySourceCompilerContext_00442000(
        CopySource_00442000** sources,
        CopyDestination_00442000** destinations,
        int count) {
    int total = 0;
    while (count-- > 0) {
        (*sources++)->CopyTo(*destinations++);
        ++total;
    }
    return total;
}
#pragma code_seg()
