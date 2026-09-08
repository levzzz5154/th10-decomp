#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408880..0x00408894: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408880() {
    __asm {
    L_00408880:
        mov eax,dword ptr [ecx+84h]
    L_00408886:
        cmp eax,1869Fh
    L_0040888b:
        jge short L_00408894
    L_0040888d:
        inc eax
    L_0040888e:
        mov dword ptr [ecx+84h],eax
    L_00408894:
        ret
    }
}
