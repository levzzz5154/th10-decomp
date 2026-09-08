#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00439040..0x0043905A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00439040() {
    __asm {
    L_00439040:
        push esi
    L_00439041:
        call asm_D3DResourceManager_Destroy_00438880
    L_00439046:
        test byte ptr [esp+4],1
    L_0043904b:
        je short L_00439056
    L_0043904d:
        push esi
    L_0043904e:
        call asm_free_004524a1
    L_00439053:
        add esp,4
    L_00439056:
        mov eax,esi
    L_00439058:
        ret 4
    }
}
