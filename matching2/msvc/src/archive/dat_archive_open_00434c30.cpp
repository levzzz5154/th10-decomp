#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00434C30..0x00434C9B: ?DatArchive_Open@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_Open_00434c30() {
    __asm {
    L_00434c30:
        push esi
    L_00434c31:
        push edi
    L_00434c32:
        mov esi,ecx
    L_00434c34:
        mov edi,eax
    L_00434c36:
        call asm_DatArchive_Close_00434d10
    L_00434c3b:
        push 0Ch
    L_00434c3d:
        call asm_operator_new_00452493
    L_00434c42:
        add esp,4
    L_00434c45:
        test eax,eax
    L_00434c47:
        je short L_00434c5f
    L_00434c49:
        mov dword ptr [eax],46F230h
    L_00434c4f:
        mov dword ptr [eax+4],0FFFFFFFFh
    L_00434c56:
        mov dword ptr [eax+8],0
    L_00434c5d:
        jmp short L_00434c61
    L_00434c5f:
        xor eax,eax
    L_00434c61:
        test eax,eax
    L_00434c63:
        mov dword ptr [esi+0Ch],eax
    L_00434c66:
        je short L_00434c97
    L_00434c68:
        push edi
    L_00434c69:
        call asm_DatArchive_LoadIndex_00434f70
    L_00434c6e:
        test al,al
    L_00434c70:
        je short L_00434c92
    L_00434c72:
        call asm_LegacyString_Duplicate_00435220
    L_00434c77:
        test eax,eax
    L_00434c79:
        mov dword ptr [esi+8],eax
    L_00434c7c:
        je short L_00434c92
    L_00434c7e:
        mov ecx,dword ptr [esi+0Ch]
    L_00434c81:
        mov esi,dword ptr [data_00474908]
    L_00434c87:
        mov edx,dword ptr [ecx]
    L_00434c89:
        push esi
    L_00434c8a:
        push eax
    L_00434c8b:
        call dword ptr [edx]
    L_00434c8d:
        pop edi
    L_00434c8e:
        mov al,1
    L_00434c90:
        pop esi
    L_00434c91:
        ret
    L_00434c92:
        call asm_DatArchive_Close_00434d10
    L_00434c97:
        pop edi
    L_00434c98:
        xor al,al
    L_00434c9a:
        pop esi
    L_00434c9b:
        ret
    }
}
