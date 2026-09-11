// Compiler context only; never selected as recovered game code.
// The caller exists to establish the internal register convention of
// Entity_Initialize_0040d830: the record pointer stays live in ESI across both
// calls, the opaque first argument stays in ECX and the script context sits on
// the stack.
#include "../../src/game/fun_0040d830_0040d830.cpp"

#pragma code_seg(".text$03context")
int __stdcall EntityInitializeCompilerContext(BulletRecord_0040d830** records,
                                              int count, void* context) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        BulletRecord_0040d830* record = records[index];
        total += (int)Entity_Initialize_0040d830(record, context);
    }
    return total;
}
#pragma code_seg()
