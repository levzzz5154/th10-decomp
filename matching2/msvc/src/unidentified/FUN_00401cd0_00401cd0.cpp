#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401CD0..0x00401CD6: FUN_00401cd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401cd0_00401cd0() {
    __asm {
    L_00401cd0:
        mov eax,dword ptr [eax+394h]
    L_00401cd6:
        ret
    }
}
