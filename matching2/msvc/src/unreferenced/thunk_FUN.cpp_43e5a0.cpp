#include "../../build_support/include/asm_encoding.hpp"
#include "../../build_support/include/asm_symbols.hpp"

// 0x00405BD0..0x00405BD4: thunk_FUN_0043e5a0
// The retail body is a bare forwarder: it shares the argument list of the
// animation routine it jumps to, so the compiler emits the tail jump directly.
void __cdecl thunk_FUN_0043e5a0_00405bd0() {
    asm_AnimationObject_ConfigureFromResource_0043e5a0();
}
