// BLOCKED (2026-09-27): native-LTCG member now emits 81 bytes with the retail
// EAX receiver and every instruction/control-flow offset, but 11 bytes differ:
// old flags use ECX and the shared -3 mask uses EDX; retail swaps those roles.
// First difference is +0x0A (MOV ECX,[EAX+378C] instead of MOV EDX,...).
// Explicit old-flags load before pending-state zeroing fixes the earlier extent
// residual. Member/free/fastcall, signed masks, reversed AND operands and three
// zero-instruction compiler-barrier positions retain the register permutation.
// See recovery_notes/player_clear_flags_00405500_cluster.md and the isolated
// matching2/build/experiments/player_flags reports. No source was promoted.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404530..0x004045A6: FUN_00404530
// Naked body preserves the retail register/stack ABI.

// 0x00405500..0x00405550: Player_ClearExpiredFlagsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_ClearExpiredFlagsRetail_00405500() {
    __asm {
    L_00405500:
        cmp dword ptr [eax+3738h],3Ch
    L_00405507:
        jl short L_00405550
    L_00405509:
        mov edx,dword ptr [eax+378Ch]
    L_0040550f:
        mov dword ptr [eax+3790h],0
    L_00405519:
        mov ecx,0FFFFFFFDh
    L_0040551e:
        and edx,ecx
    L_00405520:
        mov dword ptr [eax+378Ch],edx
    L_00405526:
        and dword ptr [eax+0AD4h],ecx
    L_0040552c:
        and dword ptr [eax+0E80h],ecx
    L_00405532:
        and dword ptr [eax+15D8h],ecx
    L_00405538:
        and dword ptr [eax+1984h],ecx
    L_0040553e:
        and dword ptr [eax+1D30h],ecx
    L_00405544:
        and dword ptr [eax+20DCh],ecx
    L_0040554a:
        and dword ptr [eax+2488h],ecx
    L_00405550:
        ret
    }
}
