#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418A70..0x00418A8E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418a70() {
    __asm {
    L_00418a70:
        mov ecx,dword ptr [eax+1CCh]
    L_00418a76:
        test ecx,ecx
    L_00418a78:
        mov edx,0FFFFFFFDh
    L_00418a7d:
        je short L_00418a82
    L_00418a7f:
        and dword ptr [ecx+4],edx
    L_00418a82:
        mov ecx,dword ptr [eax+0Ch]
    L_00418a85:
        test ecx,ecx
    L_00418a87:
        je short L_00418a8e
    L_00418a89:
        mov eax,ecx
    L_00418a8b:
        and dword ptr [eax+4],edx
    L_00418a8e:
        ret
    }
}
