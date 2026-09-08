#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C920..0x0040C928: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c920() {
    __asm {
    L_0040c920:
        mov edx,dword ptr [eax]
    L_0040c922:
        sub edx,ecx
    L_0040c924:
        mov dword ptr [eax],edx
    L_0040c926:
        mov eax,edx
    L_0040c928:
        ret
    }
}
