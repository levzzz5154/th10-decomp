#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BF30..0x0045BF72: _strcmp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strcmp_0045bf30() {
    __asm {
    L_0045bf30:
        mov edx,dword ptr [esp+4]
    L_0045bf34:
        mov ecx,dword ptr [esp+8]
    L_0045bf38:
        test edx,3
    L_0045bf3e:
        TH10_REL8(0x75, 0x0045bf3e, VA_asm_target_0045bf7c)
    L_0045bf40:
        mov eax,dword ptr [edx]
    L_0045bf42:
        cmp al,byte ptr [ecx]
    L_0045bf44:
        TH10_REL8(0x75, 0x0045bf44, VA_asm_strcmp_part_0045bf74)
    L_0045bf46:
        or al,al
    L_0045bf48:
        je short L_0045bf70
    L_0045bf4a:
        cmp ah,byte ptr [ecx+1]
    L_0045bf4d:
        TH10_REL8(0x75, 0x0045bf4d, VA_asm_strcmp_part_0045bf74)
    L_0045bf4f:
        or ah,ah
    L_0045bf51:
        je short L_0045bf70
    L_0045bf53:
        shr eax,10h
    L_0045bf56:
        cmp al,byte ptr [ecx+2]
    L_0045bf59:
        TH10_REL8(0x75, 0x0045bf59, VA_asm_strcmp_part_0045bf74)
    L_0045bf5b:
        or al,al
    L_0045bf5d:
        je short L_0045bf70
    L_0045bf5f:
        cmp ah,byte ptr [ecx+3]
    L_0045bf62:
        TH10_REL8(0x75, 0x0045bf62, VA_asm_strcmp_part_0045bf74)
    L_0045bf64:
        add ecx,4
    L_0045bf67:
        add edx,4
    L_0045bf6a:
        or ah,ah
    L_0045bf6c:
        jne short L_0045bf40
    L_0045bf6e:
        mov edi,edi
    L_0045bf70:
        xor eax,eax
    L_0045bf72:
        ret
    }
}

// 0x0045BF74..0x0045BFB7: _strcmp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strcmp_part_0045bf74() {
    __asm {
    L_0045bf74:
        sbb eax,eax
    L_0045bf76:
        shl eax,1
    L_0045bf78:
        add eax,1
    L_0045bf7b:
        ret
    L_0045bf7c:
        test edx,1
    L_0045bf82:
        je short L_0045bf9c
    L_0045bf84:
        mov al,byte ptr [edx]
    L_0045bf86:
        add edx,1
    L_0045bf89:
        cmp al,byte ptr [ecx]
    L_0045bf8b:
        jne short L_0045bf74
    L_0045bf8d:
        add ecx,1
    L_0045bf90:
        or al,al
    L_0045bf92:
        TH10_REL8(0x74, 0x0045bf92, VA_asm_target_0045bf70)
    L_0045bf94:
        test edx,2
    L_0045bf9a:
        TH10_REL8(0x74, 0x0045bf9a, VA_asm_target_0045bf40)
    L_0045bf9c:
        mov ax,word ptr [edx]
    L_0045bf9f:
        add edx,2
    L_0045bfa2:
        cmp al,byte ptr [ecx]
    L_0045bfa4:
        jne short L_0045bf74
    L_0045bfa6:
        or al,al
    L_0045bfa8:
        TH10_REL8(0x74, 0x0045bfa8, VA_asm_target_0045bf70)
    L_0045bfaa:
        cmp ah,byte ptr [ecx+1]
    L_0045bfad:
        jne short L_0045bf74
    L_0045bfaf:
        or ah,ah
    L_0045bfb1:
        TH10_REL8(0x74, 0x0045bfb1, VA_asm_target_0045bf70)
    L_0045bfb3:
        add ecx,2
    L_0045bfb6:
        TH10_REL8(0xeb, 0x0045bfb6, VA_asm_target_0045bf40)
    }
}
