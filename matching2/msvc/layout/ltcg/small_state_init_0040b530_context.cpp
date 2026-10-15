// Synthetic compiler context; never selected as game code.
#include "../../src/unreferenced/unassigned_0040b530.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall SmallStateInitCompilerContext(
        SmallState_0040B530** states, int count) {
    for (int index = 0; index < count; ++index)
        states[index]->Initialize();
}
#pragma code_seg()
