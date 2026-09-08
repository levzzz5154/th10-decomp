#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041ACA0..0x0041ACA6: FUN_0041aca0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041aca0_0041aca0() {
    __asm {
    L_0041aca0:
        mov eax,dword ptr [eax+45Ch]
    L_0041aca6:
        ret
    }
}
