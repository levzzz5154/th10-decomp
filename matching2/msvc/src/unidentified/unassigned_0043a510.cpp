#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A510..0x0043A532: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a510() {
    __asm {
    L_0043a510:
        mov eax,dword ptr [esi]
    L_0043a512:
        test eax,eax
    L_0043a514:
        jne short L_0043a51a
    L_0043a516:
        or eax,0FFFFFFFFh
    L_0043a519:
        ret
    L_0043a51a:
        push eax
    L_0043a51b:
        call dword ptr [data_004662a8]
    L_0043a521:
        mov eax,dword ptr [esi]
    L_0043a523:
        push eax
    L_0043a524:
        call dword ptr [data_004662a4]
    L_0043a52a:
        mov dword ptr [esi],0
    L_0043a530:
        xor eax,eax
    L_0043a532:
        ret
    }
}
