#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436850..0x00436856: FUN_00436850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436850_00436850() {
    __asm {
    L_00436850:
        mov eax,dword ptr [eax+108h]
    L_00436856:
        ret
    }
}
