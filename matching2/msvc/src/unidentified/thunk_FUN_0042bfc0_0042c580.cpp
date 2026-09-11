#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C580..0x0042C584: thunk_FUN_0042bfc0
// Incremental-link jump thunk: every caller that takes this address (the
// scheduler callback table) reaches the shared body at 0x0042BFC0 through a
// single tail jump. The compiled C++ call is a tail call, so MSVC emits the
// five-byte jmp with the same rel32 field the retail image has.
extern "C" void __cdecl thunk_FUN_0042bfc0_0042c580() {
    asm_FUN_0042bfc0_0042bfc0();
}
