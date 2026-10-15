// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention: size in EAX, the centred receiver in ECX, the
// minimum in ESI and the maximum in EDX.
#include "../../../src/unreferenced/unassigned_004285f0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall BoundsFromCenterCompilerContext(
        Vector2** centers, Vector2** sizes, Vector2* min, Vector2* max, int count) {
    while (count--) {
        (*centers++)->GetBounds(*sizes++, min, max);
    }
    return 0;
}
#pragma code_seg()
