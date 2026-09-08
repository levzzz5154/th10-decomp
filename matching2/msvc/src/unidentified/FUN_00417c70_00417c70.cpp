#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417C70..0x00417C7B: FUN_00417c70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417c70_00417c70() {
    __asm {
    L_00417c70:
        mov eax,dword ptr [data_00477810]
    L_00417c75:
        push eax
    L_00417c76:
        call asm_FUN_00417870_00417870
    L_00417c7b:
        ret
    }
}
