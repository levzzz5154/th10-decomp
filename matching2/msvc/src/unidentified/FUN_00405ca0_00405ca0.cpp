#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405CA0..0x00405CA6: FUN_00405ca0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405ca0_00405ca0() {
    __asm {
    L_00405ca0:
        mov eax,dword ptr [eax+3E0B50h]
    L_00405ca6:
        ret
    }
}
