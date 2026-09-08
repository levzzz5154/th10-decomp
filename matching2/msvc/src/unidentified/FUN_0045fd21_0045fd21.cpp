#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FD21..0x0045FD31: FUN_0045fd21
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045fd21_0045fd21() {
    __asm {
    L_0045fd21:
        mov eax,dword ptr [data_004981d4]
    L_0045fd26:
        push dword ptr [eax+esi*4]
    L_0045fd29:
        push esi
    L_0045fd2a:
        call asm_unlock_file2_0045a0eb
    L_0045fd2f:
        pop ecx
    L_0045fd30:
        pop ecx
    L_0045fd31:
        ret
    }
}
