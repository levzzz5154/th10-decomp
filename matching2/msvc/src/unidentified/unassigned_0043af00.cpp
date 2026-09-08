#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043AF00..0x0043AF26: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043af00() {
    __asm {
    L_0043af00:
        xor ecx,ecx
    L_0043af02:
        mov dword ptr [eax+2C8h],ecx
    L_0043af08:
        mov dword ptr [eax+2E4h],edx
    L_0043af0e:
        mov dword ptr [eax+2E8h],ecx
    L_0043af14:
        mov dword ptr [eax+2DCh],ecx
    L_0043af1a:
        mov dword ptr [eax+2E0h],1
    L_0043af24:
        xor eax,eax
    L_0043af26:
        ret
    }
}
