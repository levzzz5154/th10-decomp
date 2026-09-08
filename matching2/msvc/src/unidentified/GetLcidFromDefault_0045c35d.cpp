#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C35D..0x0045C376: _GetLcidFromDefault
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GetLcidFromDefault_0045c35d() {
    __asm {
    L_0045c35d:
        or word ptr [data_00477628],104h
    L_0045c366:
        call dword ptr [data_00466060]
    L_0045c36c:
        mov dword ptr [data_00477630],eax
    L_0045c371:
        mov dword ptr [data_0047762c],eax
    L_0045c376:
        ret
    }
}
