// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00402020.cpp"

#pragma code_seg(".text$03context")
int __stdcall ReleaseContext_00402020(Holder_00402020** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->ReleaseOwned();
    }
    return 0;
}
#pragma code_seg()
