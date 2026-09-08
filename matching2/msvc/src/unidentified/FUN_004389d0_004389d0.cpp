#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004389D0..0x004389D3: FUN_004389d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004389d0_004389d0() {
    __asm {
    L_004389d0:
        mov eax,dword ptr [eax+4]
    L_004389d3:
        ret
    }
}
