#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004624AB..0x004624C2: FUN_004624ab
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004624ab_004624ab() {
    __asm {
    L_004624ab:
        push esi
    L_004624ac:
        push dword ptr [esp+8]
    L_004624b0:
        mov esi,ecx
    L_004624b2:
        call asm_FID_conflict_runtime_error_00462468
    L_004624b7:
        mov dword ptr [esi],46CA00h
    L_004624bd:
        mov eax,esi
    L_004624bf:
        pop esi
    L_004624c0:
        ret 4
    }
}
