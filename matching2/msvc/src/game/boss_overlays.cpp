#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040E5F0..0x0040E691: BossUi_ReleaseIndicatorsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BossUi_ReleaseIndicatorsRetail_0040e5f0() {
    __asm {
    L_0040e5f0:
        push ebx
    L_0040e5f1:
        push ebp
    L_0040e5f2:
        mov ebp,dword ptr [esp+0Ch]
    L_0040e5f6:
        mov ebx,dword ptr [ebp+2444h]
    L_0040e5fc:
        test ebx,ebx
    L_0040e5fe:
        push esi
    L_0040e5ff:
        push edi
    L_0040e600:
        jl short L_0040e613
    L_0040e602:
        mov eax,dword ptr [ebp+1068h]
    L_0040e608:
        push eax
    L_0040e609:
        mov esi,492590h
    L_0040e60e:
        call asm_FUN_0043dd10_0043dd10
    L_0040e613:
        mov eax,dword ptr [ebp+2448h]
    L_0040e619:
        test eax,eax
    L_0040e61b:
        jl short L_0040e63e
    L_0040e61d:
        mov edx,dword ptr [ebp+244Ch]
    L_0040e623:
        push eax
    L_0040e624:
        mov eax,dword ptr [data_00477704]
    L_0040e629:
        lea ecx,[esp+18h]
    L_0040e62d:
        push ecx
    L_0040e62e:
        mov ecx,dword ptr [eax+edx*4+30h]
    L_0040e632:
        lea edi,[ebp+1068h]
    L_0040e638:
        push ecx
    L_0040e639:
        call asm_PlayerAnimation_Create_00448db0
    L_0040e63e:
        mov eax,dword ptr [ebp+2408h]
    L_0040e644:
        lea esi,[ebp+1068h]
    L_0040e64a:
        add ebp,2408h
    L_0040e650:
        test eax,eax
    L_0040e652:
        jle short L_0040e66d
    L_0040e654:
        push 400CCCCDh
    L_0040e659:
        push 0BFC90FDBh
    L_0040e65e:
        push 0FFFFFFFFh
    L_0040e660:
        push eax
    L_0040e661:
        mov eax,dword ptr [data_00477818]
    L_0040e666:
        mov ecx,esi
    L_0040e668:
        call asm_FUN_0041bb00_0041bb00
    L_0040e66d:
        push ebp
    L_0040e66e:
        call asm_FUN_0040c9d0_0040c9d0
    L_0040e673:
        push 0Ah
    L_0040e675:
        mov edi,474C40h
    L_0040e67a:
        mov dword ptr [ebp],0
    L_0040e681:
        call asm_FUN_00412ff0_00412ff0
    L_0040e686:
        pop edi
    L_0040e687:
        pop esi
    L_0040e688:
        pop ebp
    L_0040e689:
        mov eax,1
    L_0040e68e:
        pop ebx
    L_0040e68f:
        ret 4
    }
}

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
