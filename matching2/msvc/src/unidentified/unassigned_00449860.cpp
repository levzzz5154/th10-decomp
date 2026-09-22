#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449860..0x00449869: unassigned code fragment.  Ghidra reports no
// function boundary, callers, callees, xrefs, or dataflow at this address.
// BLOCKED: closest_byte_count=9/10; first_diff=0x00449861; residual_class=
// private register ABI (retail enters with the first pointer in EAX and the
// second in ECX, while MSVC __fastcall uses ECX and EDX); variants_tested=
// readable pointer equality with __fastcall, which matched the final 8 bytes
// but emitted MOV EAX,[ECX]/SUB EAX,[EDX]; next_lever=caller/context evidence
// establishing the nonstandard EAX/ECX entry convention.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449860() {
    __asm {
    L_00449860:
        mov eax,dword ptr [eax]
    L_00449862:
        sub eax,dword ptr [ecx]
    L_00449864:
        neg eax
    L_00449866:
        sbb eax,eax
    L_00449868:
        inc eax
    L_00449869:
        ret
    }
}
