#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C960..0x0040C970: FUN_0040c960
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c960_0040c960() {
    __asm {
    L_0040c960:
        mov ecx,dword ptr [esp+4]
    L_0040c964:
        mov edx,dword ptr [esp+8]
    L_0040c968:
        mov dword ptr [eax+34h],ecx
    L_0040c96b:
        mov dword ptr [eax+38h],edx
    L_0040c96e:
        ret 8
    }
}
