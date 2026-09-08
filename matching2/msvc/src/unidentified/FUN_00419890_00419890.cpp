#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00419890..0x00419895: FUN_00419890
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00419890_00419890() {
    __asm {
    L_00419890:
        mov eax,1
    L_00419895:
        ret
    }
}
