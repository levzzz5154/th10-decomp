#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459BB3..0x00459C26: __lseek_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_lseek_lk_00459bb3() {
    __asm {
    L_00459bb3:
        push esi
    L_00459bb4:
        mov esi,dword ptr [esp+8]
    L_00459bb8:
        push esi
    L_00459bb9:
        call asm_get_osfhandle_0045f6d4
    L_00459bbe:
        cmp eax,0FFFFFFFFh
    L_00459bc1:
        pop ecx
    L_00459bc2:
        jne short L_00459bd4
    L_00459bc4:
        call asm_FUN_00456af2_00456af2
    L_00459bc9:
        mov dword ptr [eax],9
    L_00459bcf:
        or eax,0FFFFFFFFh
    L_00459bd2:
        pop esi
    L_00459bd3:
        ret
    L_00459bd4:
        push edi
    L_00459bd5:
        push dword ptr [esp+14h]
    L_00459bd9:
        push 0
    L_00459bdb:
        push dword ptr [esp+18h]
    L_00459bdf:
        push eax
    L_00459be0:
        call dword ptr [data_004660c8]
    L_00459be6:
        mov edi,eax
    L_00459be8:
        cmp edi,0FFFFFFFFh
    L_00459beb:
        jne short L_00459bf5
    L_00459bed:
        call dword ptr [data_0046610c]
    L_00459bf3:
        jmp short L_00459bf7
    L_00459bf5:
        xor eax,eax
    L_00459bf7:
        test eax,eax
    L_00459bf9:
        je short L_00459c07
    L_00459bfb:
        push eax
    L_00459bfc:
        call asm_dosmaperr_00456b04
    L_00459c01:
        pop ecx
    L_00459c02:
        or eax,0FFFFFFFFh
    L_00459c05:
        jmp short L_00459c24
    L_00459c07:
        mov ecx,esi
    L_00459c09:
        and esi,1Fh
    L_00459c0c:
        sar ecx,5
    L_00459c0f:
        mov ecx,dword ptr [ecx*4+499200h]
    L_00459c16:
        mov eax,esi
    L_00459c18:
        lea eax,[eax+eax*8]
    L_00459c1b:
        lea eax,[ecx+eax*4+4]
    L_00459c1f:
        and byte ptr [eax],0FDh
    L_00459c22:
        mov eax,edi
    L_00459c24:
        pop edi
    L_00459c25:
        pop esi
    L_00459c26:
        ret
    }
}
