#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CCF0..0x0043CD28: FUN_0043ccf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043ccf0_0043ccf0() {
    __asm {
    L_0043ccf0:
        mov eax,dword ptr [data_004977b8]
    L_0043ccf5:
        push eax
    L_0043ccf6:
        mov ecx,492590h
    L_0043ccfb:
        call asm_FUN_0043cd30_0043cd30
    L_0043cd00:
        mov eax,dword ptr [data_004977b4]
    L_0043cd05:
        test eax,eax
    L_0043cd07:
        jne short L_0043cd1e
    L_0043cd09:
        push esi
    L_0043cd0a:
        mov esi,dword ptr [data_004660ac]
    L_0043cd10:
        push 1
    L_0043cd12:
        call esi
    L_0043cd14:
        mov eax,dword ptr [data_004977b4]
    L_0043cd19:
        test eax,eax
    L_0043cd1b:
        je short L_0043cd10
    L_0043cd1d:
        pop esi
    L_0043cd1e:
        mov dword ptr [data_004977bc],1
    L_0043cd28:
        ret
    }
}
