#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428B10..0x00428C19: FUN_00428b10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428b10_00428b10() {
    __asm {
    L_00428b10:
        push ecx
    L_00428b11:
        push esi
    L_00428b12:
        mov esi,edx
    L_00428b14:
        cmp dword ptr [esi+40h],2
    L_00428b18:
        je short L_00428b5c
    L_00428b1a:
        mov eax,dword ptr [esi+4Ch]
    L_00428b1d:
        test eax,eax
    L_00428b1f:
        je short L_00428b3b
    L_00428b21:
        mov ecx,dword ptr [eax+2480h]
    L_00428b27:
        test cl,11h
    L_00428b2a:
        jne short L_00428b34
    L_00428b2c:
        test ecx,0C0000h
    L_00428b32:
        je short L_00428b61
    L_00428b34:
        mov dword ptr [esi+4Ch],0
    L_00428b3b:
        fld dword ptr [esi+2Ch]
    L_00428b3e:
        fadd dword ptr [data_00470c18]
    L_00428b44:
        fcom dword ptr [data_00470b48]
    L_00428b4a:
        fnstsw ax
    L_00428b4c:
        test ah,41h
    L_00428b4f:
        jne short L_00428b59
    L_00428b51:
        fstp st(0)
    L_00428b53:
        fld dword ptr [data_00470b48]
    L_00428b59:
        fstp dword ptr [esi+2Ch]
    L_00428b5c:
        xor eax,eax
    L_00428b5e:
        pop esi
    L_00428b5f:
        pop ecx
    L_00428b60:
        ret
    L_00428b61:
        fld dword ptr [eax+106Ch]
    L_00428b67:
        mov ecx,dword ptr [esi+30h]
    L_00428b6a:
        fsub dword ptr [esi+18h]
    L_00428b6d:
        push ecx
    L_00428b6e:
        fld dword ptr [eax+1068h]
    L_00428b74:
        push ecx
    L_00428b75:
        fsub dword ptr [esi+14h]
    L_00428b78:
        fpatan
    L_00428b7a:
        fstp dword ptr [esp]
    L_00428b7d:
        call asm_FUN_00428ce0_00428ce0
    L_00428b82:
        fstp dword ptr [esp+4]
    L_00428b86:
        mov eax,dword ptr [esi+4]
    L_00428b89:
        fld dword ptr [esi+2Ch]
    L_00428b8c:
        cmp eax,78h
    L_00428b8f:
        jge short L_00428c0c
    L_00428b91:
        fld dword ptr [esp+4]
    L_00428b95:
        fabs
    L_00428b97:
        fcom dword ptr [data_00470c48]
    L_00428b9d:
        fnstsw ax
    L_00428b9f:
        test ah,1
    L_00428ba2:
        jne short L_00428bc3
    L_00428ba4:
        fstp st(0)
    L_00428ba6:
        fsub dword ptr [data_00470c44]
    L_00428bac:
        fcom dword ptr [data_00470c40]
    L_00428bb2:
        fnstsw ax
    L_00428bb4:
        test ah,5
    L_00428bb7:
        jp short L_00428beb
    L_00428bb9:
        fstp st(0)
    L_00428bbb:
        fld dword ptr [data_00470c40]
    L_00428bc1:
        jmp short L_00428beb
    L_00428bc3:
        fcomp dword ptr [data_00470c3c]
    L_00428bc9:
        fnstsw ax
    L_00428bcb:
        test ah,5
    L_00428bce:
        jp short L_00428beb
    L_00428bd0:
        fadd dword ptr [data_00470c18]
    L_00428bd6:
        fcom dword ptr [data_00470b48]
    L_00428bdc:
        fnstsw ax
    L_00428bde:
        test ah,41h
    L_00428be1:
        jne short L_00428beb
    L_00428be3:
        fstp st(0)
    L_00428be5:
        fld dword ptr [data_00470b48]
    L_00428beb:
        fld dword ptr [esp+4]
    L_00428bef:
        push ecx
    L_00428bf0:
        fmul dword ptr [data_00470c38]
    L_00428bf6:
        fadd dword ptr [esi+30h]
    L_00428bf9:
        fstp dword ptr [esp]
    L_00428bfc:
        call asm_Angle_Normalize_0044bc70
    L_00428c01:
        fstp dword ptr [esi+30h]
    L_00428c04:
        xor eax,eax
    L_00428c06:
        fstp dword ptr [esi+2Ch]
    L_00428c09:
        pop esi
    L_00428c0a:
        pop ecx
    L_00428c0b:
        ret
    L_00428c0c:
        fadd dword ptr [data_00470c38]
    L_00428c12:
        xor eax,eax
    L_00428c14:
        fstp dword ptr [esi+2Ch]
    L_00428c17:
        pop esi
    L_00428c18:
        pop ecx
    L_00428c19:
        ret
    }
}
