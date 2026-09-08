#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E500..0x0043E51E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043e500() {
    __asm {
    L_0043e500:
        fld dword ptr [esp+4]
    L_0043e504:
        mov dword ptr [esi+1Ch],1
    L_0043e50b:
        fmul dword ptr [data_00470b1c]
    L_0043e511:
        call asm_FUN_00463b2c_00463b2c
    L_0043e516:
        mov dword ptr [esi+14h],eax
    L_0043e519:
        mov dword ptr [esi+18h],eax
    L_0043e51c:
        ret 4
    }
}
