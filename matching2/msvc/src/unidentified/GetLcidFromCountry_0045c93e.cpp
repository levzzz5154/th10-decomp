#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C93E..0x0045C974: _GetLcidFromCountry
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GetLcidFromCountry_0045c93e() {
    __asm {
    L_0045c93e:
        push dword ptr [data_0047763c]
    L_0045c944:
        call asm_strlen_00456720
    L_0045c949:
        sub eax,3
    L_0045c94c:
        neg eax
    L_0045c94e:
        pop ecx
    L_0045c94f:
        sbb eax,eax
    L_0045c951:
        push 1
    L_0045c953:
        inc eax
    L_0045c954:
        push 45C544h
    L_0045c959:
        mov dword ptr [data_00477638],eax
    L_0045c95e:
        call dword ptr [data_00466058]
    L_0045c964:
        test byte ptr [data_00477628],4
    L_0045c96b:
        jne short L_0045c974
    L_0045c96d:
        and dword ptr [data_00477628],0
    L_0045c974:
        ret
    }
}
