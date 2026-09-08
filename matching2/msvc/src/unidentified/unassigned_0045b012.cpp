#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B012..0x0045B02C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045b012() {
    __asm {
    L_0045b012:
        push 0
    L_0045b014:
        push dword ptr [esp+14h]
    L_0045b018:
        push dword ptr [esp+14h]
    L_0045b01c:
        push dword ptr [esp+14h]
    L_0045b020:
        push dword ptr [esp+14h]
    L_0045b024:
        call asm_Strftime_0045afe0
    L_0045b029:
        add esp,14h
    L_0045b02c:
        ret
    }
}
