#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF20..0x0044DF2A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044df20() {
    __asm {
    L_0044df20:
        mov eax,dword ptr [ecx+1004h]
    L_0044df26:
        add eax,edx
    L_0044df28:
        add eax,ecx
    L_0044df2a:
        ret
    }
}
