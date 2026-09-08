#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A245..0x0045A25B: _abort
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_abort_0045a245() {
    __asm {
    L_0045a245:
        push 0Ah
    L_0045a247:
        call asm_FUN_00458efd_00458efd
    L_0045a24c:
        push 16h
    L_0045a24e:
        call asm_raise_00460028
    L_0045a253:
        pop ecx
    L_0045a254:
        pop ecx
    L_0045a255:
        push 3
    L_0045a257:
        call asm_exit_004576fd
    }
}
