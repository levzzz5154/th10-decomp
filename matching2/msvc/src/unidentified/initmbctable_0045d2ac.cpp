#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D2AC..0x0045D2C9: ___initmbctable
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_initmbctable_0045d2ac() {
    __asm {
    L_0045d2ac:
        cmp dword ptr [data_00499314],0
    L_0045d2b3:
        jne short L_0045d2c7
    L_0045d2b5:
        push 0FFFFFFFDh
    L_0045d2b7:
        call asm_setmbcp_0045d15c
    L_0045d2bc:
        pop ecx
    L_0045d2bd:
        mov dword ptr [data_00499314],1
    L_0045d2c7:
        xor eax,eax
    L_0045d2c9:
        ret
    }
}
