#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004623AA..0x004623C1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004623aa() {
    __asm {
    L_004623aa:
        push esi
    L_004623ab:
        push dword ptr [esp+8]
    L_004623af:
        mov esi,ecx
    L_004623b1:
        call asm_FID_conflict_runtime_error_00462327
    L_004623b6:
        mov dword ptr [esi],46C9F4h
    L_004623bc:
        mov eax,esi
    L_004623be:
        pop esi
    L_004623bf:
        ret 4
    }
}
