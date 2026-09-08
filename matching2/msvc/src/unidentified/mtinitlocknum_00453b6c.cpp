#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453B6C..0x00453C02: __mtinitlocknum
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mtinitlocknum_00453b6c() {
    __asm {
    L_00453b6c:
        push 8
    L_00453b6e:
        push 46A780h
    L_00453b73:
        call asm_SEH_prolog_00454bbc
    L_00453b78:
        mov esi,dword ptr [ebp+8]
    L_00453b7b:
        lea esi,[esi*8+473080h]
    L_00453b82:
        xor ebx,ebx
    L_00453b84:
        cmp dword ptr [esi],ebx
    L_00453b86:
        jne short L_00453bfa
    L_00453b88:
        push 18h
    L_00453b8a:
        call asm_malloc_00452706
    L_00453b8f:
        pop ecx
    L_00453b90:
        mov edi,eax
    L_00453b92:
        cmp edi,ebx
    L_00453b94:
        jne short L_00453ba3
    L_00453b96:
        call asm_FUN_00456af2_00456af2
    L_00453b9b:
        mov dword ptr [eax],0Ch
    L_00453ba1:
        jmp short L_00453be2
    L_00453ba3:
        push 0Ah
    L_00453ba5:
        call asm_lock_00453c0c
    L_00453baa:
        pop ecx
    L_00453bab:
        mov dword ptr [ebp-4],ebx
    L_00453bae:
        cmp dword ptr [esi],ebx
    L_00453bb0:
        jne short L_00453bea
    L_00453bb2:
        push 0FA0h
    L_00453bb7:
        push edi
    L_00453bb8:
        call asm_crtInitCritSecAndSpinCount_0045980e
    L_00453bbd:
        pop ecx
    L_00453bbe:
        pop ecx
    L_00453bbf:
        test eax,eax
    L_00453bc1:
        jne short L_00453be6
    L_00453bc3:
        push edi
    L_00453bc4:
        call asm_free_00452422
    L_00453bc9:
        call asm_FUN_00456af2_00456af2
    L_00453bce:
        mov dword ptr [eax],0Ch
    L_00453bd4:
        push 0FFFFFFFFh
    L_00453bd6:
        lea eax,[ebp-10h]
    L_00453bd9:
        push eax
    L_00453bda:
        call asm_local_unwind2_004598de
    L_00453bdf:
        add esp,0Ch
    L_00453be2:
        xor eax,eax
    L_00453be4:
        jmp short L_00453bfd
    L_00453be6:
        mov dword ptr [esi],edi
    L_00453be8:
        jmp short L_00453bf1
    L_00453bea:
        push edi
    L_00453beb:
        call asm_free_00452422
    L_00453bf0:
        pop ecx
    L_00453bf1:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00453bf5:
        call asm_FUN_00453c03_00453c03
    L_00453bfa:
        xor eax,eax
    L_00453bfc:
        inc eax
    L_00453bfd:
        call asm_SEH_epilog_00454bf7
    L_00453c02:
        ret
    }
}
