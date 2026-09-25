#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465A30..0x00465A46: FUN_00465a30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00465a30_00465a30() {
    __asm {
    L_00465a30:
        push esi
    L_00465a31:
        mov esi,474DD4h
    L_00465a36:
        mov dword ptr [data_00474dd4],4703E4h
    L_00465a40:
        call asm_Platform_StopWorker_0044c150
    L_00465a45:
        pop esi
    L_00465a46:
        ret
    }
}
