#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A6B0..0x0043A6D4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a6b0() {
    __asm {
    L_0043a6b0:
        mov eax,dword ptr [esi+4]
    L_0043a6b3:
        test eax,eax
    L_0043a6b5:
        je short L_0043a6be
    L_0043a6b7:
        push eax
    L_0043a6b8:
        call dword ptr [data_00466288]
    L_0043a6be:
        mov eax,dword ptr [esi+8]
    L_0043a6c1:
        push eax
    L_0043a6c2:
        call dword ptr [data_00466274]
    L_0043a6c8:
        mov dword ptr [esi+4],0
    L_0043a6cf:
        mov eax,1
    L_0043a6d4:
        ret
    }
}
