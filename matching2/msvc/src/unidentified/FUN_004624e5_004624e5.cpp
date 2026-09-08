#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004624E5..0x00462523: FUN_004624e5
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004624e5_004624e5() {
    __asm {
    L_004624e5:
        mov eax,4651CEh
    L_004624ea:
        call asm_FUN_00462adc_00462adc
    L_004624ef:
        sub esp,44h
    L_004624f2:
        push 46CA20h
    L_004624f7:
        lea ecx,[ebp-28h]
    L_004624fa:
        call asm_FUN_004624c3_004624c3
    L_004624ff:
        and dword ptr [ebp-4],0
    L_00462503:
        lea eax,[ebp-28h]
    L_00462506:
        push eax
    L_00462507:
        lea ecx,[ebp-50h]
    L_0046250a:
        call asm_FID_conflict_runtime_error_00462327
    L_0046250f:
        push 471240h
    L_00462514:
        lea eax,[ebp-50h]
    L_00462517:
        push eax
    L_00462518:
        mov dword ptr [ebp-50h],46C9F4h
    L_0046251f:
        call asm_CxxThrowException_8_00462afb
    }
}
