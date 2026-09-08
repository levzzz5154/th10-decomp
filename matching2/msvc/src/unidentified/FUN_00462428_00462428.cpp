#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462428..0x00462466: FUN_00462428
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462428_00462428() {
    __asm {
    L_00462428:
        mov eax,4651AAh
    L_0046242d:
        call asm_FUN_00462adc_00462adc
    L_00462432:
        sub esp,44h
    L_00462435:
        push 46CA08h
    L_0046243a:
        lea ecx,[ebp-28h]
    L_0046243d:
        call asm_FUN_004624c3_004624c3
    L_00462442:
        and dword ptr [ebp-4],0
    L_00462446:
        lea eax,[ebp-28h]
    L_00462449:
        push eax
    L_0046244a:
        lea ecx,[ebp-50h]
    L_0046244d:
        call asm_FID_conflict_runtime_error_00462327
    L_00462452:
        push 4711BCh
    L_00462457:
        lea eax,[ebp-50h]
    L_0046245a:
        push eax
    L_0046245b:
        mov dword ptr [ebp-50h],46CA00h
    L_00462462:
        call asm_CxxThrowException_8_00462afb
    }
}
