#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457932..0x0045794C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00457932() {
    __asm {
    L_00457932:
        mov eax,0E06D7363h
    L_00457937:
        cmp dword ptr [esp+4],eax
    L_0045793b:
        jne short L_0045794a
    L_0045793d:
        push dword ptr [esp+8]
    L_00457941:
        push eax
    L_00457942:
        call asm_XcptFilter_004577ce
    L_00457947:
        pop ecx
    L_00457948:
        pop ecx
    L_00457949:
        ret
    L_0045794a:
        xor eax,eax
    L_0045794c:
        ret
    }
}
