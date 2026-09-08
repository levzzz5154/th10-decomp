#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434B50..0x00434B5F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00434b50() {
    __asm {
    L_00434b50:
        mov edx,dword ptr [ecx]
    L_00434b52:
        mov ecx,dword ptr [esp+4]
    L_00434b56:
        xor eax,eax
    L_00434b58:
        cmp edx,ecx
    L_00434b5a:
        setg al
    L_00434b5d:
        ret 4
    }
}
