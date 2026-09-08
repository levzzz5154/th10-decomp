#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405E10..0x00405E16: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405e10() {
    __asm {
    L_00405e10:
        mov eax,ecx
    L_00405e12:
        and dword ptr [eax+10h],0FFFFFFFEh
    L_00405e16:
        ret
    }
}
