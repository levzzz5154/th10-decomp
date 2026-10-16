// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_444cb0.cpp"

#pragma code_seg(".text$03context")
int __stdcall DestinationCopyCompilerContext(
    DestinationCopy** destinations,
    DestinationCopySource** sources,
    int count) {
    while (count--) {
        (*destinations)->Copy(*sources, count);
        ++destinations;
        ++sources;
    }
    return 0;
}
#pragma code_seg()
