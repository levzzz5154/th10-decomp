// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0040d510_0040d510.cpp"
#pragma code_seg(".text$03context")
int __stdcall SetContext_0040d510(ObjectAccessor_0040d510** items, int count) {
    while (count--) {
        SetFlags_0040d510(*items++);
    }
    return 0;
}
#pragma code_seg()
