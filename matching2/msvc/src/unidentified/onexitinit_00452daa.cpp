#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452DAA..0x00452DD1: ___onexitinit
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_onexitinit_00452daa() {
    __asm {
    L_00452daa:
        push 80h
    L_00452daf:
        call asm_malloc_00452706
    L_00452db4:
        test eax,eax
    L_00452db6:
        pop ecx
    L_00452db7:
        mov dword ptr [data_00499310],eax
    L_00452dbc:
        jne short L_00452dc2
    L_00452dbe:
        push 18h
    L_00452dc0:
        pop eax
    L_00452dc1:
        ret
    L_00452dc2:
        and dword ptr [eax],0
    L_00452dc5:
        mov eax,dword ptr [data_00499310]
    L_00452dca:
        mov dword ptr [data_0049930c],eax
    L_00452dcf:
        xor eax,eax
    L_00452dd1:
        ret
    }
}
