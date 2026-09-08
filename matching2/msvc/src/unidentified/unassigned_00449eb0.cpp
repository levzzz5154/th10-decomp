#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449EB0..0x00449ECD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449eb0() {
    __asm {
    L_00449eb0:
        push esi
    L_00449eb1:
        mov esi,492254h
    L_00449eb6:
        call asm_Platform_StopWorker_0044c150
    L_00449ebb:
        push edi
    L_00449ebc:
        mov eax,edi
    L_00449ebe:
        call asm_D3DResourceList_ReleaseResources_00449e50
    L_00449ec3:
        lea eax,[edi+24h]
    L_00449ec6:
        push edi
    L_00449ec7:
        call asm_D3DResourceList_ReleaseResources_00449e50
    L_00449ecc:
        pop esi
    L_00449ecd:
        ret
    }
}
