#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF60..0x0041FF75: FUN_0041ff60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ff60_0041ff60() {
    __asm {
    L_0041ff60:
        push esi
    L_0041ff61:
        mov esi,eax
    L_0041ff63:
        add esi,62Ch
    L_0041ff69:
        mov dword ptr [esi],4703E4h
    L_0041ff6f:
        call asm_Platform_StopWorker_0044c150
    L_0041ff74:
        pop esi
    L_0041ff75:
        ret
    }
}
