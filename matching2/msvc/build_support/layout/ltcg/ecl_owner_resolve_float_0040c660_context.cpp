// Compiler context only; its bytes are not recovered game code.
#include "../../../src/unreferenced/FUN_0040c660_0040c660.cpp"
#include "../../../src/script/sptcmd/ecl_resolve_float_destination_00450070.cpp"

#pragma code_seg(".text$zzcontext")
float __stdcall Ctx(EclOwner_0040c660** p, int n) {
    float r = 0;
    for (int i = 0; i < n; ++i) r += *p[i]->ResolveFloatDestination(i);
    return r;
}
#pragma code_seg()
