#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C470..0x0040C47C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c470() {
    __asm {
    L_0040c470:
        mov eax,dword ptr [eax+4]
    L_0040c473:
        cdq
    L_0040c474:
        idiv dword ptr [esp+4]
    L_0040c478:
        mov eax,edx
    L_0040c47a:
        ret 4
    }
}
