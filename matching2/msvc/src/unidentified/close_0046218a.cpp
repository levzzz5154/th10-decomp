#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046218A..0x004621FD: __close
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_close_0046218a() {
    __asm {
    L_0046218a:
        push 0Ch
    L_0046218c:
        push 46C9D8h
    L_00462191:
        call asm_SEH_prolog_00454bbc
    L_00462196:
        mov ebx,dword ptr [ebp+8]
    L_00462199:
        cmp ebx,dword ptr [data_004991e4]
    L_0046219f:
        TH10_REL8(0x73, 0x0046219f, VA_asm_close_part_00462209)
    L_004621a1:
        mov eax,ebx
    L_004621a3:
        sar eax,5
    L_004621a6:
        lea edi,[eax*4+499200h]
    L_004621ad:
        mov eax,ebx
    L_004621af:
        and eax,1Fh
    L_004621b2:
        lea esi,[eax+eax*8]
    L_004621b5:
        shl esi,2
    L_004621b8:
        mov eax,dword ptr [edi]
    L_004621ba:
        test byte ptr [eax+esi+4],1
    L_004621bf:
        TH10_REL8(0x74, 0x004621bf, VA_asm_close_part_00462209)
    L_004621c1:
        push ebx
    L_004621c2:
        call asm_lock_fhandle_0045f715
    L_004621c7:
        pop ecx
    L_004621c8:
        and dword ptr [ebp-4],0
    L_004621cc:
        mov eax,dword ptr [edi]
    L_004621ce:
        test byte ptr [eax+esi+4],1
    L_004621d3:
        je short L_004621e1
    L_004621d5:
        push ebx
    L_004621d6:
        call asm_close_lk_00462107
    L_004621db:
        pop ecx
    L_004621dc:
        mov dword ptr [ebp-1Ch],eax
    L_004621df:
        jmp short L_004621f0
    L_004621e1:
        call asm_FUN_00456af2_00456af2
    L_004621e6:
        mov dword ptr [eax],9
    L_004621ec:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_004621f0:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004621f4:
        call asm_FUN_00462201_00462201
    L_004621f9:
        mov eax,dword ptr [ebp-1Ch]
    L_004621fc:
        TH10_REL8(0xeb, 0x004621fc, VA_asm_target_0046221f)
    }
}

// 0x00462209..0x00462224: __close
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_close_part_00462209() {
    __asm {
    L_00462209:
        call asm_FUN_00456af2_00456af2
    L_0046220e:
        mov dword ptr [eax],9
    L_00462214:
        call asm_FUN_00456afb_00456afb
    L_00462219:
        and dword ptr [eax],0
    L_0046221c:
        or eax,0FFFFFFFFh
    L_0046221f:
        call asm_SEH_epilog_00454bf7
    L_00462224:
        ret
    }
}
