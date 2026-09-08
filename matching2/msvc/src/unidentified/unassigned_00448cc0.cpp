#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00448CC0..0x00448CF1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00448cc0() {
    __asm {
    L_00448cc0:
        mov eax,dword ptr [esi+358h]
    L_00448cc6:
        test eax,eax
    L_00448cc8:
        je short L_00448cd3
    L_00448cca:
        push eax
    L_00448ccb:
        call asm_free_00452422
    L_00448cd0:
        add esp,4
    L_00448cd3:
        test byte ptr [esp+4],1
    L_00448cd8:
        mov dword ptr [esi+358h],0
    L_00448ce2:
        je short L_00448ced
    L_00448ce4:
        push esi
    L_00448ce5:
        call asm_free_004524a1
    L_00448cea:
        add esp,4
    L_00448ced:
        mov eax,esi
    L_00448cef:
        ret 4
    }
}
