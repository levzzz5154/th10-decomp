#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427AD0..0x00427ADB: FUN_00427ad0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427ad0_00427ad0() {
    __asm {
    L_00427ad0:
        push edi
    L_00427ad1:
        mov edi,ecx
    L_00427ad3:
        call asm_Recovery_SwitchPlaybackState_00427ae0
    L_00427ad8:
        xor eax,eax
    L_00427ada:
        pop edi
    L_00427adb:
        ret
    }
}
