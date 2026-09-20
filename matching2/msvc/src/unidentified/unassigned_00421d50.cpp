#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421D50..0x00421D6A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2701): closest_byte_count=27/27; first_diff=unmeasured;
// residual_class=abi/cluster: this deleting-destructor-style fragment enters
// with the object in ESI, dispatches through the vtable release slot (+8),
// clears the 0x3ADA74 field, and owns a bare RET.
// variants_tested=member Release/Clear model and exact retail wrapper; a
// declaration-visible thiscall cannot preserve the ESI receiver convention.
// next_lever=native-LTCG destructor cluster preserving ESI and the indirect
// vtable call/clear sequence; retain this exact wrapper meanwhile.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421d50() {
    __asm {
    L_00421d50:
        mov eax,dword ptr [esi+3ADA74h]
    L_00421d56:
        test eax,eax
    L_00421d58:
        je short L_00421d6a
    L_00421d5a:
        mov ecx,dword ptr [eax]
    L_00421d5c:
        push eax
    L_00421d5d:
        call dword ptr [ecx+8]
    L_00421d60:
        mov dword ptr [esi+3ADA74h],0
    L_00421d6a:
        ret
    }
}
