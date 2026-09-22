// BLOCKED (D3407): closest_byte_count=0/81; first_diff=extent (best readable member candidate emitted 89 bytes vs retail 81 before byte comparison);
// residual_class=private-ABI/cluster; the retail function receives and returns its player object in EAX,
// while standalone MSVC member compilation uses ECX and schedules the value_3790 store after the flag chain.
// variants_tested=retail naked baseline (81/81 exact), readable nonvolatile padded member (89 bytes),
// readable volatile padded member (144 bytes), live Ghidra FUN_00405500 pseudocode, and exact probe;
// next_lever=native-LTCG cluster with initialize_player_00405860 as the real EAX caller and a semantic region classification.

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
