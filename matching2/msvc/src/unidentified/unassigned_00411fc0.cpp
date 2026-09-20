// BLOCKED (H2601): closest_byte_count=616; first_diff=unmeasured;
// residual_class=structural: absolute jump-table layout plus mixed return ABI:
// this ownerless fragment dispatches through 0x00412228 and its leaves
// alternate integer, float, and integer-to-float results while consuming
// ECX/global state; a normal C++ switch cannot place that table at the retail
// boundary;
// variants_tested=exact retail naked wrapper, accessor-family semantic reading,
// and paired comparison with the sibling 0x00412350 dispatch fragment;
// next_lever=co-compile an address-pinned 0x00412228 jump-table anchor with
// both dispatch fragments and the real ECL caller context.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00411FC0..0x00412227: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00411fc0() {
    __asm {
    L_00411fc0:
        mov eax,dword ptr [esp+4]
    L_00411fc4:
        add eax,2710h
    L_00411fc9:
        cmp eax,32h
    L_00411fcc:
        ja asm_target_00412223
    L_00411fd2:
        jmp dword ptr [eax*4+412228h]
    L_00411fd9:
        mov ecx,4918B0h
    L_00411fde:
        call asm_Rng_NextU32_0044b9e0
    L_00411fe3:
        ret 4
    L_00411fe6:
        mov ecx,4918B0h
    L_00411feb:
        call asm_Rng_NextFloat_0044bb20
    L_00411ff0:
        call asm_FUN_00463b2c_00463b2c
    L_00411ff5:
        ret 4
    L_00411ff8:
        mov ecx,4918B0h
    L_00411ffd:
        call asm_Rng_NextFloatSigned_0044bb90
    L_00412002:
        call asm_FUN_00463b2c_00463b2c
    L_00412007:
        ret 4
    L_0041200a:
        mov eax,dword ptr [data_00477834]
    L_0041200f:
        fld dword ptr [eax+3C0h]
    L_00412015:
        call asm_FUN_00463b2c_00463b2c
    L_0041201a:
        ret 4
    L_0041201d:
        mov ecx,dword ptr [data_00477834]
    L_00412023:
        fld dword ptr [ecx+3C4h]
    L_00412029:
        call asm_FUN_00463b2c_00463b2c
    L_0041202e:
        ret 4
    L_00412031:
        mov eax,dword ptr [ecx+115Ch]
    L_00412037:
        ret 4
    L_0041203a:
        xor eax,eax
    L_0041203c:
        mov al,byte ptr [ecx+2482h]
    L_00412042:
        and eax,1
    L_00412045:
        ret 4
    L_00412048:
        mov eax,dword ptr [ecx+1138h]
    L_0041204e:
        ret 4
    L_00412051:
        mov eax,dword ptr [ecx+113Ch]
    L_00412057:
        ret 4
    L_0041205a:
        mov eax,dword ptr [ecx+1140h]
    L_00412060:
        ret 4
    L_00412063:
        mov eax,dword ptr [ecx+1144h]
    L_00412069:
        ret 4
    L_0041206c:
        fld dword ptr [ecx+1148h]
    L_00412072:
        call asm_FUN_00463b2c_00463b2c
    L_00412077:
        ret 4
    L_0041207a:
        fld dword ptr [ecx+114Ch]
    L_00412080:
        call asm_FUN_00463b2c_00463b2c
    L_00412085:
        ret 4
    L_00412088:
        fld dword ptr [ecx+1150h]
    L_0041208e:
        call asm_FUN_00463b2c_00463b2c
    L_00412093:
        ret 4
    L_00412096:
        fld dword ptr [ecx+1154h]
    L_0041209c:
        call asm_FUN_00463b2c_00463b2c
    L_004120a1:
        ret 4
    L_004120a4:
        fld dword ptr [ecx+1068h]
    L_004120aa:
        call asm_FUN_00463b2c_00463b2c
    L_004120af:
        ret 4
    L_004120b2:
        fld dword ptr [ecx+1094h]
    L_004120b8:
        call asm_FUN_00463b2c_00463b2c
    L_004120bd:
        ret 4
    L_004120c0:
        fld dword ptr [ecx+1098h]
    L_004120c6:
        call asm_FUN_00463b2c_00463b2c
    L_004120cb:
        ret 4
    L_004120ce:
        fld dword ptr [ecx+10C0h]
    L_004120d4:
        call asm_FUN_00463b2c_00463b2c
    L_004120d9:
        ret 4
    L_004120dc:
        fld dword ptr [ecx+10C4h]
    L_004120e2:
        call asm_FUN_00463b2c_00463b2c
    L_004120e7:
        ret 4
    L_004120ea:
        fld dword ptr [ecx+10B0h]
    L_004120f0:
        call asm_FUN_00463b2c_00463b2c
    L_004120f5:
        ret 4
    L_004120f8:
        fld dword ptr [ecx+10DCh]
    L_004120fe:
        call asm_FUN_00463b2c_00463b2c
    L_00412103:
        ret 4
    L_00412106:
        fld dword ptr [ecx+1078h]
    L_0041210c:
        fld dword ptr [ecx+1074h]
    L_00412112:
        fpatan
    L_00412114:
        call asm_FUN_00463b2c_00463b2c
    L_00412119:
        ret 4
    L_0041211c:
        fld dword ptr [ecx+10ACh]
    L_00412122:
        call asm_FUN_00463b2c_00463b2c
    L_00412127:
        ret 4
    L_0041212a:
        fld dword ptr [ecx+10D8h]
    L_00412130:
        call asm_FUN_00463b2c_00463b2c
    L_00412135:
        ret 4
    L_00412138:
        fld dword ptr [ecx+10B4h]
    L_0041213e:
        call asm_FUN_00463b2c_00463b2c
    L_00412143:
        ret 4
    L_00412146:
        fld dword ptr [ecx+10E0h]
    L_0041214c:
        call asm_FUN_00463b2c_00463b2c
    L_00412151:
        ret 4
    L_00412154:
        mov edx,dword ptr [data_00477834]
    L_0041215a:
        fld dword ptr [edx+3C0h]
    L_00412160:
        call asm_FUN_00463b2c_00463b2c
    L_00412165:
        ret 4
    L_00412168:
        mov eax,dword ptr [data_00477834]
    L_0041216d:
        fld dword ptr [eax+3C4h]
    L_00412173:
        call asm_FUN_00463b2c_00463b2c
    L_00412178:
        ret 4
    L_0041217b:
        mov ecx,dword ptr [data_00477704]
    L_00412181:
        mov edx,dword ptr [ecx+10h]
    L_00412184:
        fld dword ptr [edx+1068h]
    L_0041218a:
        call asm_FUN_00463b2c_00463b2c
    L_0041218f:
        ret 4
    L_00412192:
        mov eax,dword ptr [data_00477704]
    L_00412197:
        mov ecx,dword ptr [eax+10h]
    L_0041219a:
        fld dword ptr [ecx+106Ch]
    L_004121a0:
        call asm_FUN_00463b2c_00463b2c
    L_004121a5:
        ret 4
    L_004121a8:
        push esi
    L_004121a9:
        lea esi,[ecx+10FCh]
    L_004121af:
        call asm_AnimationManager_ValidateHandle_00449450
    L_004121b4:
        movsx eax,word ptr [eax+38Ah]
    L_004121bb:
        pop esi
    L_004121bc:
        ret 4
    L_004121bf:
        mov eax,dword ptr [data_00474c98]
    L_004121c4:
        ret 4
    L_004121c7:
        mov eax,dword ptr [data_00474c74]
    L_004121cc:
        ret 4
    L_004121cf:
        mov eax,dword ptr [ecx+23FCh]
    L_004121d5:
        ret 4
    L_004121d8:
        mov ecx,dword ptr [data_00474c74]
    L_004121de:
        xor eax,eax
    L_004121e0:
        test ecx,ecx
    L_004121e2:
        sete al
    L_004121e5:
        ret 4
    L_004121e8:
        mov ecx,dword ptr [data_00474c74]
    L_004121ee:
        xor eax,eax
    L_004121f0:
        cmp ecx,1
    L_004121f3:
        sete al
    L_004121f6:
        ret 4
    L_004121f9:
        mov ecx,dword ptr [data_00474c74]
    L_004121ff:
        xor eax,eax
    L_00412201:
        cmp ecx,2
    L_00412204:
        sete al
    L_00412207:
        ret 4
    L_0041220a:
        mov ecx,dword ptr [data_00474c74]
    L_00412210:
        xor eax,eax
    L_00412212:
        cmp ecx,3
    L_00412215:
        sete al
    L_00412218:
        ret 4
    L_0041221b:
        mov eax,1
    L_00412220:
        ret 4
    L_00412223:
        xor eax,eax
    L_00412225:
        ret 4
    }
}
