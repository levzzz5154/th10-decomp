#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401490..0x004014AA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401490() {
    __asm {
    L_00401490:
        push esi
    L_00401491:
        call asm_DestroyGameThread_00401260
    L_00401496:
        test byte ptr [esp+4],1
    L_0040149b:
        je short L_004014a6
    L_0040149d:
        push esi
    L_0040149e:
        call asm_free_004524a1
    L_004014a3:
        add esp,4
    L_004014a6:
        mov eax,esi
    L_004014a8:
        ret 4
    }
}
