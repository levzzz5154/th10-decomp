#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F7B5..0x0045F7D6: FUN_0045f7b5
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045f7b5_0045f7b5() {
    __asm {
    L_0045f7b5:
        mov eax,dword ptr [esp+4]
    L_0045f7b9:
        mov ecx,eax
    L_0045f7bb:
        and eax,1Fh
    L_0045f7be:
        sar ecx,5
    L_0045f7c1:
        mov ecx,dword ptr [ecx*4+499200h]
    L_0045f7c8:
        lea eax,[eax+eax*8]
    L_0045f7cb:
        lea eax,[ecx+eax*4+0Ch]
    L_0045f7cf:
        push eax
    L_0045f7d0:
        call dword ptr [data_004660b4]
    L_0045f7d6:
        ret
    }
}
