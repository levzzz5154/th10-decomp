#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449A70..0x00449A8F: unassigned code fragment
// BLOCKED (M2703): closest_byte_count=24/32; first_diff=0x00449A78;
// residual_class=compiler scheduling after private-ABI recovery.  A readable
// ResetRecord::Reset member in a native-LTCG caller context did pin the retail
// entry (list object in EAX, child pointer in ECX) and matched 24 of 32 bytes,
// but MSVC hoisted the flags AND ahead of the three zero stores.  Ghidra found
// no xref into 0x00449A70 itself.  The real adjacent unwind topology is
// 0x00465350/0x00465358 -> 0x00449A90 (EAX reset), not this entry.
// variants_tested=field-by-field Reset member standalone (38-byte body),
// native-LTCG member context with the real EAX/ECX entry pair, volatile-field
// order controls, and comma-sequenced stores; every non-overlay variant was
// rejected for extent or instruction scheduling.  The retained body is exact.
// next_lever=an actual 0x00449A70 caller or a distinct compiler scheduling
// lever; the available Unwind callers legally anchor only 0x00449A90.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449a70() {
    __asm {
    L_00449a70:
        mov edx,dword ptr [eax+4]
    L_00449a73:
        mov dword ptr [eax+8],ecx
    L_00449a76:
        xor ecx,ecx
    L_00449a78:
        mov dword ptr [eax+0Ch],ecx
    L_00449a7b:
        mov dword ptr [eax+10h],ecx
    L_00449a7e:
        mov dword ptr [eax],ecx
    L_00449a80:
        and edx,0FFFFFFFEh
    L_00449a83:
        mov dword ptr [eax+4],edx
    L_00449a86:
        mov dword ptr [eax+14h],eax
    L_00449a89:
        mov dword ptr [eax+18h],ecx
    L_00449a8c:
        mov dword ptr [eax+1Ch],ecx
    L_00449a8f:
        ret
    }
}
