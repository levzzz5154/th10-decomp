#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441E90..0x00441EB2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441e90() {
    __asm {
    L_00441e90:
        mov edx,dword ptr [edi+4]
    L_00441e93:
        push ebx
    L_00441e94:
        mov ebx,dword ptr [edi+8]
    L_00441e97:
        push esi
    L_00441e98:
        mov esi,ecx
    L_00441e9a:
        mov ecx,dword ptr [esi+4]
    L_00441e9d:
        add ecx,edx
    L_00441e9f:
        mov edx,dword ptr [esi+8]
    L_00441ea2:
        mov esi,dword ptr [esi]
    L_00441ea4:
        add edx,ebx
    L_00441ea6:
        add esi,dword ptr [edi]
    L_00441ea8:
        mov dword ptr [eax],esi
    L_00441eaa:
        pop esi
    L_00441eab:
        mov dword ptr [eax+4],ecx
    L_00441eae:
        mov dword ptr [eax+8],edx
    L_00441eb1:
        pop ebx
    L_00441eb2:
        ret
    }
}
