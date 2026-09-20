#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D2702): closest_byte_count=171; first_diff=unmeasured;
// residual_class=abi/cluster; the helper receives its motion state in ESI,
// branches between Cartesian and polar updates, calls the retained
// PolarToVector FSINCOS leaf, and then runs both coordinates through the
// private x87 angle-wrapping helper.  Its stack temporaries and register
// homes are coupled to the polar caller cluster.
// variants_tested=the recovered six-float motion layout, direct Vector2 polar
// update source, the existing bullet/effect callers, and the exact retail
// overlay; no readable candidate was byte-measured.
// next_lever=compile this helper with PolarToVector, the x87 wrapping callee,
// and the real bullet/effect callers as one native-LTCG cluster.
// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0044C2A0..0x0044C34A: Recovery_AdvancePolarMotion
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_AdvancePolarMotion_0044c2a0() {
    __asm {
    L_0044c2a0:
        mov al,byte ptr [esi+28h]
    L_0044c2a3:
        sub esp,18h
    L_0044c2a6:
        test al,1
    L_0044c2a8:
        jne short L_0044c2c5
    L_0044c2aa:
        fld dword ptr [esi]
    L_0044c2ac:
        fadd dword ptr [esi+0Ch]
    L_0044c2af:
        fstp dword ptr [esi]
    L_0044c2b1:
        fld dword ptr [esi+10h]
    L_0044c2b4:
        fadd dword ptr [esi+4]
    L_0044c2b7:
        fstp dword ptr [esi+4]
    L_0044c2ba:
        fld dword ptr [esi+14h]
    L_0044c2bd:
        fadd dword ptr [esi+8]
    L_0044c2c0:
        fstp dword ptr [esi+8]
    L_0044c2c3:
        jmp short L_0044c30f
    L_0044c2c5:
        mov eax,dword ptr [esi+20h]
    L_0044c2c8:
        mov ecx,dword ptr [esi+1Ch]
    L_0044c2cb:
        push eax
    L_0044c2cc:
        push ecx
    L_0044c2cd:
        lea ecx,[esp+14h]
    L_0044c2d1:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_0044c2d6:
        fld dword ptr [esp+0Ch]
    L_0044c2da:
        fadd dword ptr [esi+0Ch]
    L_0044c2dd:
        mov edx,dword ptr [esi+14h]
    L_0044c2e0:
        mov dword ptr [esp+8],edx
    L_0044c2e4:
        mov eax,esi
    L_0044c2e6:
        fstp dword ptr [esp]
    L_0044c2e9:
        mov ecx,dword ptr [esp]
    L_0044c2ec:
        fld dword ptr [esp+10h]
    L_0044c2f0:
        mov dword ptr [esp+14h],0
    L_0044c2f8:
        fadd dword ptr [esi+10h]
    L_0044c2fb:
        mov dword ptr [eax],ecx
    L_0044c2fd:
        mov ecx,dword ptr [esp+8]
    L_0044c301:
        fstp dword ptr [esp+4]
    L_0044c305:
        mov edx,dword ptr [esp+4]
    L_0044c309:
        mov dword ptr [eax+4],edx
    L_0044c30c:
        mov dword ptr [eax+8],ecx
    L_0044c30f:
        fld dword ptr [esi]
    L_0044c311:
        sub esp,8
    L_0044c314:
        fmul dword ptr [data_00470b44]
    L_0044c31a:
        fstp qword ptr [esp]
    L_0044c31d:
        call asm_FUN_00452ff0_00452ff0
    L_0044c322:
        fmul dword ptr [data_00470b00]
    L_0044c328:
        fstp dword ptr [esi]
    L_0044c32a:
        fld dword ptr [esi+4]
    L_0044c32d:
        fmul dword ptr [data_00470b44]
    L_0044c333:
        fstp qword ptr [esp]
    L_0044c336:
        call asm_FUN_00452ff0_00452ff0
    L_0044c33b:
        fmul dword ptr [data_00470b00]
    L_0044c341:
        add esp,8
    L_0044c344:
        fstp dword ptr [esi+4]
    L_0044c347:
        add esp,18h
    L_0044c34a:
        ret
    }
}
