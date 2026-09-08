#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449510..0x00449528: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449510() {
    __asm {
    L_00449510:
        mov ecx,dword ptr [eax]
    L_00449512:
        and dword ptr [ecx+35Ch],0FFFFFFFDh
    L_00449519:
        mov ecx,dword ptr [eax]
    L_0044951b:
        or dword ptr [ecx+35Ch],edx
    L_00449521:
        mov eax,dword ptr [eax+4]
    L_00449524:
        test eax,eax
    L_00449526:
        jne short L_00449510
    L_00449528:
        ret
    }
}
