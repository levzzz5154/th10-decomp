#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004598DE..0x00459945: __local_unwind2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_local_unwind2_004598de() {
    __asm {
    L_004598de:
        push ebx
    L_004598df:
        push esi
    L_004598e0:
        push edi
    L_004598e1:
        mov eax,dword ptr [esp+10h]
    L_004598e5:
        push eax
    L_004598e6:
        push 0FFFFFFFEh
    L_004598e8:
        push 4598BCh
    L_004598ed:
        push dword ptr fs:[0]
    L_004598f4:
        mov dword ptr fs:[0],esp
    L_004598fb:
        mov eax,dword ptr [esp+20h]
    L_004598ff:
        mov ebx,dword ptr [eax+8]
    L_00459902:
        mov esi,dword ptr [eax+0Ch]
    L_00459905:
        cmp esi,0FFFFFFFFh
    L_00459908:
        je short L_00459938
    L_0045990a:
        cmp esi,dword ptr [esp+24h]
    L_0045990e:
        je short L_00459938
    L_00459910:
        lea esi,[esi+esi*2]
    L_00459913:
        mov ecx,dword ptr [ebx+esi*4]
    L_00459916:
        mov dword ptr [esp+8],ecx
    L_0045991a:
        mov dword ptr [eax+0Ch],ecx
    L_0045991d:
        cmp dword ptr [ebx+esi*4+4],0
    L_00459922:
        jne short L_00459936
    L_00459924:
        push 101h
    L_00459929:
        mov eax,dword ptr [ebx+esi*4+8]
    L_0045992d:
        call asm_FUN_00459972_00459972
    L_00459932:
        call dword ptr [ebx+esi*4+8]
    L_00459936:
        jmp short L_004598fb
    L_00459938:
        pop dword ptr fs:[0]
    L_0045993f:
        add esp,0Ch
    L_00459942:
        pop edi
    L_00459943:
        pop esi
    L_00459944:
        pop ebx
    L_00459945:
        ret
    }
}
