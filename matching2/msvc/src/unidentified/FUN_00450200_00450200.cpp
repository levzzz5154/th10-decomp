#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450200..0x00450206: FUN_00450200
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00450200_00450200() {
    __asm {
    L_00450200:
        mov ecx,dword ptr [eax+4]
    L_00450203:
        mov eax,dword ptr [ecx+4]
    L_00450206:
        ret
    }
}
