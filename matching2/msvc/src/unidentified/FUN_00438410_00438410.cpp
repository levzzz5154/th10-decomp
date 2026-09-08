#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438410..0x00438414: FUN_00438410
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00438410_00438410() {
    __asm {
    L_00438410:
        mov eax,ecx
    L_00438412:
        ret 4
    }
}
