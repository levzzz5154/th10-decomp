#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00415E30..0x00415E8C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00415e30() {
    __asm {
    L_00415e30:
        push esi
    L_00415e31:
        call asm_FUN_00415e90_00415e90
    L_00415e36:
        test eax,eax
    L_00415e38:
        je short L_00415e40
    L_00415e3a:
        mov eax,1
    L_00415e3f:
        ret
    L_00415e40:
        mov edx,dword ptr [esi+8]
    L_00415e43:
        mov ecx,dword ptr [esi+10h]
    L_00415e46:
        mov dword ptr [esi+4],edx
    L_00415e49:
        fld dword ptr [ecx]
    L_00415e4b:
        fcomp dword ptr [data_00470b68]
    L_00415e51:
        fnstsw ax
    L_00415e53:
        test ah,41h
    L_00415e56:
        jne short L_00415e7a
    L_00415e58:
        fld dword ptr [ecx]
    L_00415e5a:
        fcomp dword ptr [data_00470b64]
    L_00415e60:
        fnstsw ax
    L_00415e62:
        test ah,5
    L_00415e65:
        jp short L_00415e7a
    L_00415e67:
        fld dword ptr [esi+0Ch]
    L_00415e6a:
        inc edx
    L_00415e6b:
        fadd dword ptr [data_00470afc]
    L_00415e71:
        mov dword ptr [esi+8],edx
    L_00415e74:
        xor eax,eax
    L_00415e76:
        fstp dword ptr [esi+0Ch]
    L_00415e79:
        ret
    L_00415e7a:
        fld dword ptr [esi+0Ch]
    L_00415e7d:
        fadd dword ptr [ecx]
    L_00415e7f:
        fst dword ptr [esi+0Ch]
    L_00415e82:
        call asm_FUN_00463b2c_00463b2c
    L_00415e87:
        mov dword ptr [esi+8],eax
    L_00415e8a:
        xor eax,eax
    L_00415e8c:
        ret
    }
}
