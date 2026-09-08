#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459E8E..0x00459F11: __write
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_write_00459e8e() {
    __asm {
    L_00459e8e:
        push 0Ch
    L_00459e90:
        push 46B0B0h
    L_00459e95:
        call asm_SEH_prolog_00454bbc
    L_00459e9a:
        mov ebx,dword ptr [ebp+8]
    L_00459e9d:
        cmp ebx,dword ptr [data_004991e4]
    L_00459ea3:
        TH10_REL8(0x73, 0x00459ea3, VA_asm_write_part_00459f1d)
    L_00459ea5:
        mov eax,ebx
    L_00459ea7:
        sar eax,5
    L_00459eaa:
        lea edi,[eax*4+499200h]
    L_00459eb1:
        mov eax,ebx
    L_00459eb3:
        and eax,1Fh
    L_00459eb6:
        lea esi,[eax+eax*8]
    L_00459eb9:
        shl esi,2
    L_00459ebc:
        mov eax,dword ptr [edi]
    L_00459ebe:
        test byte ptr [eax+esi+4],1
    L_00459ec3:
        TH10_REL8(0x74, 0x00459ec3, VA_asm_write_part_00459f1d)
    L_00459ec5:
        push ebx
    L_00459ec6:
        call asm_lock_fhandle_0045f715
    L_00459ecb:
        pop ecx
    L_00459ecc:
        and dword ptr [ebp-4],0
    L_00459ed0:
        mov eax,dword ptr [edi]
    L_00459ed2:
        test byte ptr [eax+esi+4],1
    L_00459ed7:
        je short L_00459eed
    L_00459ed9:
        push dword ptr [ebp+10h]
    L_00459edc:
        push dword ptr [ebp+0Ch]
    L_00459edf:
        push ebx
    L_00459ee0:
        call asm_FUN_00459cd2_00459cd2
    L_00459ee5:
        add esp,0Ch
    L_00459ee8:
        mov dword ptr [ebp-1Ch],eax
    L_00459eeb:
        jmp short L_00459f04
    L_00459eed:
        call asm_FUN_00456af2_00456af2
    L_00459ef2:
        mov dword ptr [eax],9
    L_00459ef8:
        call asm_FUN_00456afb_00456afb
    L_00459efd:
        and dword ptr [eax],0
    L_00459f00:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_00459f04:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00459f08:
        call asm_FUN_00459f15_00459f15
    L_00459f0d:
        mov eax,dword ptr [ebp-1Ch]
    L_00459f10:
        TH10_REL8(0xeb, 0x00459f10, VA_asm_target_00459f33)
    }
}

// 0x00459F1D..0x00459F38: __write
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_write_part_00459f1d() {
    __asm {
    L_00459f1d:
        call asm_FUN_00456af2_00456af2
    L_00459f22:
        mov dword ptr [eax],9
    L_00459f28:
        call asm_FUN_00456afb_00456afb
    L_00459f2d:
        and dword ptr [eax],0
    L_00459f30:
        or eax,0FFFFFFFFh
    L_00459f33:
        call asm_SEH_epilog_00454bf7
    L_00459f38:
        ret
    }
}
