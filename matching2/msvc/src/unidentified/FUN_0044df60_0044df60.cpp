#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF60..0x0044DF66: FUN_0044df60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044df60_0044df60() {
    __asm {
    L_0044df60:
        mov eax,dword ptr [eax+102Ch]
    L_0044df66:
        ret
    }
}
