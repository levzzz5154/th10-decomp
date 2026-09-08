#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE20..0x0040AE2B: FUN_0040ae20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ae20_0040ae20() {
    __asm {
    L_0040ae20:
        mov edx,dword ptr [eax+ecx*4+3AD06Ch]
    L_0040ae27:
        jmp asm_AnimationManager_MarkResourceForRemoval_004493e0
    }
}
