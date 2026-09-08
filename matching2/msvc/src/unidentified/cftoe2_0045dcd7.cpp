#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DCD7..0x0045DD84: __cftoe2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_cftoe2_0045dcd7() {
    __asm {
    L_0045dcd7:
        push ebp
    L_0045dcd8:
        mov ebp,esp
    L_0045dcda:
        cmp byte ptr [ebp+10h],0
    L_0045dcde:
        push esi
    L_0045dcdf:
        mov esi,eax
    L_0045dce1:
        je short L_0045dd00
    L_0045dce3:
        xor eax,eax
    L_0045dce5:
        cmp dword ptr [ebp+8],eax
    L_0045dce8:
        push edi
    L_0045dce9:
        setg al
    L_0045dcec:
        xor ecx,ecx
    L_0045dcee:
        cmp dword ptr [esi],2Dh
    L_0045dcf1:
        sete cl
    L_0045dcf4:
        mov edi,eax
    L_0045dcf6:
        add ecx,ebx
    L_0045dcf8:
        mov eax,ecx
    L_0045dcfa:
        call asm_shift_0045dcba
    L_0045dcff:
        pop edi
    L_0045dd00:
        cmp dword ptr [esi],2Dh
    L_0045dd03:
        mov eax,ebx
    L_0045dd05:
        jne short L_0045dd0d
    L_0045dd07:
        mov byte ptr [ebx],2Dh
    L_0045dd0a:
        lea eax,[ebx+1]
    L_0045dd0d:
        cmp dword ptr [ebp+8],0
    L_0045dd11:
        jle short L_0045dd24
    L_0045dd13:
        lea ecx,[eax+1]
    L_0045dd16:
        mov dl,byte ptr [ecx]
    L_0045dd18:
        mov byte ptr [eax],dl
    L_0045dd1a:
        mov eax,ecx
    L_0045dd1c:
        mov cl,byte ptr [data_00473af4]
    L_0045dd22:
        mov byte ptr [eax],cl
    L_0045dd24:
        xor ecx,ecx
    L_0045dd26:
        cmp byte ptr [ebp+10h],cl
    L_0045dd29:
        push 46C554h
    L_0045dd2e:
        sete cl
    L_0045dd31:
        add ecx,eax
    L_0045dd33:
        add ecx,dword ptr [ebp+8]
    L_0045dd36:
        push ecx
    L_0045dd37:
        call asm_FUN_0045bd80_0045bd80
    L_0045dd3c:
        cmp dword ptr [ebp+0Ch],0
    L_0045dd40:
        pop ecx
    L_0045dd41:
        pop ecx
    L_0045dd42:
        mov ecx,eax
    L_0045dd44:
        je short L_0045dd49
    L_0045dd46:
        mov byte ptr [ecx],45h
    L_0045dd49:
        mov eax,dword ptr [esi+0Ch]
    L_0045dd4c:
        inc ecx
    L_0045dd4d:
        cmp byte ptr [eax],30h
    L_0045dd50:
        je short L_0045dd80
    L_0045dd52:
        mov eax,dword ptr [esi+4]
    L_0045dd55:
        dec eax
    L_0045dd56:
        jns short L_0045dd5d
    L_0045dd58:
        neg eax
    L_0045dd5a:
        mov byte ptr [ecx],2Dh
    L_0045dd5d:
        inc ecx
    L_0045dd5e:
        cmp eax,64h
    L_0045dd61:
        jl short L_0045dd6d
    L_0045dd63:
        cdq
    L_0045dd64:
        push 64h
    L_0045dd66:
        pop esi
    L_0045dd67:
        idiv esi
    L_0045dd69:
        add byte ptr [ecx],al
    L_0045dd6b:
        mov eax,edx
    L_0045dd6d:
        inc ecx
    L_0045dd6e:
        cmp eax,0Ah
    L_0045dd71:
        jl short L_0045dd7d
    L_0045dd73:
        cdq
    L_0045dd74:
        push 0Ah
    L_0045dd76:
        pop esi
    L_0045dd77:
        idiv esi
    L_0045dd79:
        add byte ptr [ecx],al
    L_0045dd7b:
        mov eax,edx
    L_0045dd7d:
        add byte ptr [ecx+1],al
    L_0045dd80:
        mov eax,ebx
    L_0045dd82:
        pop esi
    L_0045dd83:
        pop ebp
    L_0045dd84:
        ret
    }
}
