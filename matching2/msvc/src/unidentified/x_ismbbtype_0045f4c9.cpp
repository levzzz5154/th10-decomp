#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F4C9..0x0045F4FB: x_ismbbtype
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_x_ismbbtype_0045f4c9() {
    __asm {
    L_0045f4c9:
        movzx eax,byte ptr [esp+4]
    L_0045f4ce:
        mov cl,byte ptr [esp+0Ch]
    L_0045f4d2:
        test byte ptr [eax+497FA1h],cl
    L_0045f4d8:
        jne short L_0045f4f8
    L_0045f4da:
        cmp dword ptr [esp+8],0
    L_0045f4df:
        je short L_0045f4f1
    L_0045f4e1:
        mov ecx,dword ptr [data_004739d8]
    L_0045f4e7:
        movzx eax,word ptr [ecx+eax*2]
    L_0045f4eb:
        and eax,dword ptr [esp+8]
    L_0045f4ef:
        jmp short L_0045f4f3
    L_0045f4f1:
        xor eax,eax
    L_0045f4f3:
        test eax,eax
    L_0045f4f5:
        jne short L_0045f4f8
    L_0045f4f7:
        ret
    L_0045f4f8:
        xor eax,eax
    L_0045f4fa:
        inc eax
    L_0045f4fb:
        ret
    }
}
