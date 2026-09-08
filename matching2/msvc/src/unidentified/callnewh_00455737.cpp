#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455737..0x00455751: __callnewh
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_callnewh_00455737() {
    __asm {
    L_00455737:
        mov eax,dword ptr [data_00477360]
    L_0045573c:
        test eax,eax
    L_0045573e:
        je short L_0045574f
    L_00455740:
        push dword ptr [esp+4]
    L_00455744:
        call eax
    L_00455746:
        test eax,eax
    L_00455748:
        pop ecx
    L_00455749:
        je short L_0045574f
    L_0045574b:
        xor eax,eax
    L_0045574d:
        inc eax
    L_0045574e:
        ret
    L_0045574f:
        xor eax,eax
    L_00455751:
        ret
    }
}
