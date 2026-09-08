#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435300..0x00435314: FUN_00435300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00435300_00435300() {
    __asm {
    L_00435300:
        mov dword ptr [eax],46F230h
    L_00435306:
        mov dword ptr [eax+4],0FFFFFFFFh
    L_0043530d:
        mov dword ptr [eax+8],0
    L_00435314:
        ret
    }
}
