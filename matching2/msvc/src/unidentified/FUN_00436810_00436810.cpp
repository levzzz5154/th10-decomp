#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436810..0x00436816: FUN_00436810
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436810_00436810() {
    __asm {
    L_00436810:
        mov eax,dword ptr [eax+100h]
    L_00436816:
        ret
    }
}
