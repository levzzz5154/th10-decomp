#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C9FB..0x0045CA4F: _GetLcidFromLanguage
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GetLcidFromLanguage_0045c9fb() {
    __asm {
    L_0045c9fb:
        push dword ptr [data_00477644]
    L_0045ca01:
        call asm_strlen_00456720
    L_0045ca06:
        sub eax,3
    L_0045ca09:
        neg eax
    L_0045ca0b:
        sbb eax,eax
    L_0045ca0d:
        inc eax
    L_0045ca0e:
        pop ecx
    L_0045ca0f:
        mov dword ptr [data_00477634],eax
    L_0045ca14:
        je short L_0045ca22
    L_0045ca16:
        mov dword ptr [data_00477640],2
    L_0045ca20:
        jmp short L_0045ca32
    L_0045ca22:
        mov edx,dword ptr [data_00477644]
    L_0045ca28:
        call asm_GetPrimaryLen_0045c527
    L_0045ca2d:
        mov dword ptr [data_00477640],eax
    L_0045ca32:
        push 1
    L_0045ca34:
        push 45C86Fh
    L_0045ca39:
        call dword ptr [data_00466058]
    L_0045ca3f:
        test byte ptr [data_00477628],4
    L_0045ca46:
        jne short L_0045ca4f
    L_0045ca48:
        and dword ptr [data_00477628],0
    L_0045ca4f:
        ret
    }
}
