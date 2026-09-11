// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_00405150_00405150.cpp"

#pragma code_seg(".text$03context")
int __stdcall f405150CompilerContext(RuntimeRecord** records, int count, int value) {
    for (int index = 0; index < count; ++index)
        StoreValue48(records[index], value);
    return 0;
}
#pragma code_seg()
