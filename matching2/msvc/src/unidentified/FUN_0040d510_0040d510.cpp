#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D510..0x0040D52B: FUN_0040d510
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d510_0040d510() {
    __asm {
    L_0040d510:
        mov ecx,dword ptr [eax+8]
    L_0040d513:
        test ecx,ecx
    L_0040d515:
        mov edx,2
    L_0040d51a:
        je short L_0040d51f
    L_0040d51c:
        or dword ptr [ecx+4],edx
    L_0040d51f:
        mov ecx,dword ptr [eax+0Ch]
    L_0040d522:
        test ecx,ecx
    L_0040d524:
        je short L_0040d52b
    L_0040d526:
        mov eax,ecx
    L_0040d528:
        or dword ptr [eax+4],edx
    L_0040d52b:
        ret
    }
}
