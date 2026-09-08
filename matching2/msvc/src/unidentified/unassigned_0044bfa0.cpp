#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044BFA0..0x0044BFE9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044bfa0() {
    __asm {
    L_0044bfa0:
        mov edx,dword ptr [esi+4]
    L_0044bfa3:
        mov ecx,dword ptr [esi+0Ch]
    L_0044bfa6:
        mov dword ptr [esi],edx
    L_0044bfa8:
        fld dword ptr [ecx]
    L_0044bfaa:
        fcomp dword ptr [data_00470b68]
    L_0044bfb0:
        fnstsw ax
    L_0044bfb2:
        test ah,41h
    L_0044bfb5:
        jne short L_0044bfd9
    L_0044bfb7:
        fld dword ptr [ecx]
    L_0044bfb9:
        fcomp dword ptr [data_00470b64]
    L_0044bfbf:
        fnstsw ax
    L_0044bfc1:
        test ah,5
    L_0044bfc4:
        jp short L_0044bfd9
    L_0044bfc6:
        fld dword ptr [esi+8]
    L_0044bfc9:
        inc edx
    L_0044bfca:
        fadd dword ptr [data_00470afc]
    L_0044bfd0:
        mov dword ptr [esi+4],edx
    L_0044bfd3:
        mov eax,edx
    L_0044bfd5:
        fstp dword ptr [esi+8]
    L_0044bfd8:
        ret
    L_0044bfd9:
        fld dword ptr [ecx]
    L_0044bfdb:
        fadd dword ptr [esi+8]
    L_0044bfde:
        fst dword ptr [esi+8]
    L_0044bfe1:
        call asm_FUN_00463b2c_00463b2c
    L_0044bfe6:
        mov dword ptr [esi+4],eax
    L_0044bfe9:
        ret
    }
}
