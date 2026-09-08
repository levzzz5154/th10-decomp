#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AB80..0x0042ABC8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ab80() {
    __asm {
    L_0042ab80:
        mov eax,dword ptr [esi+627Ch]
    L_0042ab86:
        xor ecx,ecx
    L_0042ab88:
        cmp eax,ecx
    L_0042ab8a:
        je short L_0042ab95
    L_0042ab8c:
        mov edx,dword ptr [esi+6280h]
    L_0042ab92:
        mov dword ptr [eax+8],edx
    L_0042ab95:
        mov eax,dword ptr [esi+6280h]
    L_0042ab9b:
        cmp eax,ecx
    L_0042ab9d:
        je short L_0042aba8
    L_0042ab9f:
        mov edx,dword ptr [esi+627Ch]
    L_0042aba5:
        mov dword ptr [eax+4],edx
    L_0042aba8:
        test byte ptr [esp+4],1
    L_0042abad:
        mov dword ptr [esi+627Ch],ecx
    L_0042abb3:
        mov dword ptr [esi+6280h],ecx
    L_0042abb9:
        je short L_0042abc4
    L_0042abbb:
        push esi
    L_0042abbc:
        call asm_free_004524a1
    L_0042abc1:
        add esp,4
    L_0042abc4:
        mov eax,esi
    L_0042abc6:
        ret 4
    }
}
