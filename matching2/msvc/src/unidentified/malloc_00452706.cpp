#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452706..0x00452717: _malloc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_malloc_00452706() {
    __asm {
    L_00452706:
        push dword ptr [data_00477364]
    L_0045270c:
        push dword ptr [esp+8]
    L_00452710:
        call asm_nh_malloc_004526da
    L_00452715:
        pop ecx
    L_00452716:
        pop ecx
    L_00452717:
        ret
    }
}
