#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043D670..0x0043D68F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043d670() {
    __asm {
    L_0043d670:
        push 0
    L_0043d672:
        push 0
    L_0043d674:
        call asm_FUN_0044b360_0044b360
    L_0043d679:
        mov ecx,dword ptr [esp+4]
    L_0043d67d:
        xor edx,edx
    L_0043d67f:
        test eax,eax
    L_0043d681:
        setne dl
    L_0043d684:
        mov dword ptr [ecx+1F84h],eax
    L_0043d68a:
        dec edx
    L_0043d68b:
        mov eax,edx
    L_0043d68d:
        ret 4
    }
}
