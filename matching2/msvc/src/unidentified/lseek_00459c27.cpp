#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459C27..0x00459CAA: __lseek
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lseek_00459c27() {
    __asm {
    L_00459c27:
        push 0Ch
    L_00459c29:
        push 46B0A0h
    L_00459c2e:
        call asm_SEH_prolog_00454bbc
    L_00459c33:
        mov ebx,dword ptr [ebp+8]
    L_00459c36:
        cmp ebx,dword ptr [data_004991e4]
    L_00459c3c:
        TH10_REL8(0x73, 0x00459c3c, VA_asm_lseek_part_00459cb6)
    L_00459c3e:
        mov eax,ebx
    L_00459c40:
        sar eax,5
    L_00459c43:
        lea edi,[eax*4+499200h]
    L_00459c4a:
        mov eax,ebx
    L_00459c4c:
        and eax,1Fh
    L_00459c4f:
        lea esi,[eax+eax*8]
    L_00459c52:
        shl esi,2
    L_00459c55:
        mov eax,dword ptr [edi]
    L_00459c57:
        test byte ptr [eax+esi+4],1
    L_00459c5c:
        TH10_REL8(0x74, 0x00459c5c, VA_asm_lseek_part_00459cb6)
    L_00459c5e:
        push ebx
    L_00459c5f:
        call asm_lock_fhandle_0045f715
    L_00459c64:
        pop ecx
    L_00459c65:
        and dword ptr [ebp-4],0
    L_00459c69:
        mov eax,dword ptr [edi]
    L_00459c6b:
        test byte ptr [eax+esi+4],1
    L_00459c70:
        je short L_00459c86
    L_00459c72:
        push dword ptr [ebp+10h]
    L_00459c75:
        push dword ptr [ebp+0Ch]
    L_00459c78:
        push ebx
    L_00459c79:
        call asm_lseek_lk_00459bb3
    L_00459c7e:
        add esp,0Ch
    L_00459c81:
        mov dword ptr [ebp-1Ch],eax
    L_00459c84:
        jmp short L_00459c9d
    L_00459c86:
        call asm_FUN_00456af2_00456af2
    L_00459c8b:
        mov dword ptr [eax],9
    L_00459c91:
        call asm_FUN_00456afb_00456afb
    L_00459c96:
        and dword ptr [eax],0
    L_00459c99:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_00459c9d:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00459ca1:
        call asm_FUN_00459cae_00459cae
    L_00459ca6:
        mov eax,dword ptr [ebp-1Ch]
    L_00459ca9:
        TH10_REL8(0xeb, 0x00459ca9, VA_asm_target_00459ccc)
    }
}

// 0x00459CB6..0x00459CD1: __lseek
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lseek_part_00459cb6() {
    __asm {
    L_00459cb6:
        call asm_FUN_00456af2_00456af2
    L_00459cbb:
        mov dword ptr [eax],9
    L_00459cc1:
        call asm_FUN_00456afb_00456afb
    L_00459cc6:
        and dword ptr [eax],0
    L_00459cc9:
        or eax,0FFFFFFFFh
    L_00459ccc:
        call asm_SEH_epilog_00454bf7
    L_00459cd1:
        ret
    }
}
