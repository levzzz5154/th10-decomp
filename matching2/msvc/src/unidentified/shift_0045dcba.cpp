#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DCBA..0x0045DCD6: __shift
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_shift_0045dcba() {
    __asm {
    L_0045dcba:
        test edi,edi
    L_0045dcbc:
        push esi
    L_0045dcbd:
        mov esi,eax
    L_0045dcbf:
        je short L_0045dcd5
    L_0045dcc1:
        push esi
    L_0045dcc2:
        call asm_strlen_00456720
    L_0045dcc7:
        inc eax
    L_0045dcc8:
        push eax
    L_0045dcc9:
        push esi
    L_0045dcca:
        add esi,edi
    L_0045dccc:
        push esi
    L_0045dccd:
        call asm_memmove_00453280
    L_0045dcd2:
        add esp,10h
    L_0045dcd5:
        pop esi
    L_0045dcd6:
        ret
    }
}
