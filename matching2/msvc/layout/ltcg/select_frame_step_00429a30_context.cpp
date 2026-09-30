// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/unassigned_00429a30.cpp"

#pragma code_seg(".text$zzcontext")
int __stdcall Ctx(Entity_00429a30** p, int n) {
    int total = 0;
    for (int i = 0; i < n; ++i) total += p[i]->SelectFrameStep();
    return total;
}
#pragma code_seg()
