#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AB00..0x0041AB0E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041ab00() {
    __asm {
    L_0041ab00:
        mov ecx,dword ptr [eax+44h]
    L_0041ab03:
        test ecx,ecx
    L_0041ab05:
        je short L_0041ab0b
    L_0041ab07:
        mov eax,dword ptr [eax+4Ch]
    L_0041ab0a:
        ret
    L_0041ab0b:
        mov eax,dword ptr [eax+48h]
    L_0041ab0e:
        ret
    }
}
