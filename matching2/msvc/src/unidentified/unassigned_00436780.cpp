#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436780..0x00436790: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436780() {
    __asm {
    L_00436780:
        mov eax,dword ptr [esp+4]
    L_00436784:
        lea edx,[eax+1]
    L_00436787:
        mov cl,byte ptr [eax]
    L_00436789:
        inc eax
    L_0043678a:
        test cl,cl
    L_0043678c:
        jne short L_00436787
    L_0043678e:
        sub eax,edx
    L_00436790:
        ret
    }
}
