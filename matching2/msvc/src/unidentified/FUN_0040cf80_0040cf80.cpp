#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CF80..0x0040CF8C: FUN_0040cf80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cf80_0040cf80() {
    __asm {
    L_0040cf80:
        mov eax,dword ptr [esp+4]
    L_0040cf84:
        mov dword ptr [ecx+440h],eax
    L_0040cf8a:
        ret 4
    }
}
