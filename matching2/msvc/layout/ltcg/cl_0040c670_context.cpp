// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0040c670.cpp"

#pragma code_seg(".text$03context")
int __stdcall ResolveContext_0040c670(EclSource_0040c670** sources, int* selectors, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += Resolve_0040c670(selectors[i], sources[i], i);
    }
    return total;
}
#pragma code_seg()
