#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00426510..0x00426516: FUN_00426510
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00426510_00426510() {
    __asm {
    L_00426510:
        mov eax,ecx
    L_00426512:
        jmp asm_FUN_00426360_00426360
    }
}
