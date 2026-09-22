#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404E90..0x00404EA0: unassigned code fragment
// BLOCKED (M2703): closest_byte_count=14/17; first_diff=0x00404E91;
// residual_class=private ABI/register allocation: a readable member compare
// preserves the object in ECX but MSVC 13.10 loads +4 into ECX and the stack
// threshold into EDX, while retail loads +4 into EDX and then overwrites ECX
// with the threshold.  The native body remains the exact ABI overlay.
// variants_tested=member compare, reversed relational spelling, explicit
// temporaries, volatile field, bool return, and __fastcall receiver forms;
// all compiled to the same 3-byte register-allocation delta.
// next_lever=an actual caller/context that exposes the retail ECX/EDX order;
// Ghidra reports no function or xrefs at this unresolved fragment.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404e90() {
    __asm {
    L_00404e90:
        mov edx,dword ptr [ecx+4]
    L_00404e93:
        mov ecx,dword ptr [esp+4]
    L_00404e97:
        xor eax,eax
    L_00404e99:
        cmp edx,ecx
    L_00404e9b:
        setge al
    L_00404e9e:
        ret 4
    }
}
