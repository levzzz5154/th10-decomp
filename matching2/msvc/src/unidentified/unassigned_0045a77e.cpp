#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A77E..0x0045A7B3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045a77e() {
    __asm {
    L_0045a77e:
        cmp dword ptr [esi],1
    L_0045a781:
        mov ecx,dword ptr [edi]
    L_0045a783:
        push ebx
    L_0045a784:
        jbe short L_0045a79f
    L_0045a786:
        push 0Ah
    L_0045a788:
        cdq
    L_0045a789:
        pop ebx
    L_0045a78a:
        idiv ebx
    L_0045a78c:
        add dl,30h
    L_0045a78f:
        mov byte ptr [ecx],dl
    L_0045a791:
        inc ecx
    L_0045a792:
        dec dword ptr [esi]
    L_0045a794:
        test eax,eax
    L_0045a796:
        mov edx,dword ptr [esi]
    L_0045a798:
        jle short L_0045a79f
    L_0045a79a:
        cmp edx,1
    L_0045a79d:
        ja short L_0045a786
    L_0045a79f:
        mov eax,dword ptr [edi]
    L_0045a7a1:
        mov dword ptr [edi],ecx
    L_0045a7a3:
        dec ecx
    L_0045a7a4:
        mov bl,byte ptr [eax]
    L_0045a7a6:
        mov dl,byte ptr [ecx]
    L_0045a7a8:
        mov byte ptr [ecx],bl
    L_0045a7aa:
        dec ecx
    L_0045a7ab:
        mov byte ptr [eax],dl
    L_0045a7ad:
        inc eax
    L_0045a7ae:
        cmp eax,ecx
    L_0045a7b0:
        jb short L_0045a7a4
    L_0045a7b2:
        pop ebx
    L_0045a7b3:
        ret
    }
}
