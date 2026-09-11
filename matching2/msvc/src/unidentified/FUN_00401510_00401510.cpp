#include "asm_symbols.hpp"

// 0x00401510..0x00401516: FUN_00401510
// Forwards the caller's object to the worker at 0x00401760, which takes it as
// its only stack argument.
typedef void (__stdcall* FUN_00401760_fn)(void*);

void __fastcall FUN_00401510(void* self) {
    ((FUN_00401760_fn)asm_FUN_00401760_00401760)(self);
}
