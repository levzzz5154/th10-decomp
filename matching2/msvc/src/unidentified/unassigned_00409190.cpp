#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409190..0x004091BD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00409190() {
    __asm {
    L_00409190:
        test byte ptr [esi+378Ch],1
    L_00409197:
        je short L_004091b8
    L_00409199:
        mov ecx,dword ptr [data_00491c10]
    L_0040919f:
        lea eax,[esi+10h]
    L_004091a2:
        call asm_FUN_004451c0_004451c0
    L_004091a7:
        mov ecx,dword ptr [data_00491c10]
    L_004091ad:
        lea eax,[esi+3BCh]
    L_004091b3:
        call asm_FUN_004451c0_004451c0
    L_004091b8:
        mov eax,1
    L_004091bd:
        ret
    }
}
