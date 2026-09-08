#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436840..0x00436846: FUN_00436840
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436840_00436840() {
    __asm {
    L_00436840:
        mov eax,dword ptr [eax+104h]
    L_00436846:
        ret
    }
}
