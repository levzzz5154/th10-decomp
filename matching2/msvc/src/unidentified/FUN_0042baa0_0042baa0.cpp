#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BAA0..0x0042BAAC: FUN_0042baa0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042baa0_0042baa0() {
    __asm {
    L_0042baa0:
        mov eax,dword ptr [esp+4]
    L_0042baa4:
        mov dword ptr [ecx+340h],eax
    L_0042baaa:
        ret 4
    }
}
