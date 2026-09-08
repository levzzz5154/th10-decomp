#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456A8C..0x00456AC3: FUN_00456a8c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00456a8c_00456a8c() {
    __asm {
    L_00456a8c:
        mov eax,45DF97h
    L_00456a91:
        mov dword ptr [data_004739c0],eax
    L_00456a96:
        mov dword ptr [data_004739c4],45DC17h
    L_00456aa0:
        mov dword ptr [data_004739c8],45DC7Ch
    L_00456aaa:
        mov dword ptr [data_004739cc],45DBDBh
    L_00456ab4:
        mov dword ptr [data_004739d0],45DC62h
    L_00456abe:
        mov dword ptr [data_004739d4],eax
    L_00456ac3:
        ret
    }
}
