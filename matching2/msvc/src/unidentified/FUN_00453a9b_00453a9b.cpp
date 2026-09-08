#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453A9B..0x00453AA0: FUN_00453a9b
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00453a9b_00453a9b() {
    __asm {
    L_00453a9b:
        mov eax,dword ptr [data_00499340]
    L_00453aa0:
        ret
    }
}
