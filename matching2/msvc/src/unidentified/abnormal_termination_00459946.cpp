#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459946..0x00459968: __abnormal_termination
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_abnormal_termination_00459946() {
    __asm {
    L_00459946:
        xor eax,eax
    L_00459948:
        mov ecx,dword ptr fs:[0]
    L_0045994f:
        cmp dword ptr [ecx+4],4598BCh
    L_00459956:
        jne short L_00459968
    L_00459958:
        mov edx,dword ptr [ecx+0Ch]
    L_0045995b:
        mov edx,dword ptr [edx+0Ch]
    L_0045995e:
        cmp dword ptr [ecx+8],edx
    L_00459961:
        jne short L_00459968
    L_00459963:
        mov eax,1
    L_00459968:
        ret
    }
}
