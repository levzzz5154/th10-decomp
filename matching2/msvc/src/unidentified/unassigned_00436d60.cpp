#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436D60..0x00436D96: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436d60() {
    __asm {
    L_00436d60:
        xor ecx,ecx
    L_00436d62:
        mov cx,word ptr [edx]
    L_00436d65:
        test ch,0F0h
    L_00436d68:
        je short L_00436d96
    L_00436d6a:
        shr ecx,8
    L_00436d6d:
        and ecx,0Fh
    L_00436d70:
        push edi
    L_00436d71:
        add dword ptr [eax],ecx
    L_00436d73:
        mov edi,dword ptr [eax+4]
    L_00436d76:
        xor ecx,ecx
    L_00436d78:
        mov cl,byte ptr [edx]
    L_00436d7a:
        shr ecx,4
    L_00436d7d:
        and ecx,0Fh
    L_00436d80:
        add edi,ecx
    L_00436d82:
        mov ecx,dword ptr [eax+8]
    L_00436d85:
        mov dword ptr [eax+4],edi
    L_00436d88:
        movzx edx,byte ptr [edx]
    L_00436d8b:
        and edx,0Fh
    L_00436d8e:
        add ecx,edx
    L_00436d90:
        mov dword ptr [eax+8],ecx
    L_00436d93:
        inc dword ptr [esi]
    L_00436d95:
        pop edi
    L_00436d96:
        ret
    }
}
