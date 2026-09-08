#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452647..0x0045265E: FUN_00452647
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452647_00452647() {
    __asm {
    L_00452647:
        cmp dword ptr [ebp-1Ch],0
    L_0045264b:
        jne short L_0045265e
    L_0045264d:
        push dword ptr [ebp+14h]
    L_00452650:
        push dword ptr [ebp+10h]
    L_00452653:
        push dword ptr [ebp+0Ch]
    L_00452656:
        push dword ptr [ebp+8]
    L_00452659:
        call asm_ArrayUnwind_004525a1
    L_0045265e:
        ret
    }
}
