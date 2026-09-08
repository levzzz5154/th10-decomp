#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004243B0..0x004243CC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004243b0() {
    __asm {
    L_004243b0:
        mov edx,dword ptr [ecx]
    L_004243b2:
        mov ecx,dword ptr [esp+4]
    L_004243b6:
        xor eax,eax
    L_004243b8:
        cmp edx,ecx
    L_004243ba:
        setl al
    L_004243bd:
        ret 4
    L_004243c0:
        push eax
    L_004243c1:
        mov eax,dword ptr [esp+8]
    L_004243c5:
        call asm_MenuCursor_Advance_0044bea0
    L_004243ca:
        ret 4
    }
}
