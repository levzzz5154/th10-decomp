#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405360..0x00405363: FUN_00405360
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405360_00405360() {
    __asm {
    L_00405360:
        mov eax,dword ptr [eax+8]
    L_00405363:
        ret
    }
}
