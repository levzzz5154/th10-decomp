#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004597FE..0x0045980D: ___crtInitCritSecNoSpinCount@8
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtInitCritSecNoSpinCount_8_004597fe() {
    __asm {
    L_004597fe:
        push dword ptr [esp+4]
    L_00459802:
        call dword ptr [data_004660b8]
    L_00459808:
        xor eax,eax
    L_0045980a:
        inc eax
    L_0045980b:
        ret 8
    }
}
