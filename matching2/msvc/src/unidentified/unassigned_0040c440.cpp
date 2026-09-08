#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C440..0x0040C457: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040c440() {
    __asm {
    L_0040c440:
        push esi
    L_0040c441:
        mov esi,eax
    L_0040c443:
        add esi,89A4h
    L_0040c449:
        mov eax,esi
    L_0040c44b:
        call asm_FUN_00409e50_00409e50
    L_0040c450:
        mov dword ptr [esi],0
    L_0040c456:
        pop esi
    L_0040c457:
        ret
    }
}
