#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462525..0x0046253C: FUN_00462525
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462525_00462525() {
    __asm {
    L_00462525:
        push esi
    L_00462526:
        push dword ptr [esp+8]
    L_0046252a:
        mov esi,ecx
    L_0046252c:
        call asm_FID_conflict_runtime_error_00462468
    L_00462531:
        mov dword ptr [esi],46C9F4h
    L_00462537:
        mov eax,esi
    L_00462539:
        pop esi
    L_0046253a:
        ret 4
    }
}
