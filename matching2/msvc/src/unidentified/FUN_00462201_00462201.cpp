#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462201..0x00462208: FUN_00462201
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462201_00462201() {
    __asm {
    L_00462201:
        push ebx
    L_00462202:
        call asm_FUN_0045f7b5_0045f7b5
    L_00462207:
        pop ecx
    L_00462208:
        ret
    }
}
