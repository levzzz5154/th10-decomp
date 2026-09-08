#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A6E0..0x0043A6EA: FUN_0043a6e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a6e0_0043a6e0() {
    __asm {
    L_0043a6e0:
        mov ecx,dword ptr [esp+0Ch]
    L_0043a6e4:
        mov eax,dword ptr [ecx]
    L_0043a6e6:
        call dword ptr [eax]
    L_0043a6e8:
        ret 14h
    }
}
