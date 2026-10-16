// Compiler context only; never selected as recovered game code.
#include "../../../src/core/main/d3d_initialize.cpp"

#pragma code_seg(".text$0044b9b0_context")
// The link's entry: a caller for the whole-program link to see.
extern "C" int __stdcall RigEntry(void* instance, int show) {
    return D3DInitialize();
}
#pragma code_seg()
