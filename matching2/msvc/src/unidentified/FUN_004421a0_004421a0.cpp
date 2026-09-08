#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004421A0..0x004421B0: FUN_004421a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004421a0_004421a0() {
    __asm {
    L_004421a0:
        mov edx,dword ptr [eax]
    L_004421a2:
        mov dword ptr [ecx],edx
    L_004421a4:
        mov edx,dword ptr [eax+4]
    L_004421a7:
        mov dword ptr [ecx+4],edx
    L_004421aa:
        mov eax,dword ptr [eax+8]
    L_004421ad:
        mov dword ptr [ecx+8],eax
    L_004421b0:
        ret
    }
}
