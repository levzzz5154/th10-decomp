#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041F780..0x0041F79E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041f780() {
    __asm {
    L_0041f780:
        fld dword ptr [esp+4]
    L_0041f784:
        fmul dword ptr [ecx+8]
    L_0041f787:
        fld dword ptr [esp+4]
    L_0041f78b:
        fmul dword ptr [ecx+4]
    L_0041f78e:
        fld dword ptr [esp+4]
    L_0041f792:
        fmul dword ptr [ecx]
    L_0041f794:
        fstp dword ptr [eax]
    L_0041f796:
        fstp dword ptr [eax+4]
    L_0041f799:
        fstp dword ptr [eax+8]
    L_0041f79c:
        ret 4
    }
}
