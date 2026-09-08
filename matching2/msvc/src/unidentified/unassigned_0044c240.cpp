#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C240..0x0044C24E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c240() {
    __asm {
    L_0044c240:
        mov eax,dword ptr [eax+4]
    L_0044c243:
        test eax,eax
    L_0044c245:
        je short L_0044c24e
    L_0044c247:
        push eax
    L_0044c248:
        call dword ptr [data_00466130]
    L_0044c24e:
        ret
    }
}
