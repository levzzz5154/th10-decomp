#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004623E9..0x00462400: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004623e9() {
    __asm {
    L_004623e9:
        push esi
    L_004623ea:
        push dword ptr [esp+8]
    L_004623ee:
        mov esi,ecx
    L_004623f0:
        call asm_FID_conflict_runtime_error_00462327
    L_004623f5:
        mov dword ptr [esi],46CA00h
    L_004623fb:
        mov eax,esi
    L_004623fd:
        pop esi
    L_004623fe:
        ret 4
    }
}
