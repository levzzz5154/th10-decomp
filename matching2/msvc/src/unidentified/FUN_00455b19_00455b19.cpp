#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455B19..0x00455BF2: FUN_00455b19
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00455b19_00455b19() {
    __asm {
    L_00455b19:
        push ecx
    L_00455b1a:
        mov eax,dword ptr [data_0047334c]
    L_00455b1f:
        push edi
    L_00455b20:
        xor edi,edi
    L_00455b22:
        inc edi
    L_00455b23:
        test eax,eax
    L_00455b25:
        mov dword ptr [esp+4],edi
    L_00455b29:
        jne short L_00455b43
    L_00455b2b:
        push 351h
    L_00455b30:
        call asm_malloc_00452706
    L_00455b35:
        test eax,eax
    L_00455b37:
        pop ecx
    L_00455b38:
        mov dword ptr [data_0047334c],eax
    L_00455b3d:
        je asm_target_00455bf0
    L_00455b43:
        push ebx
    L_00455b44:
        push ebp
    L_00455b45:
        push esi
    L_00455b46:
        mov byte ptr [eax],0
    L_00455b49:
        push dword ptr [data_00473358]
    L_00455b4f:
        mov ebp,46AA00h
    L_00455b54:
        push ebp
    L_00455b55:
        push dword ptr [data_00473354]
    L_00455b5b:
        push 3
    L_00455b5d:
        push dword ptr [data_0047334c]
    L_00455b63:
        call asm_strcats_00455990
    L_00455b68:
        add esp,14h
    L_00455b6b:
        push 0Ch
    L_00455b6d:
        pop esi
    L_00455b6e:
        mov ebx,473358h
    L_00455b73:
        push 46A9FCh
    L_00455b78:
        push dword ptr [data_0047334c]
    L_00455b7e:
        call asm_FUN_0045bd90_0045bd90
    L_00455b83:
        push dword ptr [esi+473358h]
    L_00455b89:
        push dword ptr [ebx]
    L_00455b8b:
        call asm_strcmp_0045bf30
    L_00455b90:
        add esp,10h
    L_00455b93:
        test eax,eax
    L_00455b95:
        je short L_00455b9c
    L_00455b97:
        and dword ptr [esp+10h],0
    L_00455b9c:
        inc edi
    L_00455b9d:
        lea esi,[edi+edi*2]
    L_00455ba0:
        shl esi,2
    L_00455ba3:
        lea ebx,[esi+47334Ch]
    L_00455ba9:
        push dword ptr [ebx]
    L_00455bab:
        push ebp
    L_00455bac:
        push dword ptr [esi+473348h]
    L_00455bb2:
        push 3
    L_00455bb4:
        push dword ptr [data_0047334c]
    L_00455bba:
        call asm_strcats_00455990
    L_00455bbf:
        add esp,14h
    L_00455bc2:
        cmp edi,5
    L_00455bc5:
        jl short L_00455b73
    L_00455bc7:
        cmp dword ptr [esp+10h],0
    L_00455bcc:
        pop esi
    L_00455bcd:
        pop ebp
    L_00455bce:
        pop ebx
    L_00455bcf:
        jne short L_00455bd8
    L_00455bd1:
        mov eax,dword ptr [data_0047334c]
    L_00455bd6:
        jmp short L_00455bf0
    L_00455bd8:
        push dword ptr [data_0047334c]
    L_00455bde:
        call asm_free_00452422
    L_00455be3:
        and dword ptr [data_0047334c],0
    L_00455bea:
        mov eax,dword ptr [data_00473364]
    L_00455bef:
        pop ecx
    L_00455bf0:
        pop edi
    L_00455bf1:
        pop ecx
    L_00455bf2:
        ret
    }
}
