// BLOCKED (M2701): closest_byte_count=0; first_diff=0x0042C8A0;
// residual_class=private ABI: retail multiplies the row in EAX, adds the
// column in ECX, and receives the table pointer on the stack before RET 4.
// variants_tested=extern-C stdcall table/row/column declaration (30-byte
// extent, first diff at byte 0), compiled with the project MSVC 13.10 profile
// and rejected because the declaration cannot preserve the private registers.
// next_lever=native-LTCG context that establishes EAX/ECX as the row/column
// inputs while retaining the stack table argument and exact fixed symbol.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C8A0..0x0042C8B5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042c8a0() {
    __asm {
    L_0042c8a0:
        imul eax,10DFh
    L_0042c8a6:
        add eax,ecx
    L_0042c8a8:
        mov ecx,dword ptr [esp+4]
    L_0042c8ac:
        mov eax,dword ptr [ecx+eax*4+4D0h]
    L_0042c8b3:
        ret 4
    }
}
