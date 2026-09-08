#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C800..0x0042C82C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042c800() {
    __asm {
    L_0042c800:
        push esi
    L_0042c801:
        mov esi,dword ptr [data_00491c10]
    L_0042c807:
        add esi,3AD070h
    L_0042c80d:
        push edi
    L_0042c80e:
        mov edi,dword ptr [esi]
    L_0042c810:
        test edi,edi
    L_0042c812:
        je short L_0042c82a
    L_0042c814:
        call asm_FUN_00447810_00447810
    L_0042c819:
        mov eax,dword ptr [esi]
    L_0042c81b:
        push eax
    L_0042c81c:
        call asm_free_004524a1
    L_0042c821:
        add esp,4
    L_0042c824:
        mov dword ptr [esi],0
    L_0042c82a:
        pop edi
    L_0042c82b:
        pop esi
    L_0042c82c:
        ret
    }
}
