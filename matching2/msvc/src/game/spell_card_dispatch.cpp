#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED: closest_byte_count=20/356; first_diff=extent (readable
// candidate emitted 341 bytes, retail extent 356); residual_class=private
// EBX manager ABI and register-sensitive score-gauge call; variants_tested=
// raw typed SpellRecord/SpellSlot model from live Ghidra plus legacy schema,
// standalone MSVC 13.10 probe; next_lever=native-LTCG cluster with the real
// 0x00417870 caller that establishes EBX and the production spell layout.

// 0x0042A6A0..0x0042A803: FUN_0042a6a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a6a0_0042a6a0() {
    __asm {
    L_0042a6a0:
        push ecx
    L_0042a6a1:
        mov eax,dword ptr [ebx+10h]
    L_0042a6a4:
        test eax,eax
    L_0042a6a6:
        jne short L_0042a71e
    L_0042a6a8:
        push edi
    L_0042a6a9:
        push 1C4h
    L_0042a6ae:
        call asm_operator_new_00452493
    L_0042a6b3:
        mov edx,eax
    L_0042a6b5:
        add esp,4
    L_0042a6b8:
        xor eax,eax
    L_0042a6ba:
        test edx,edx
    L_0042a6bc:
        je short L_0042a6c9
    L_0042a6be:
        mov ecx,71h
    L_0042a6c3:
        mov edi,edx
    L_0042a6c5:
        rep stosd
    L_0042a6c7:
        mov eax,edx
    L_0042a6c9:
        mov ecx,dword ptr [data_00474c7c]
    L_0042a6cf:
        mov dword ptr [ebx+ecx*4+1Ch],eax
    L_0042a6d3:
        mov edx,dword ptr [data_00474c7c]
    L_0042a6d9:
        mov eax,dword ptr [ebx+edx*4+1Ch]
    L_0042a6dd:
        mov cx,word ptr [data_004918b0]
    L_0042a6e4:
        mov word ptr [eax+2],cx
    L_0042a6e8:
        mov dx,word ptr [data_00474c7c]
    L_0042a6ef:
        mov dword ptr [data_004918b4],0
    L_0042a6f9:
        mov ecx,dword ptr [eax+1C0h]
    L_0042a6ff:
        mov word ptr [eax],dx
    L_0042a702:
        mov edi,dword ptr [data_00491fc4]
    L_0042a708:
        mov edx,dword ptr [eax+1C0h]
    L_0042a70e:
        xor ecx,edi
    L_0042a710:
        and ecx,1
    L_0042a713:
        xor edx,ecx
    L_0042a715:
        mov dword ptr [eax+1C0h],edx
    L_0042a71b:
        pop edi
    L_0042a71c:
        pop ecx
    L_0042a71d:
        ret
    L_0042a71e:
        cmp eax,1
    L_0042a721:
        jne asm_target_0042a802
    L_0042a727:
        mov eax,dword ptr [data_00474c7c]
    L_0042a72c:
        lea edx,[eax+eax*8]
    L_0042a72f:
        mov ecx,dword ptr [ebx+edx*4+0A0h]
    L_0042a736:
        lea eax,[ebx+edx*4+0A0h]
    L_0042a73d:
        mov edx,dword ptr [eax+8]
    L_0042a740:
        mov dword ptr [eax+4],ecx
    L_0042a743:
        mov dword ptr [eax+0Ch],edx
    L_0042a746:
        mov dword ptr [eax+14h],0
    L_0042a74d:
        push esi
    L_0042a74e:
        mov esi,dword ptr [eax+10h]
    L_0042a751:
        mov ax,word ptr [esi+2]
    L_0042a755:
        mov word ptr [data_004918b0],ax
    L_0042a75b:
        mov dword ptr [data_004918b4],0
    L_0042a765:
        mov ecx,dword ptr [esi+0Ch]
    L_0042a768:
        mov dword ptr [data_00474c44],ecx
    L_0042a76e:
        mov dx,word ptr [esi+10h]
    L_0042a772:
        mov word ptr [data_00474c48],dx
    L_0042a779:
        mov eax,dword ptr [esi+14h]
    L_0042a77c:
        lea eax,[eax+eax*4]
    L_0042a77f:
        shl eax,1
    L_0042a781:
        push eax
    L_0042a782:
        mov ecx,474C40h
    L_0042a787:
        call asm_ScoreGauge_SetTargetTenthAndDisableTimer_00418b80
    L_0042a78c:
        test byte ptr [data_00474c64],1
    L_0042a793:
        mov eax,dword ptr [esi+18h]
    L_0042a796:
        mov dword ptr [esp+4],eax
    L_0042a79a:
        jne short L_0042a7b5
    L_0042a79c:
        mov ecx,dword ptr [data_00474c64]
    L_0042a7a2:
        or ecx,1
    L_0042a7a5:
        mov dword ptr [data_00474c60],476F78h
    L_0042a7af:
        mov dword ptr [data_00474c64],ecx
    L_0042a7b5:
        fild dword ptr [esp+4]
    L_0042a7b9:
        mov dword ptr [data_00474c58],eax
    L_0042a7be:
        dec eax
    L_0042a7bf:
        mov dword ptr [data_00474c54],eax
    L_0042a7c4:
        fstp dword ptr [data_00474c5c]
    L_0042a7ca:
        mov ecx,dword ptr [esi+1Ch]
    L_0042a7cd:
        mov dword ptr [data_00474c70],ecx
    L_0042a7d3:
        mov edx,dword ptr [esi+20h]
    L_0042a7d6:
        mov dword ptr [data_00474c98],edx
    L_0042a7dc:
        mov eax,dword ptr [esi+1B4h]
    L_0042a7e2:
        mov dword ptr [data_00474c90],eax
    L_0042a7e7:
        mov eax,dword ptr [data_00474c7c]
    L_0042a7ec:
        lea ecx,[eax+eax*8]
    L_0042a7ef:
        mov edx,dword ptr [ebx+ecx*4+0B0h]
    L_0042a7f6:
        mov eax,dword ptr [edx+1B8h]
    L_0042a7fc:
        mov dword ptr [data_00474c9c],eax
    L_0042a801:
        pop esi
    L_0042a802:
        pop ecx
    L_0042a803:
        ret
    }
}
