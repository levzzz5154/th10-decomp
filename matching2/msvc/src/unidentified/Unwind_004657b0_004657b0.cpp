#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004657B0..0x004657BA: Unwind@004657b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Unwind_004657b0_004657b0() {
    __asm {
    L_004657b0:
        mov eax,dword ptr [ebp+4]
    L_004657b3:
        push eax
    L_004657b4:
        call asm_free_004524a1
    L_004657b9:
        pop ecx
    L_004657ba:
        ret
    }
}
