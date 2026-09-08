#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040BA80..0x0040BA85: FUN_0040ba80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ba80_0040ba80() {
    __asm {
    L_0040ba80:
        mov eax,1
    L_0040ba85:
        ret
    }
}
