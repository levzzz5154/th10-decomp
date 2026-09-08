#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417640..0x00417643: FUN_00417640
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417640_00417640() {
    __asm {
    L_00417640:
        mov eax,dword ptr [eax+18h]
    L_00417643:
        ret
    }
}
