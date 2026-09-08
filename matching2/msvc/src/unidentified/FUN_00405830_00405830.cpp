#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405830..0x00405835: FUN_00405830
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405830_00405830() {
    __asm {
    L_00405830:
        mov eax,1
    L_00405835:
        ret
    }
}
