#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE40..0x0040CE49: FUN_0040ce40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ce40_0040ce40() {
    __asm {
    L_0040ce40:
        mov ecx,dword ptr [eax+9EB8h]
    L_0040ce46:
        mov eax,dword ptr [ecx+78h]
    L_0040ce49:
        ret
    }
}
