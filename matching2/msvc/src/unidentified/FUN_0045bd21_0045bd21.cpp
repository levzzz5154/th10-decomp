#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BD21..0x0045BD26: FUN_0045bd21
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045bd21_0045bd21() {
    __asm {
    L_0045bd21:
        mov eax,dword ptr [data_00473af0]
    L_0045bd26:
        ret
    }
}
