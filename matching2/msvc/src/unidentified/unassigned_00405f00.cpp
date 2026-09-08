#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F00..0x00405F31: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405f00() {
    __asm {
    L_00405f00:
        mov edx,dword ptr [data_00491c10]
    L_00405f06:
        push 46CD88h
    L_00405f0b:
        mov ecx,7
    L_00405f10:
        call asm_Recovery_LoadCachedResource_00447280
    L_00405f15:
        test eax,eax
    L_00405f17:
        jne short L_00405f2f
    L_00405f19:
        push 46CD54h
    L_00405f1e:
        mov ecx,474F70h
    L_00405f23:
        call asm_TextLog_Append_0044b810
    L_00405f28:
        add esp,4
    L_00405f2b:
        or eax,0FFFFFFFFh
    L_00405f2e:
        ret
    L_00405f2f:
        xor eax,eax
    L_00405f31:
        ret
    }
}
