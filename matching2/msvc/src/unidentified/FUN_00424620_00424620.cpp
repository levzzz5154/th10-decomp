#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424620..0x00424638: FUN_00424620
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424620_00424620() {
    __asm {
    L_00424620:
        mov dword ptr [ecx+332Ch],eax
    L_00424626:
        mov dword ptr [ecx+33C4h],eax
    L_0042462c:
        mov dword ptr [ecx+345Ch],eax
    L_00424632:
        mov dword ptr [ecx+34F4h],eax
    L_00424638:
        ret
    }
}
