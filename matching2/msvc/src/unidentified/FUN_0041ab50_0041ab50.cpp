#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AB50..0x0041AB56: FUN_0041ab50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ab50_0041ab50() {
    __asm {
    L_0041ab50:
        mov eax,dword ptr [eax+12Ch]
    L_0041ab56:
        ret
    }
}
