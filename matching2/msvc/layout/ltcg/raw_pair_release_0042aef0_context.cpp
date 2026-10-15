// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0042aef0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall RawPairReleaseContext_0042aef0(RawPair_0042aef0** items, int count) {
    while (count--) {
        RawPair_0042aef0_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
