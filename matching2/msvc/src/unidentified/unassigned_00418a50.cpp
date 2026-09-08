#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418A50..0x00418A60: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418a50() {
    __asm {
    L_00418a50:
        mov edx,dword ptr [ecx+4]
    L_00418a53:
        mov ecx,dword ptr [esp+4]
    L_00418a57:
        xor eax,eax
    L_00418a59:
        cmp edx,ecx
    L_00418a5b:
        sete al
    L_00418a5e:
        ret 4
    }
}
