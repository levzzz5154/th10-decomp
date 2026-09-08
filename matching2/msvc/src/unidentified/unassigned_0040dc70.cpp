#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040DC70..0x0040DC7B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040dc70() {
    __asm {
    L_0040dc70:
        add eax,103Ch
    L_0040dc75:
        push eax
    L_0040dc76:
        call asm_FUN_0040dc80_0040dc80
    L_0040dc7b:
        ret
    }
}
