#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043D0F0..0x0043D111: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043d0f0() {
    __asm {
    L_0043d0f0:
        push ecx
    L_0043d0f1:
        lea eax,[esp]
    L_0043d0f4:
        push eax
    L_0043d0f5:
        push 0
    L_0043d0f7:
        push 492590h
    L_0043d0fc:
        push 43D080h
    L_0043d101:
        push 0
    L_0043d103:
        push 0
    L_0043d105:
        call dword ptr [data_00466118]
    L_0043d10b:
        mov dword ptr [data_004977ac],eax
    L_0043d110:
        pop ecx
    L_0043d111:
        ret
    }
}
