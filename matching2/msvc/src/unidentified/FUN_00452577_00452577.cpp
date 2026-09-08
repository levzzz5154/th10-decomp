#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452577..0x0045258E: FUN_00452577
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452577_00452577() {
    __asm {
    L_00452577:
        cmp dword ptr [ebp-20h],0
    L_0045257b:
        jne short L_0045258e
    L_0045257d:
        push dword ptr [ebp+18h]
    L_00452580:
        push dword ptr [ebp-1Ch]
    L_00452583:
        push dword ptr [ebp+0Ch]
    L_00452586:
        push dword ptr [ebp+8]
    L_00452589:
        call asm_ArrayUnwind_004525a1
    L_0045258e:
        ret
    }
}
