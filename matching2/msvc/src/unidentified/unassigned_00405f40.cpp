#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F40..0x00405F6E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405f40() {
    __asm {
    L_00405f40:
        push esi
    L_00405f41:
        mov esi,dword ptr [data_00491c10]
    L_00405f47:
        add esi,3AD088h
    L_00405f4d:
        push edi
    L_00405f4e:
        mov edi,dword ptr [esi]
    L_00405f50:
        test edi,edi
    L_00405f52:
        je short L_00405f6a
    L_00405f54:
        call asm_FUN_00447810_00447810
    L_00405f59:
        mov eax,dword ptr [esi]
    L_00405f5b:
        push eax
    L_00405f5c:
        call asm_free_004524a1
    L_00405f61:
        add esp,4
    L_00405f64:
        mov dword ptr [esi],0
    L_00405f6a:
        pop edi
    L_00405f6b:
        xor eax,eax
    L_00405f6d:
        pop esi
    L_00405f6e:
        ret
    }
}
