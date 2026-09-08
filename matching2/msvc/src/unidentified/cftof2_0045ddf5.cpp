#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DDF5..0x0045DE90: __cftof2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_cftof2_0045ddf5() {
    __asm {
    L_0045ddf5:
        push ebp
    L_0045ddf6:
        mov ebp,esp
    L_0045ddf8:
        push ebx
    L_0045ddf9:
        push esi
    L_0045ddfa:
        mov esi,eax
    L_0045ddfc:
        mov eax,dword ptr [esi+4]
    L_0045ddff:
        dec eax
    L_0045de00:
        cmp byte ptr [ebp+10h],0
    L_0045de04:
        push edi
    L_0045de05:
        je short L_0045de22
    L_0045de07:
        cmp eax,dword ptr [ebp+0Ch]
    L_0045de0a:
        jne short L_0045de22
    L_0045de0c:
        xor ecx,ecx
    L_0045de0e:
        cmp dword ptr [esi],2Dh
    L_0045de11:
        sete cl
    L_0045de14:
        add ecx,eax
    L_0045de16:
        add ecx,dword ptr [ebp+8]
    L_0045de19:
        mov eax,ecx
    L_0045de1b:
        mov byte ptr [eax],30h
    L_0045de1e:
        mov byte ptr [eax+1],0
    L_0045de22:
        cmp dword ptr [esi],2Dh
    L_0045de25:
        mov ebx,dword ptr [ebp+8]
    L_0045de28:
        jne short L_0045de2e
    L_0045de2a:
        mov byte ptr [ebx],2Dh
    L_0045de2d:
        inc ebx
    L_0045de2e:
        mov eax,dword ptr [esi+4]
    L_0045de31:
        xor edi,edi
    L_0045de33:
        inc edi
    L_0045de34:
        test eax,eax
    L_0045de36:
        jg short L_0045de45
    L_0045de38:
        mov eax,ebx
    L_0045de3a:
        call asm_shift_0045dcba
    L_0045de3f:
        mov byte ptr [ebx],30h
    L_0045de42:
        inc ebx
    L_0045de43:
        jmp short L_0045de47
    L_0045de45:
        add ebx,eax
    L_0045de47:
        cmp dword ptr [ebp+0Ch],0
    L_0045de4b:
        jle short L_0045de89
    L_0045de4d:
        mov eax,ebx
    L_0045de4f:
        call asm_shift_0045dcba
    L_0045de54:
        mov al,byte ptr [data_00473af4]
    L_0045de59:
        mov byte ptr [ebx],al
    L_0045de5b:
        mov esi,dword ptr [esi+4]
    L_0045de5e:
        inc ebx
    L_0045de5f:
        test esi,esi
    L_0045de61:
        jge short L_0045de89
    L_0045de63:
        neg esi
    L_0045de65:
        cmp byte ptr [ebp+10h],0
    L_0045de69:
        jne short L_0045de70
    L_0045de6b:
        cmp dword ptr [ebp+0Ch],esi
    L_0045de6e:
        jl short L_0045de73
    L_0045de70:
        mov dword ptr [ebp+0Ch],esi
    L_0045de73:
        mov edi,dword ptr [ebp+0Ch]
    L_0045de76:
        mov eax,ebx
    L_0045de78:
        call asm_shift_0045dcba
    L_0045de7d:
        push edi
    L_0045de7e:
        push 30h
    L_0045de80:
        push ebx
    L_0045de81:
        call asm_memset_0045bed0
    L_0045de86:
        add esp,0Ch
    L_0045de89:
        mov eax,dword ptr [ebp+8]
    L_0045de8c:
        pop edi
    L_0045de8d:
        pop esi
    L_0045de8e:
        pop ebx
    L_0045de8f:
        pop ebp
    L_0045de90:
        ret
    }
}
