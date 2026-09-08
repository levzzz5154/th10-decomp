#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004539B1..0x004539CA: ___heap_select
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_heap_select_004539b1() {
    __asm {
    L_004539b1:
        cmp dword ptr [data_00477470],2
    L_004539b8:
        jne short L_004539c7
    L_004539ba:
        cmp dword ptr [data_0047747c],5
    L_004539c1:
        jb short L_004539c7
    L_004539c3:
        xor eax,eax
    L_004539c5:
        inc eax
    L_004539c6:
        ret
    L_004539c7:
        push 3
    L_004539c9:
        pop eax
    L_004539ca:
        ret
    }
}
