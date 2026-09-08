#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462C01..0x00462C11: exception
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_exception_00462c01() {
    __asm {
    L_00462c01:
        mov eax,ecx
    L_00462c03:
        and dword ptr [eax+4],0
    L_00462c07:
        and dword ptr [eax+8],0
    L_00462c0b:
        mov dword ptr [eax],46CA68h
    L_00462c11:
        ret
    }
}
