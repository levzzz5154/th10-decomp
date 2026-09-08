#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405160..0x00405163: FUN_00405160
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405160_00405160() {
    __asm {
    L_00405160:
        mov dword ptr [eax+44h],ecx
    L_00405163:
        ret
    }
}
