#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450210..0x0045021B: FUN_00450210
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00450210_00450210() {
    __asm {
    L_00450210:
        mov ecx,dword ptr [eax+4]
    L_00450213:
        mov edx,dword ptr [esp+4]
    L_00450217:
        mov dword ptr [ecx],edx
    L_00450219:
        ret 4
    }
}
