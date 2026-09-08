#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C520..0x0040C523: FUN_0040c520
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c520_0040c520() {
    __asm {
    L_0040c520:
        mov eax,dword ptr [eax+4]
    L_0040c523:
        ret
    }
}
