#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442000..0x00442005: FUN_00442000
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442000_00442000() {
    __asm {
    L_00442000:
        mov ecx,dword ptr [eax]
    L_00442002:
        mov dword ptr [edx+4],ecx
    L_00442005:
        ret
    }
}
