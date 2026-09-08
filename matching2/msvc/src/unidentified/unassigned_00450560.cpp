#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450560..0x0045057D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00450560() {
    __asm {
    L_00450560:
        push ecx
    L_00450561:
        mov dword ptr [esi+102Ch],eax
    L_00450567:
        call asm_FUN_00450470_00450470
    L_0045056c:
        mov edx,dword ptr [esi+4]
    L_0045056f:
        mov dword ptr [edx+4],eax
    L_00450572:
        mov eax,dword ptr [esi+4]
    L_00450575:
        mov dword ptr [eax],0
    L_0045057b:
        xor eax,eax
    L_0045057d:
        ret
    }
}
