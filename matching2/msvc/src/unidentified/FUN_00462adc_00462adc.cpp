#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462ADC..0x00462AFA: FUN_00462adc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462adc_00462adc() {
    __asm {
    L_00462adc:
        push 0FFFFFFFFh
    L_00462ade:
        push eax
    L_00462adf:
        mov eax,dword ptr fs:[0]
    L_00462ae5:
        push eax
    L_00462ae6:
        mov eax,dword ptr [esp+0Ch]
    L_00462aea:
        mov dword ptr fs:[0],esp
    L_00462af1:
        mov dword ptr [esp+0Ch],ebp
    L_00462af5:
        lea ebp,[esp+0Ch]
    L_00462af9:
        push eax
    L_00462afa:
        ret
    }
}
