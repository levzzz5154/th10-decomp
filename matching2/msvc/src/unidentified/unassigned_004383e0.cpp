#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004383E0..0x004383ED: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004383e0() {
    __asm {
    L_004383e0:
        cmp dword ptr [ecx+18h],10h
    L_004383e4:
        jb short L_004383ea
    L_004383e6:
        mov eax,dword ptr [ecx+4]
    L_004383e9:
        ret
    L_004383ea:
        lea eax,[ecx+4]
    L_004383ed:
        ret
    }
}
