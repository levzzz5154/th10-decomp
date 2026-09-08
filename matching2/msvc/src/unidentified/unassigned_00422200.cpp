#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422200..0x0042221B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00422200() {
    __asm {
    L_00422200:
        mov ecx,dword ptr [eax+8]
    L_00422203:
        test ecx,ecx
    L_00422205:
        mov edx,2
    L_0042220a:
        je short L_0042220f
    L_0042220c:
        or dword ptr [ecx+4],edx
    L_0042220f:
        mov ecx,dword ptr [eax+0Ch]
    L_00422212:
        test ecx,ecx
    L_00422214:
        je short L_0042221b
    L_00422216:
        mov eax,ecx
    L_00422218:
        or dword ptr [eax+4],edx
    L_0042221b:
        ret
    }
}
