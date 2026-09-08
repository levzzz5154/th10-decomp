#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CD10..0x0045CD55: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045cd10() {
    __asm {
    L_0045cd10:
        and dword ptr [data_00477690],0
    L_0045cd17:
        cmp eax,0FFFFFFFEh
    L_0045cd1a:
        jne short L_0045cd2c
    L_0045cd1c:
        mov dword ptr [data_00477690],1
    L_0045cd26:
        jmp dword ptr [data_00466048]
    L_0045cd2c:
        cmp eax,0FFFFFFFDh
    L_0045cd2f:
        jne short L_0045cd41
    L_0045cd31:
        mov dword ptr [data_00477690],1
    L_0045cd3b:
        jmp dword ptr [data_0046604c]
    L_0045cd41:
        cmp eax,0FFFFFFFCh
    L_0045cd44:
        jne short L_0045cd55
    L_0045cd46:
        mov eax,dword ptr [data_00477664]
    L_0045cd4b:
        mov dword ptr [data_00477690],1
    L_0045cd55:
        ret
    }
}
