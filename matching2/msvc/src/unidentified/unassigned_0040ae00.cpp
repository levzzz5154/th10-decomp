#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE00..0x0040AE1B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ae00() {
    __asm {
    L_0040ae00:
        mov ecx,dword ptr [eax+8]
    L_0040ae03:
        test ecx,ecx
    L_0040ae05:
        mov edx,0FFFFFFFDh
    L_0040ae0a:
        je short L_0040ae0f
    L_0040ae0c:
        and dword ptr [ecx+4],edx
    L_0040ae0f:
        mov ecx,dword ptr [eax+0Ch]
    L_0040ae12:
        test ecx,ecx
    L_0040ae14:
        je short L_0040ae1b
    L_0040ae16:
        mov eax,ecx
    L_0040ae18:
        and dword ptr [eax+4],edx
    L_0040ae1b:
        ret
    }
}
