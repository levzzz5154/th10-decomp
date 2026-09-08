#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452A84..0x00452ABB: _atof
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_atof_00452a84() {
    __asm {
    L_00452a84:
        push ebp
    L_00452a85:
        mov ebp,esp
    L_00452a87:
        sub esp,18h
    L_00452a8a:
        push esi
    L_00452a8b:
        mov esi,dword ptr [ebp+8]
    L_00452a8e:
        jmp short L_00452a91
    L_00452a90:
        inc esi
    L_00452a91:
        movzx eax,byte ptr [esi]
    L_00452a94:
        push eax
    L_00452a95:
        call asm_isspace_004568d7
    L_00452a9a:
        test eax,eax
    L_00452a9c:
        pop ecx
    L_00452a9d:
        jne short L_00452a90
    L_00452a9f:
        push eax
    L_00452aa0:
        push eax
    L_00452aa1:
        push esi
    L_00452aa2:
        call asm_strlen_00456720
    L_00452aa7:
        pop ecx
    L_00452aa8:
        push eax
    L_00452aa9:
        lea eax,[ebp-18h]
    L_00452aac:
        push esi
    L_00452aad:
        push eax
    L_00452aae:
        call asm_FUN_00456674_00456674
    L_00452ab3:
        fld qword ptr [eax+10h]
    L_00452ab6:
        add esp,14h
    L_00452ab9:
        pop esi
    L_00452aba:
        leave
    L_00452abb:
        ret
    }
}
