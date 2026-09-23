#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F715..0x0045F7A8: __lock_fhandle
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lock_fhandle_0045f715(int) {
    __asm {
    L_0045f715:
        push 8
    L_0045f717:
        push 46C890h
    L_0045f71c:
        call asm_SEH_prolog_00454bbc
    L_0045f721:
        mov edi,dword ptr [ebp+8]
    L_0045f724:
        mov ecx,edi
    L_0045f726:
        sar ecx,5
    L_0045f729:
        mov eax,edi
    L_0045f72b:
        and eax,1Fh
    L_0045f72e:
        lea eax,[eax+eax*8]
    L_0045f731:
        mov ecx,dword ptr [ecx*4+499200h]
    L_0045f738:
        lea esi,[ecx+eax*4]
    L_0045f73b:
        xor ebx,ebx
    L_0045f73d:
        cmp dword ptr [esi+8],ebx
    L_0045f740:
        jne short L_0045f783
    L_0045f742:
        push 0Ah
    L_0045f744:
        call asm_lock_00453c0c
    L_0045f749:
        pop ecx
    L_0045f74a:
        mov dword ptr [ebp-4],ebx
    L_0045f74d:
        cmp dword ptr [esi+8],ebx
    L_0045f750:
        jne short L_0045f77a
    L_0045f752:
        push 0FA0h
    L_0045f757:
        lea eax,[esi+0Ch]
    L_0045f75a:
        push eax
    L_0045f75b:
        call asm_crtInitCritSecAndSpinCount_0045980e
    L_0045f760:
        pop ecx
    L_0045f761:
        pop ecx
    L_0045f762:
        test eax,eax
    L_0045f764:
        jne short L_0045f777
    L_0045f766:
        push 0FFFFFFFFh
    L_0045f768:
        lea eax,[ebp-10h]
    L_0045f76b:
        push eax
    L_0045f76c:
        call asm_local_unwind2_004598de
    L_0045f771:
        pop ecx
    L_0045f772:
        pop ecx
    L_0045f773:
        xor eax,eax
    L_0045f775:
        jmp short L_0045f7a3
    L_0045f777:
        inc dword ptr [esi+8]
    L_0045f77a:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045f77e:
        call asm_FUN_0045f7ac_0045f7ac
    L_0045f783:
        mov eax,edi
    L_0045f785:
        sar eax,5
    L_0045f788:
        and edi,1Fh
    L_0045f78b:
        lea ecx,[edi+edi*8]
    L_0045f78e:
        mov eax,dword ptr [eax*4+499200h]
    L_0045f795:
        lea eax,[eax+ecx*4+0Ch]
    L_0045f799:
        push eax
    L_0045f79a:
        call dword ptr [data_004660b0]
    L_0045f7a0:
        xor eax,eax
    L_0045f7a2:
        inc eax
    L_0045f7a3:
        call asm_SEH_epilog_00454bf7
    L_0045f7a8:
        ret
    }
}
