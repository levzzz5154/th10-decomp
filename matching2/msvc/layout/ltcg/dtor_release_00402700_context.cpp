// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00402700.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DtorReleaseContext_00402700(Destroyable_00402700** items, int count) {
    while (count--) {
        Destroyable_00402700_Release(*items++);
    }
    return 0;
}
#pragma code_seg()
