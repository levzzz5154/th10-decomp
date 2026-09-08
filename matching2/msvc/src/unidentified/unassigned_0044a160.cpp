#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044A160..0x0044A18A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044a160() {
    __asm {
    L_0044a160:
        test cx,cx
    L_0044a163:
        jl short L_0044a186
    L_0044a165:
        mov eax,1
    L_0044a16a:
        shl eax,cl
    L_0044a16c:
        and eax,dword ptr [esp+4]
    L_0044a170:
        je short L_0044a177
    L_0044a172:
        movzx ecx,si
    L_0044a175:
        jmp short L_0044a179
    L_0044a177:
        xor ecx,ecx
    L_0044a179:
        or word ptr [edx],cx
    L_0044a17c:
        test eax,eax
    L_0044a17e:
        je short L_0044a186
    L_0044a180:
        movzx eax,si
    L_0044a183:
        ret 4
    L_0044a186:
        xor eax,eax
    L_0044a188:
        ret 4
    }
}
