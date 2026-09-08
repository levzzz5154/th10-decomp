#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436D30..0x00436D5D: FUN_00436d30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436d30_00436d30() {
    __asm {
    L_00436d30:
        push ebx
    L_00436d31:
        mov bl,byte ptr [ecx+3]
    L_00436d34:
        test bl,bl
    L_00436d36:
        je short L_00436d5c
    L_00436d38:
        mov ebx,dword ptr [eax+4]
    L_00436d3b:
        push esi
    L_00436d3c:
        movzx esi,byte ptr [ecx+2]
    L_00436d40:
        add dword ptr [eax],esi
    L_00436d42:
        movzx esi,byte ptr [ecx+1]
    L_00436d46:
        add ebx,esi
    L_00436d48:
        mov esi,dword ptr [eax+8]
    L_00436d4b:
        mov dword ptr [eax+4],ebx
    L_00436d4e:
        movzx ecx,byte ptr [ecx]
    L_00436d51:
        add esi,ecx
    L_00436d53:
        mov dword ptr [eax+8],esi
    L_00436d56:
        mov eax,dword ptr [edx]
    L_00436d58:
        inc eax
    L_00436d59:
        mov dword ptr [edx],eax
    L_00436d5b:
        pop esi
    L_00436d5c:
        pop ebx
    L_00436d5d:
        ret
    }
}
