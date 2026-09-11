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

