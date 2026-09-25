#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C080..0x0044C0A3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c080() {
    __asm {
    L_0044c080:
        push esi
    L_0044c081:
        mov esi,edx
    L_0044c083:
        and esi,1
    L_0044c086:
        sub edx,esi
    L_0044c088:
        xor eax,eax
    L_0044c08a:
        test edx,edx
    L_0044c08c:
        jle short L_0044c0a2
    L_0044c08e:
        lea esi,[edx-1]
    L_0044c091:
        shr esi,1
    L_0044c093:
        inc esi
    L_0044c094:
        mov dl,byte ptr [ecx]
    L_0044c096:
        add dl,al
    L_0044c098:
        add ecx,2
    L_0044c09b:
        dec esi
    L_0044c09c:
        movzx ax,dl
    L_0044c0a0:
        jne short L_0044c094
    L_0044c0a2:
        pop esi
    L_0044c0a3:
        ret
    }
}
