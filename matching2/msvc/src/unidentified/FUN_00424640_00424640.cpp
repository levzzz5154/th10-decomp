#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424640..0x00424643: FUN_00424640
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424640_00424640() {
    __asm {
    L_00424640:
        mov eax,dword ptr [eax+4]
    L_00424643:
        ret
    }
}
