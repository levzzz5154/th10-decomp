#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409F60..0x00409F63: FUN_00409f60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409f60_00409f60() {
    __asm {
    L_00409f60:
        mov eax,dword ptr [eax+60h]
    L_00409f63:
        ret
    }
}
