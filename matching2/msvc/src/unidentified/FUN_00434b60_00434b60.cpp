#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434B60..0x00434B63: FUN_00434b60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00434b60_00434b60() {
    __asm {
    L_00434b60:
        mov eax,dword ptr [eax+4]
    L_00434b63:
        ret
    }
}
