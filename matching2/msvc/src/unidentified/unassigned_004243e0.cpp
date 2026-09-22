// BLOCKED (M2901): closest_byte_count=13/16; first_diff=0x004243E1;
// residual_class=private ABI/register allocation: Ghidra disassembles an
// ECX receiver and stack operand, with the receiver word in EDX and operand
// in ECX before the branchless SETNE tail. A readable __thiscall member keeps
// the ABI and extent but allocates those live ranges as ECX/EDX instead.
// variants_tested=exact retail naked wrapper; readable int __thiscall member;
// register-qualified locals; prior bool/int/const/pointer/volatile/member
// and branch-shaped member probes. The readable candidates remain 3 bytes
// different; next_lever=native-LTCG context or semantic manifest migration
// that anchors the retail EDX/ECX live ranges.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004243E0..0x004243EF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004243e0() {
    __asm {
    L_004243e0:
        mov edx,dword ptr [ecx]
    L_004243e2:
        mov ecx,dword ptr [esp+4]
    L_004243e6:
        xor eax,eax
    L_004243e8:
        cmp edx,ecx
    L_004243ea:
        setne al
    L_004243ed:
        ret 4
    }
}
