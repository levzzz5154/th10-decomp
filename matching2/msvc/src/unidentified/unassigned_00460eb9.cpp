#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460EB9..0x00460EE3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00460eb9() {
    __asm {
    L_00460eb9:
        push esi
    L_00460eba:
        call asm_FUN_0045fe7e_0045fe7e
    L_00460ebf:
        mov esi,dword ptr [eax]
    L_00460ec1:
        fninit
    L_00460ec3:
        call asm_setdefaultprecision_0045dfe8
    L_00460ec8:
        test esi,esi
    L_00460eca:
        je short L_00460ee2
    L_00460ecc:
        mov eax,dword ptr [esi+4]
    L_00460ecf:
        test dword ptr [eax],10008h
    L_00460ed5:
        je short L_00460ee2
    L_00460ed7:
        and dword ptr [eax+20h],0
    L_00460edb:
        mov dword ptr [eax+24h],0FFFFh
    L_00460ee2:
        pop esi
    L_00460ee3:
        ret
    }
}
