#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D2702): closest_byte_count=111; first_diff=unmeasured;
// residual_class=abi/cluster; retail enters with the animation context in EDX,
// the source position record in ESI, and the script handle in the stack slot,
// while the manager object remains in ECX across AnimationManager_Find and the
// child-list walk.  That private register contract is not expressible by a
// standalone readable member without compiling the Find/setter cluster.
// variants_tested=the existing SetPosition/Find semantic structures, a
// translated-position member candidate using the same +0x340/+0x14/+0x18
// layout, and the exact retail overlay; no candidate was byte-measured.
// next_lever=co-compile AnimationManager_Find, SetPosition, this setter, and
// its real animation callers as one native-LTCG cluster.
// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449350..0x004493BE: ?AnimationManager_SetTranslatedPosition@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetTranslatedPosition_00449350() {
    __asm {
    L_00449350:
        mov eax,dword ptr [esp+4]
    L_00449354:
        push eax
    L_00449355:
        call asm_AnimationManager_Find_004491c0
    L_0044935a:
        test eax,eax
    L_0044935c:
        je short L_004493bc
    L_0044935e:
        fld dword ptr [esi]
    L_00449360:
        fadd dword ptr [data_00470b4c]
    L_00449366:
        fstp dword ptr [eax+340h]
    L_0044936c:
        fld dword ptr [esi+4]
    L_0044936f:
        fadd dword ptr [data_00470b48]
    L_00449375:
        fstp dword ptr [eax+344h]
    L_0044937b:
        mov ecx,dword ptr [esi+8]
    L_0044937e:
        mov dword ptr [eax+348h],ecx
    L_00449384:
        mov ecx,dword ptr [eax+18h]
    L_00449387:
        test ecx,ecx
    L_00449389:
        jne short L_004493bc
    L_0044938b:
        mov ecx,dword ptr [eax+14h]
    L_0044938e:
        test ecx,ecx
    L_00449390:
        je short L_004493bc
    L_00449392:
        fld dword ptr [esi]
    L_00449394:
        mov eax,dword ptr [ecx]
    L_00449396:
        fadd dword ptr [data_00470b4c]
    L_0044939c:
        add eax,340h
    L_004493a1:
        fstp dword ptr [eax]
    L_004493a3:
        fld dword ptr [esi+4]
    L_004493a6:
        fadd dword ptr [data_00470b48]
    L_004493ac:
        fstp dword ptr [eax+4]
    L_004493af:
        mov edx,dword ptr [esi+8]
    L_004493b2:
        mov dword ptr [eax+8],edx
    L_004493b5:
        mov ecx,dword ptr [ecx+4]
    L_004493b8:
        test ecx,ecx
    L_004493ba:
        jne short L_00449392
    L_004493bc:
        ret 4
    }
}
