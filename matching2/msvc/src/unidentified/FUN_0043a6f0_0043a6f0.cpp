#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A6F0..0x0043A6FD: FUN_0043a6f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a6f0_0043a6f0() {
    __asm {
    L_0043a6f0:
        push ecx
    L_0043a6f1:
        mov byte ptr [esp],ah
    L_0043a6f4:
        mov byte ptr [esp+1],al
    L_0043a6f8:
        mov ax,word ptr [esp]
    L_0043a6fc:
        pop ecx
    L_0043a6fd:
        ret
    }
}
