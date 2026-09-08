#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405280..0x00405290: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405280() {
    __asm {
    L_00405280:
        mov edx,dword ptr [ecx+4]
    L_00405283:
        mov ecx,dword ptr [esp+4]
    L_00405287:
        xor eax,eax
    L_00405289:
        cmp edx,ecx
    L_0040528b:
        setle al
    L_0040528e:
        ret 4
    }
}
