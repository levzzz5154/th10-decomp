#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F6D4..0x0045F714: __get_osfhandle
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_get_osfhandle_0045f6d4() {
    __asm {
    L_0045f6d4:
        mov eax,dword ptr [esp+4]
    L_0045f6d8:
        cmp eax,dword ptr [data_004991e4]
    L_0045f6de:
        jae short L_0045f6fe
    L_0045f6e0:
        mov ecx,eax
    L_0045f6e2:
        and eax,1Fh
    L_0045f6e5:
        sar ecx,5
    L_0045f6e8:
        mov ecx,dword ptr [ecx*4+499200h]
    L_0045f6ef:
        lea eax,[eax+eax*8]
    L_0045f6f2:
        lea eax,[ecx+eax*4]
    L_0045f6f5:
        test byte ptr [eax+4],1
    L_0045f6f9:
        je short L_0045f6fe
    L_0045f6fb:
        mov eax,dword ptr [eax]
    L_0045f6fd:
        ret
    L_0045f6fe:
        call asm_FUN_00456af2_00456af2
    L_0045f703:
        mov dword ptr [eax],9
    L_0045f709:
        call asm_FUN_00456afb_00456afb
    L_0045f70e:
        and dword ptr [eax],0
    L_0045f711:
        or eax,0FFFFFFFFh
    L_0045f714:
        ret
    }
}
