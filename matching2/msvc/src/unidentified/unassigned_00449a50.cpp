#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449A50..0x00449A6F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2702): closest_byte_count=15/32; first_diff=0x00449A51;
// residual_class=private ABI/register allocation: the readable field-by-field
// Reset member matched the operation sequence but used ECX as receiver, while
// retail enters with the object in EAX and keeps the flags word in EDX.
// variants_tested=field-by-field Reset member (17 differing bytes), plus a
// genuinely different real-caller anchor from Ghidra: Unwind@00465350 and
// Unwind@00465358 load EAX from [EBP+4] (the latter adds 0x24) and tail-jump
// to the sibling 0x00449A90 EAX-ABI reset. Those are real callers for the
// adjacent reset family, but Ghidra reports no xref into 0x00449A50 itself,
// so they cannot legally bind this target's entry.
// next_lever=promote this region with the real Unwind ABI anchor in a
// native-LTCG cluster (and re-carve 0x00449A70 separately), or manifest
// semantic migration.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449a50() {
    __asm {
    L_00449a50:
        mov edx,dword ptr [eax+4]
    L_00449a53:
        xor ecx,ecx
    L_00449a55:
        mov dword ptr [eax+8],ecx
    L_00449a58:
        mov dword ptr [eax+0Ch],ecx
    L_00449a5b:
        mov dword ptr [eax+10h],ecx
    L_00449a5e:
        mov dword ptr [eax],ecx
    L_00449a60:
        and edx,0FFFFFFFEh
    L_00449a63:
        mov dword ptr [eax+4],edx
    L_00449a66:
        mov dword ptr [eax+14h],eax
    L_00449a69:
        mov dword ptr [eax+18h],ecx
    L_00449a6c:
        mov dword ptr [eax+1Ch],ecx
    L_00449a6f:
        ret
    }
}
