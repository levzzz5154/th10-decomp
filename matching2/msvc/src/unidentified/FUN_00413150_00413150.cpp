#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413150..0x00413159: FUN_00413150
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00413150_00413150() {
    __asm {
    L_00413150:
        mov eax,dword ptr [esp+4]
    L_00413154:
        mov dword ptr [ecx+20h],eax
    L_00413157:
        ret 4
    }
}
