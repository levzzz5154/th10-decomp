#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CDF0..0x0040CDF3: FUN_0040cdf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cdf0_0040cdf0() {
    __asm {
    L_0040cdf0:
        mov eax,dword ptr [eax+78h]
    L_0040cdf3:
        ret
    }
}
