#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409F80..0x00409F83: FUN_00409f80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409f80_00409f80() {
    __asm {
    L_00409f80:
        mov eax,dword ptr [eax+54h]
    L_00409f83:
        ret
    }
}
