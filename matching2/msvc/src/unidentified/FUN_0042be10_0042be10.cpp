#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BE10..0x0042BE1F: FUN_0042be10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042be10_0042be10() {
    __asm {
    L_0042be10:
        push esi
    L_0042be11:
        mov esi,dword ptr [data_00477844]
    L_0042be17:
        call asm_FUN_0042be20_0042be20
    L_0042be1c:
        xor eax,eax
    L_0042be1e:
        pop esi
    L_0042be1f:
        ret
    }
}
