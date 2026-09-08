#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408860..0x00408874: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408860() {
    __asm {
    L_00408860:
        mov eax,dword ptr [ecx+80h]
    L_00408866:
        cmp eax,1869Fh
    L_0040886b:
        jge short L_00408874
    L_0040886d:
        inc eax
    L_0040886e:
        mov dword ptr [ecx+80h],eax
    L_00408874:
        ret
    }
}
