#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462371..0x0046238D: FUN_00462371
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462371_00462371() {
    __asm {
    L_00462371:
        push esi
    L_00462372:
        mov esi,ecx
    L_00462374:
        push 0
    L_00462376:
        push 1
    L_00462378:
        lea ecx,[esi+0Ch]
    L_0046237b:
        mov dword ptr [esi],46C9E8h
    L_00462381:
        call asm_Reserve_LegacyString_00438380
    L_00462386:
        mov ecx,esi
    L_00462388:
        pop esi
    L_00462389:
        jmp asm_exception_00462cac
    }
}
