#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C820..0x0040C824: FUN_0040c820
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c820_0040c820() {
    __asm {
    L_0040c820:
        mov eax,dword ptr [eax+ecx*4+0Ch]
    L_0040c824:
        ret
    }
}
