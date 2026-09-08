#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004087D0..0x004087D7: FUN_004087d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004087d0_004087d0() {
    __asm {
    L_004087d0:
        mov word ptr [eax+304h],cx
    L_004087d7:
        ret
    }
}
