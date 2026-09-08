#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041EA40..0x0041EAEC: FUN_0041ea40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ea40_0041ea40() {
    __asm {
    L_0041ea40:
        push esi
    L_0041ea41:
        mov esi,ecx
    L_0041ea43:
        fld dword ptr [esi+24h]
    L_0041ea46:
        push edi
    L_0041ea47:
        fadd dword ptr [data_00470b4c]
    L_0041ea4d:
        push 3FC90FDBh
    L_0041ea52:
        lea edi,[esi+61Ch]
    L_0041ea58:
        fstp dword ptr [esi+950h]
    L_0041ea5e:
        fld dword ptr [esi+28h]
    L_0041ea61:
        fadd dword ptr [data_00470b48]
    L_0041ea67:
        fstp dword ptr [esi+954h]
    L_0041ea6d:
        mov eax,dword ptr [esi+2Ch]
    L_0041ea70:
        mov dword ptr [esi+958h],eax
    L_0041ea76:
        mov ecx,dword ptr [esi+3Ch]
    L_0041ea79:
        push ecx
    L_0041ea7a:
        call asm_Angle_NormalizeSum_0044bc10
    L_0041ea7f:
        fstp dword ptr [edi+2Ch]
    L_0041ea82:
        mov eax,dword ptr [edi+35Ch]
    L_0041ea88:
        mov ecx,dword ptr [data_00491c10]
    L_0041ea8e:
        or eax,4
    L_0041ea91:
        mov dword ptr [edi+35Ch],eax
    L_0041ea97:
        mov eax,edi
    L_0041ea99:
        call asm_FUN_004451c0_004451c0
    L_0041ea9e:
        fld dword ptr [data_00470b04]
    L_0041eaa4:
        fld dword ptr [esi+4Ch]
    L_0041eaa7:
        fucompp
    L_0041eaa9:
        fnstsw ax
    L_0041eaab:
        test ah,44h
    L_0041eaae:
        jp short L_0041eae8
    L_0041eab0:
        fld dword ptr [esi+24h]
    L_0041eab3:
        mov ecx,dword ptr [data_00491c10]
    L_0041eab9:
        fadd dword ptr [data_00470b4c]
    L_0041eabf:
        lea eax,[esi+9C8h]
    L_0041eac5:
        fstp dword ptr [esi+0CFCh]
    L_0041eacb:
        fld dword ptr [esi+28h]
    L_0041eace:
        fadd dword ptr [data_00470b48]
    L_0041ead4:
        fstp dword ptr [esi+0D00h]
    L_0041eada:
        mov edx,dword ptr [esi+2Ch]
    L_0041eadd:
        mov dword ptr [esi+0D04h],edx
    L_0041eae3:
        call asm_FUN_004451c0_004451c0
    L_0041eae8:
        pop edi
    L_0041eae9:
        xor eax,eax
    L_0041eaeb:
        pop esi
    L_0041eaec:
        ret
    }
}
