#include "../../build_support/include/asm_encoding.hpp"
#include "../../build_support/include/asm_symbols.hpp"

// 0x00436A20..0x00436A24: thunk_FUN_00436a30
// The retail body is a bare forwarder: it shares the argument list of the
// flush routine it jumps to, so the compiler emits the tail jump directly.
void __cdecl thunk_FUN_00436a30_00436a20() {
    asm_FontCache_FlushRetail_00436a30();
}
