#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412D50..0x00412D53: FUN_00412d50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412d50_00412d50() {
    __asm {
    L_00412d50:
        mov dword ptr [ecx+38h],eax
    L_00412d53:
        ret
    }
}
