#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461361..0x004613E4: __read
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_read_00461361() {
    __asm {
    L_00461361:
        push 0Ch
    L_00461363:
        push 46C950h
    L_00461368:
        call asm_SEH_prolog_00454bbc
    L_0046136d:
        mov ebx,dword ptr [ebp+8]
    L_00461370:
        cmp ebx,dword ptr [data_004991e4]
    L_00461376:
        TH10_REL8(0x73, 0x00461376, VA_asm_read_part_004613f0)
    L_00461378:
        mov eax,ebx
    L_0046137a:
        sar eax,5
    L_0046137d:
        lea edi,[eax*4+499200h]
    L_00461384:
        mov eax,ebx
    L_00461386:
        and eax,1Fh
    L_00461389:
        lea esi,[eax+eax*8]
    L_0046138c:
        shl esi,2
    L_0046138f:
        mov eax,dword ptr [edi]
    L_00461391:
        test byte ptr [eax+esi+4],1
    L_00461396:
        TH10_REL8(0x74, 0x00461396, VA_asm_read_part_004613f0)
    L_00461398:
        push ebx
    L_00461399:
        call asm_lock_fhandle_0045f715
    L_0046139e:
        pop ecx
    L_0046139f:
        and dword ptr [ebp-4],0
    L_004613a3:
        mov eax,dword ptr [edi]
    L_004613a5:
        test byte ptr [eax+esi+4],1
    L_004613aa:
        je short L_004613c0
    L_004613ac:
        push dword ptr [ebp+10h]
    L_004613af:
        push dword ptr [ebp+0Ch]
    L_004613b2:
        push ebx
    L_004613b3:
        call asm_FUN_00461184_00461184
    L_004613b8:
        add esp,0Ch
    L_004613bb:
        mov dword ptr [ebp-1Ch],eax
    L_004613be:
        jmp short L_004613d7
    L_004613c0:
        call asm_FUN_00456af2_00456af2
    L_004613c5:
        mov dword ptr [eax],9
    L_004613cb:
        call asm_FUN_00456afb_00456afb
    L_004613d0:
        and dword ptr [eax],0
    L_004613d3:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_004613d7:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004613db:
        call asm_FUN_004613e8_004613e8
    L_004613e0:
        mov eax,dword ptr [ebp-1Ch]
    L_004613e3:
        TH10_REL8(0xeb, 0x004613e3, VA_asm_target_00461406)
    }
}

// 0x004613F0..0x0046140B: __read
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_read_part_004613f0() {
    __asm {
    L_004613f0:
        call asm_FUN_00456af2_00456af2
    L_004613f5:
        mov dword ptr [eax],9
    L_004613fb:
        call asm_FUN_00456afb_00456afb
    L_00461400:
        and dword ptr [eax],0
    L_00461403:
        or eax,0FFFFFFFFh
    L_00461406:
        call asm_SEH_epilog_00454bf7
    L_0046140b:
        ret
    }
}
