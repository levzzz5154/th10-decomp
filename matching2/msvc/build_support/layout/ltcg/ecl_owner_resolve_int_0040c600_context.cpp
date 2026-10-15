// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/unassigned_0040c600.cpp"

#pragma code_seg(".text$zzcontext")
int __stdcall Ctx(EclOwner_0040c600** p, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += *p[i]->ResolveIntDestination(i);
    return r;
}
#pragma code_seg()
