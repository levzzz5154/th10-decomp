#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460D10..0x00460D86: __fptostr
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_fptostr_00460d10() {
    __asm {
    L_00460d10:
        push ebp
    L_00460d11:
        mov ebp,esp
    L_00460d13:
        mov edx,dword ptr [ebp+10h]
    L_00460d16:
        mov ecx,dword ptr [edx+0Ch]
    L_00460d19:
        push ebx
    L_00460d1a:
        mov ebx,dword ptr [ebp+0Ch]
    L_00460d1d:
        test ebx,ebx
    L_00460d1f:
        push esi
    L_00460d20:
        mov esi,dword ptr [ebp+8]
    L_00460d23:
        push edi
    L_00460d24:
        lea edi,[esi+1]
    L_00460d27:
        mov byte ptr [esi],30h
    L_00460d2a:
        mov eax,edi
    L_00460d2c:
        jle short L_00460d4d
    L_00460d2e:
        mov dword ptr [ebp+8],ebx
    L_00460d31:
        xor ebx,ebx
    L_00460d33:
        mov dl,byte ptr [ecx]
    L_00460d35:
        test dl,dl
    L_00460d37:
        je short L_00460d3f
    L_00460d39:
        movsx edx,dl
    L_00460d3c:
        inc ecx
    L_00460d3d:
        jmp short L_00460d42
    L_00460d3f:
        push 30h
    L_00460d41:
        pop edx
    L_00460d42:
        mov byte ptr [eax],dl
    L_00460d44:
        inc eax
    L_00460d45:
        dec dword ptr [ebp+8]
    L_00460d48:
        jne short L_00460d33
    L_00460d4a:
        mov edx,dword ptr [ebp+10h]
    L_00460d4d:
        test ebx,ebx
    L_00460d4f:
        mov byte ptr [eax],0
    L_00460d52:
        jl short L_00460d66
    L_00460d54:
        cmp byte ptr [ecx],35h
    L_00460d57:
        jl short L_00460d66
    L_00460d59:
        jmp short L_00460d5e
    L_00460d5b:
        mov byte ptr [eax],30h
    L_00460d5e:
        dec eax
    L_00460d5f:
        cmp byte ptr [eax],39h
    L_00460d62:
        je short L_00460d5b
    L_00460d64:
        inc byte ptr [eax]
    L_00460d66:
        cmp byte ptr [esi],31h
    L_00460d69:
        jne short L_00460d70
    L_00460d6b:
        inc dword ptr [edx+4]
    L_00460d6e:
        jmp short L_00460d82
    L_00460d70:
        push edi
    L_00460d71:
        call asm_strlen_00456720
    L_00460d76:
        inc eax
    L_00460d77:
        push eax
    L_00460d78:
        push edi
    L_00460d79:
        push esi
    L_00460d7a:
        call asm_memmove_00453280
    L_00460d7f:
        add esp,10h
    L_00460d82:
        pop edi
    L_00460d83:
        pop esi
    L_00460d84:
        pop ebx
    L_00460d85:
        pop ebp
    L_00460d86:
        ret
    }
}
