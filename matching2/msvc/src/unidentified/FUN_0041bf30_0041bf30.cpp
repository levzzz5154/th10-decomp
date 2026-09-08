#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BF30..0x0041BF48: FUN_0041bf30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bf30_0041bf30() {
    __asm {
    L_0041bf30:
        mov eax,dword ptr [ecx+4]
    L_0041bf33:
        mov edx,dword ptr [ecx+8]
    L_0041bf36:
        mov dword ptr [eax+8],edx
    L_0041bf39:
        mov eax,dword ptr [ecx+8]
    L_0041bf3c:
        test eax,eax
    L_0041bf3e:
        je short L_0041bf46
    L_0041bf40:
        mov ecx,dword ptr [ecx+4]
    L_0041bf43:
        mov dword ptr [eax+4],ecx
    L_0041bf46:
        xor eax,eax
    L_0041bf48:
        ret
    }
}
