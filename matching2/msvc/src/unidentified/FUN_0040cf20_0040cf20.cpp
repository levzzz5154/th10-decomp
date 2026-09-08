#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CF20..0x0040CF29: FUN_0040cf20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cf20_0040cf20() {
    __asm {
    L_0040cf20:
        mov eax,dword ptr [esp+4]
    L_0040cf24:
        mov dword ptr [ecx+48h],eax
    L_0040cf27:
        ret 4
    }
}
