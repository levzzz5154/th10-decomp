#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EE01..0x0045EE1C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045ee01() {
    __asm {
    L_0045ee01:
        mov ecx,dword ptr [esp+4]
    L_0045ee05:
        test ecx,ecx
    L_0045ee07:
        je short L_0045ee14
    L_0045ee09:
        dec ecx
    L_0045ee0a:
        cmp byte ptr [eax],0
    L_0045ee0d:
        je short L_0045ee15
    L_0045ee0f:
        inc eax
    L_0045ee10:
        test ecx,ecx
    L_0045ee12:
        jne short L_0045ee09
    L_0045ee14:
        dec ecx
    L_0045ee15:
        mov eax,dword ptr [esp+4]
    L_0045ee19:
        sub eax,ecx
    L_0045ee1b:
        dec eax
    L_0045ee1c:
        ret
    }
}
