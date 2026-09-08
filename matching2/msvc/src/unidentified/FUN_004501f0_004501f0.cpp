#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004501F0..0x004501F6: FUN_004501f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004501f0_004501f0() {
    __asm {
    L_004501f0:
        mov ecx,dword ptr [eax+4]
    L_004501f3:
        mov dword ptr [ecx+4],edx
    L_004501f6:
        ret
    }
}
