#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413140..0x00413149: FUN_00413140
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413140_00413140() {
    __asm {
    L_00413140:
        mov eax,dword ptr [esp+4]
    L_00413144:
        mov dword ptr [ecx+24h],eax
    L_00413147:
        ret 4
    }
}
