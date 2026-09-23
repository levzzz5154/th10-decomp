#include "asm_symbols.hpp"

// 0x0045A245..0x0045A25B: _abort
extern "C" __declspec(noreturn) void __cdecl asm_abort_0045a245() {
    asm_FUN_00458efd_00458efd(10);
    (void)asm_raise_00460028(0x16);
    asm_exit_004576fd(3);
    for (;;) {
    }
}
