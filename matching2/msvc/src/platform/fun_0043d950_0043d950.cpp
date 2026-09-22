#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A910..0x0043A9AB: FUN_0043a910
// Naked body preserves the retail register/stack ABI.

// BLOCKED (D3401): closest_byte_count=298/298; first_diff=none
// (authoritative MSVC 13.10 probe exact for the retained retail body).
// residual_class=private EAX index/ESI owner ABI, archive record stride and
// division scheduling, CreateEventA/CreateThread import placement, and the
// 0x0044CBF0 stream worker's native-LTCG callback context. variants_tested=
// live Ghidra decompile plus xrefs/callers/callees, dependency path analysis,
// and dataflow request; Ghidra reports no PCode for this private-ABI region.
// next_lever=construct the required cluster with caller 0x0043DECC, callee
// 0x0043D790, and 0x0044CBF0, then compile the readable body under native LTCG.
//
// 0x0043D950..0x0043DA79: FUN_0043d950
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d950_0043d950() {
    __asm {
    L_0043d950:
        push ebx
    L_0043d951:
        mov ebx,eax
    L_0043d953:
        mov eax,dword ptr [esi+610h]
    L_0043d959:
        test eax,eax
    L_0043d95b:
        push ebp
    L_0043d95c:
        push edi
    L_0043d95d:
        je asm_target_0043da67
    L_0043d963:
        mov al,byte ptr [data_00491d63]
    L_0043d968:
        test al,al
    L_0043d96a:
        jne short L_0043d975
    L_0043d96c:
        mov eax,0FFFFFFFFh
    L_0043d971:
        pop edi
    L_0043d972:
        pop ebp
    L_0043d973:
        pop ebx
    L_0043d974:
        ret
    L_0043d975:
        cmp dword ptr [esi],0
    L_0043d978:
        je asm_target_0043da67
    L_0043d97e:
        test byte ptr [data_00491d78],10h
    L_0043d985:
        jne short L_0043d99b
    L_0043d987:
        shl ebx,8
    L_0043d98a:
        lea ecx,[ebx+esi+4108h]
    L_0043d991:
        mov eax,esi
    L_0043d993:
        pop edi
    L_0043d994:
        pop ebp
    L_0043d995:
        pop ebx
    L_0043d996:
        jmp asm_Recovery_SelectArchiveEntry_0043d790
    L_0043d99b:
        mov eax,dword ptr [esi+ebx*4+1EC0h]
    L_0043d9a2:
        test eax,eax
    L_0043d9a4:
        je asm_target_0043da67
    L_0043d9aa:
        mov eax,dword ptr [esi+ebx*4+1E80h]
    L_0043d9b1:
        movzx ebp,word ptr [eax+2Ch]
    L_0043d9b5:
        mov edi,dword ptr [eax+24h]
    L_0043d9b8:
        imul edi,ebp
    L_0043d9bb:
        push 0
    L_0043d9bd:
        push 0
    L_0043d9bf:
        push 0
    L_0043d9c1:
        shl edi,2
    L_0043d9c4:
        push 0
    L_0043d9c6:
        shr edi,4
    L_0043d9c9:
        call dword ptr [data_00466120]
    L_0043d9cf:
        mov dword ptr [esi+520Ch],eax
    L_0043d9d5:
        mov ecx,dword ptr [data_00491c70]
    L_0043d9db:
        lea eax,[esi+614h]
    L_0043d9e1:
        push eax
    L_0043d9e2:
        push 0
    L_0043d9e4:
        push ecx
    L_0043d9e5:
        push 43E3A0h
    L_0043d9ea:
        push 0
    L_0043d9ec:
        push 0
    L_0043d9ee:
        call dword ptr [data_00466118]
    L_0043d9f4:
        mov edx,dword ptr [esi+520Ch]
    L_0043d9fa:
        push edx
    L_0043d9fb:
        mov dword ptr [esi+618h],eax
    L_0043da01:
        xor edx,edx
    L_0043da03:
        mov eax,edi
    L_0043da05:
        div ebp
    L_0043da07:
        mov ecx,dword ptr [data_0046a67c]
    L_0043da0d:
        sub edi,edx
    L_0043da0f:
        mov edx,dword ptr [data_0046a680]
    L_0043da15:
        push edi
    L_0043da16:
        push 10h
    L_0043da18:
        sub esp,10h
    L_0043da1b:
        mov eax,esp
    L_0043da1d:
        mov dword ptr [eax],ecx
    L_0043da1f:
        mov ecx,dword ptr [data_0046a684]
    L_0043da25:
        mov dword ptr [eax+4],edx
    L_0043da28:
        mov edx,dword ptr [data_0046a688]
    L_0043da2e:
        mov dword ptr [eax+8],ecx
    L_0043da31:
        mov ecx,dword ptr [esi+ebx*4+1F40h]
    L_0043da38:
        mov dword ptr [eax+0Ch],edx
    L_0043da3b:
        mov eax,dword ptr [esi+ebx*4+1E80h]
    L_0043da42:
        mov edx,dword ptr [esi+ebx*4+1F00h]
    L_0043da49:
        push eax
    L_0043da4a:
        mov eax,dword ptr [esi+610h]
    L_0043da50:
        push ecx
    L_0043da51:
        push edx
    L_0043da52:
        lea ecx,[esi+5208h]
    L_0043da58:
        push eax
    L_0043da59:
        mov edx,10100h
    L_0043da5e:
        call asm_FUN_0044cbf0_0044cbf0
    L_0043da63:
        test eax,eax
    L_0043da65:
        jge short L_0043da6e
    L_0043da67:
        or eax,0FFFFFFFFh
    L_0043da6a:
        pop edi
    L_0043da6b:
        pop ebp
    L_0043da6c:
        pop ebx
    L_0043da6d:
        ret
    L_0043da6e:
        pop edi
    L_0043da6f:
        pop ebp
    L_0043da70:
        mov dword ptr [esi+1F80h],ebx
    L_0043da76:
        xor eax,eax
    L_0043da78:
        pop ebx
    L_0043da79:
        ret
    }
}
