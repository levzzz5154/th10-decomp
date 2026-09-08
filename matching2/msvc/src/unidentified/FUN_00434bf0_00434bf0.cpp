#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434BF0..0x00434BFA: FUN_00434bf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00434bf0_00434bf0() {
    __asm {
    L_00434bf0:
        lea eax,[eax+eax*8]
    L_00434bf3:
        mov eax,dword ptr [ecx+eax*4+0B0h]
    L_00434bfa:
        ret
    }
}
