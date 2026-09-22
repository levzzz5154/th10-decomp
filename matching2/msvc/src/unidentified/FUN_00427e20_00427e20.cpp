// BLOCKED (H3101): closest_byte_count=0/23; first_diff=0x00427E20;
// residual_class=three-argument private ABI (result EAX, source EDX,
// destination ECX) plus ESI preservation. Live Ghidra boundary is
// 00427E20..00427E36 and the body copies two dwords through ESI.
// variants_tested=typed free Pair27*(result,source,destination) under
// native LTCG (32-byte stack-argument body, first diff 0x00427E20);
// no readable candidate produced the EAX/EDX/ECX register split.
// next_lever=real coupled caller/callee context that retains the private
// three-register convention while preserving the ESI save/restore.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427E20..0x00427E36: FUN_00427e20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427e20_00427e20() {
    __asm {
    L_00427e20:
        push esi
    L_00427e21:
        mov esi,dword ptr [edx]
    L_00427e23:
        mov dword ptr [ecx],esi
    L_00427e25:
        mov edx,dword ptr [edx+4]
    L_00427e28:
        mov dword ptr [ecx+4],edx
    L_00427e2b:
        mov edx,esi
    L_00427e2d:
        mov dword ptr [eax],edx
    L_00427e2f:
        mov ecx,dword ptr [ecx+4]
    L_00427e32:
        mov dword ptr [eax+4],ecx
    L_00427e35:
        pop esi
    L_00427e36:
        ret
    }
}
