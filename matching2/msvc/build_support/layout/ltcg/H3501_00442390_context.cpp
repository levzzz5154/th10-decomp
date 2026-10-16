// Synthetic compiler context only; it is not recovered game code.
#include "../../../src/unreferenced/FUN.cpp_442390.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall CopySourceCompilerContext_00442390(
        CopySource2** sources,
        CopyDestination2** destinations,
        int count) {
    int total = 0;
    while (count-- > 0) {
        (*sources++)->CopyTo(*destinations++);
        ++total;
    }
    return total;
}
#pragma code_seg()
