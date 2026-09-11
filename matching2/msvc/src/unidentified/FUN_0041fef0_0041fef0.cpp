#include "asm_symbols.hpp"

// 0x0041FEF0..0x0041FEF6: FUN_0041fef0
// Scheduler callback: the context arrives in ECX, and the worker at 0x0041FDD0
// takes it as its only stack argument, so the forward is a single push/ret pair.
typedef void (__stdcall* FUN_0041fdd0_fn)(void*);

void __fastcall FUN_0041fef0_0041fef0(void* self) {
    ((FUN_0041fdd0_fn)asm_FUN_0041fdd0_0041fdd0)(self);
}
