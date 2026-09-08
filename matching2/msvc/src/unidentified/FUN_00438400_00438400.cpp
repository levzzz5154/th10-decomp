#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438400..0x00438402: FUN_00438400
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00438400_00438400() {
    __asm {
    L_00438400:
        mov eax,ecx
    L_00438402:
        ret
    }
}
