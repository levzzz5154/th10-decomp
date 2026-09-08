#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402020..0x0040203D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402020() {
    __asm {
    L_00402020:
        mov eax,dword ptr [esi+358h]
    L_00402026:
        test eax,eax
    L_00402028:
        je short L_00402033
    L_0040202a:
        push eax
    L_0040202b:
        call asm_free_00452422
    L_00402030:
        add esp,4
    L_00402033:
        mov dword ptr [esi+358h],0
    L_0040203d:
        ret
    }
}
