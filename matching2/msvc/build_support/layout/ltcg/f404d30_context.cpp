// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN_00404d30_00404d30.cpp"

#pragma code_seg(".text$03context")
int __stdcall f404d30CompilerContext(TrajectoryState** states, int count) {
    for (int index = 0; index < count; ++index) {
        states[index]->ResetStep();
        states[index]->ResetStep();
    }
    return 0;
}
#pragma code_seg()
