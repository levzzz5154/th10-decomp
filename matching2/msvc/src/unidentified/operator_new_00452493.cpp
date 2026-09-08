#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452493..0x004524A0: operator_new
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_operator_new_00452493() {
    __asm {
    L_00452493:
        push 1
    L_00452495:
        push dword ptr [esp+8]
    L_00452499:
        call asm_nh_malloc_004526da
    L_0045249e:
        pop ecx
    L_0045249f:
        pop ecx
    L_004524a0:
        ret
    }
}
