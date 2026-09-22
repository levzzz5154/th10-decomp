#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004087A0..0x004087B0: unassigned code fragment
// BLOCKED (M2703): closest_byte_count=14/17; first_diff=0x004087A1;
// residual_class=private ABI/register allocation: the readable member setter
// matches the stores and RET 4, but MSVC 13.10 keeps the receiver in ECX;
// retail receives the object in EAX and the stack value in ECX.  Ghidra has
// no containing function or xrefs from this unresolved fragment.
// variants_tested=natural member setter with explicit +0x2C/+0x35C layout;
// the only mismatch is the receiver/value register allocation at the entry
// and corresponding base registers in both stores.
// next_lever=native-LTCG caller topology that proves the EAX receiver and ECX
// child/value pair without a synthetic ABI signature.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004087a0() {
    __asm {
    L_004087a0:
        mov ecx,dword ptr [esp+4]
    L_004087a4:
        mov dword ptr [eax+2Ch],ecx
    L_004087a7:
        or dword ptr [eax+35Ch],4
    L_004087ae:
        ret 4
    }
}
