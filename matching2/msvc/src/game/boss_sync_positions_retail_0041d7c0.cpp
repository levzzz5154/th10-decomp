#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040E5F0..0x0040E691: BossUi_ReleaseIndicatorsRetail
// Naked body preserves the retail register/stack ABI.

// 0x0041D7C0..0x0041D86C: Boss_SyncOverlayPositionsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Boss_SyncPositionsRetail_0041d7c0() {
    __asm {
    L_0041d7c0:
        push esi
    L_0041d7c1:
        mov esi,ecx
    L_0041d7c3:
        fld dword ptr [esi+24h]
    L_0041d7c6:
        push edi
    L_0041d7c7:
        fadd dword ptr [data_00470b4c]
    L_0041d7cd:
        push 3FC90FDBh
    L_0041d7d2:
        lea edi,[esi+600h]
    L_0041d7d8:
        fstp dword ptr [esi+934h]
    L_0041d7de:
        fld dword ptr [esi+28h]
    L_0041d7e1:
        fadd dword ptr [data_00470b48]
    L_0041d7e7:
        fstp dword ptr [esi+938h]
    L_0041d7ed:
        mov eax,dword ptr [esi+2Ch]
    L_0041d7f0:
        mov dword ptr [esi+93Ch],eax
    L_0041d7f6:
        mov ecx,dword ptr [esi+3Ch]
    L_0041d7f9:
        push ecx
    L_0041d7fa:
        call asm_Angle_NormalizeSum_0044bc10
    L_0041d7ff:
        fstp dword ptr [edi+2Ch]
    L_0041d802:
        mov eax,dword ptr [edi+35Ch]
    L_0041d808:
        mov ecx,dword ptr [data_00491c10]
    L_0041d80e:
        or eax,4
    L_0041d811:
        mov dword ptr [edi+35Ch],eax
    L_0041d817:
        mov eax,edi
    L_0041d819:
        call asm_FUN_004451c0_004451c0
    L_0041d81e:
        fld dword ptr [data_00470b04]
    L_0041d824:
        fld dword ptr [esi+4Ch]
    L_0041d827:
        fucompp
    L_0041d829:
        fnstsw ax
    L_0041d82b:
        test ah,44h
    L_0041d82e:
        jp short L_0041d868
    L_0041d830:
        fld dword ptr [esi+24h]
    L_0041d833:
        mov ecx,dword ptr [data_00491c10]
    L_0041d839:
        fadd dword ptr [data_00470b4c]
    L_0041d83f:
        lea eax,[esi+9ACh]
    L_0041d845:
        fstp dword ptr [esi+0CE0h]
    L_0041d84b:
        fld dword ptr [esi+28h]
    L_0041d84e:
        fadd dword ptr [data_00470b48]
    L_0041d854:
        fstp dword ptr [esi+0CE4h]
    L_0041d85a:
        mov edx,dword ptr [esi+2Ch]
    L_0041d85d:
        mov dword ptr [esi+0CE8h],edx
    L_0041d863:
        call asm_FUN_004451c0_004451c0
    L_0041d868:
        pop edi
    L_0041d869:
        xor eax,eax
    L_0041d86b:
        pop esi
    L_0041d86c:
        ret
    }
}
