#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441E50..0x00441E87: RandomVector_StoreRoundedScalar
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RandomVector_StoreRoundedScalar_00441e50() {
    __asm {
    L_00441e50:
        fild dword ptr [edi+4]
    L_00441e53:
        push ebx
    L_00441e54:
        push ebp
    L_00441e55:
        fmul dword ptr [esp+0Ch]
    L_00441e59:
        call asm_FUN_00463b2c_00463b2c
    L_00441e5e:
        fild dword ptr [edi+8]
    L_00441e61:
        mov ebx,eax
    L_00441e63:
        fmul dword ptr [esp+0Ch]
    L_00441e67:
        call asm_FUN_00463b2c_00463b2c
    L_00441e6c:
        fild dword ptr [edi]
    L_00441e6e:
        mov ebp,eax
    L_00441e70:
        fmul dword ptr [esp+0Ch]
    L_00441e74:
        call asm_FUN_00463b2c_00463b2c
    L_00441e79:
        mov dword ptr [esi+8],ebp
    L_00441e7c:
        pop ebp
    L_00441e7d:
        mov dword ptr [esi],eax
    L_00441e7f:
        mov dword ptr [esi+4],ebx
    L_00441e82:
        mov eax,esi
    L_00441e84:
        pop ebx
    L_00441e85:
        ret 4
    }
}
