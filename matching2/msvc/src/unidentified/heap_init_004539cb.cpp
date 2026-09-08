#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004539CB..0x00453A1B: __heap_init
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_heap_init_004539cb() {
    __asm {
    L_004539cb:
        xor eax,eax
    L_004539cd:
        cmp dword ptr [esp+4],eax
    L_004539d1:
        push 0
    L_004539d3:
        sete al
    L_004539d6:
        push 1000h
    L_004539db:
        push eax
    L_004539dc:
        call dword ptr [data_0046618c]
    L_004539e2:
        test eax,eax
    L_004539e4:
        mov dword ptr [data_00499340],eax
    L_004539e9:
        je short L_00453a15
    L_004539eb:
        call asm_heap_select_004539b1
    L_004539f0:
        cmp eax,3
    L_004539f3:
        mov dword ptr [data_00499344],eax
    L_004539f8:
        jne short L_00453a18
    L_004539fa:
        push 3F8h
    L_004539ff:
        call asm_sbh_heap_init_00453c52
    L_00453a04:
        test eax,eax
    L_00453a06:
        pop ecx
    L_00453a07:
        jne short L_00453a18
    L_00453a09:
        push dword ptr [data_00499340]
    L_00453a0f:
        call dword ptr [data_00466190]
    L_00453a15:
        xor eax,eax
    L_00453a17:
        ret
    L_00453a18:
        xor eax,eax
    L_00453a1a:
        inc eax
    L_00453a1b:
        ret
    }
}
