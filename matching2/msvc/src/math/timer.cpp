#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404ED0..0x00404F17: ?FrameTimer_Tick@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FrameTimer_Tick_00404ed0() {
    __asm {
    L_00404ed0:
        mov edx,dword ptr [esi+4]
    L_00404ed3:
        mov ecx,dword ptr [esi+0Ch]
    L_00404ed6:
        mov dword ptr [esi],edx
    L_00404ed8:
        fld dword ptr [ecx]
    L_00404eda:
        fcomp dword ptr [data_00470b68]
    L_00404ee0:
        fnstsw ax
    L_00404ee2:
        test ah,41h
    L_00404ee5:
        jne short L_00404f07
    L_00404ee7:
        fld dword ptr [ecx]
    L_00404ee9:
        fcomp dword ptr [data_00470b64]
    L_00404eef:
        fnstsw ax
    L_00404ef1:
        test ah,5
    L_00404ef4:
        jp short L_00404f07
    L_00404ef6:
        fld dword ptr [esi+8]
    L_00404ef9:
        inc edx
    L_00404efa:
        fadd dword ptr [data_00470afc]
    L_00404f00:
        mov dword ptr [esi+4],edx
    L_00404f03:
        fstp dword ptr [esi+8]
    L_00404f06:
        ret
    L_00404f07:
        fld dword ptr [ecx]
    L_00404f09:
        fadd dword ptr [esi+8]
    L_00404f0c:
        fst dword ptr [esi+8]
    L_00404f0f:
        call asm_FUN_00463b2c_00463b2c
    L_00404f14:
        mov dword ptr [esi+4],eax
    L_00404f17:
        ret
    }
}

// 0x00428DD0..0x00428DE3: ?FrameTimer_Decrement@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FrameTimer_Decrement_00428dd0() {
    __asm {
    L_00428dd0:
        push ecx
    L_00428dd1:
        neg eax
    L_00428dd3:
        mov dword ptr [esp],eax
    L_00428dd6:
        fild dword ptr [esp]
    L_00428dd9:
        push ecx
    L_00428dda:
        fstp dword ptr [esp]
    L_00428ddd:
        call asm_FrameTimer_Advance_0044bf40
    L_00428de2:
        pop ecx
    L_00428de3:
        ret
    }
}

// 0x0042C620..0x0042C66F: ?GameState_SetTimerTarget@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_SetTimerTarget_0042c620() {
    __asm {
    L_0042c620:
        mov dword ptr [eax+20h],ecx
    L_0042c623:
        mov ecx,dword ptr [eax+2C0h]
    L_0042c629:
        xor edx,edx
    L_0042c62b:
        test cl,1
    L_0042c62e:
        jne short L_0042c659
    L_0042c630:
        or ecx,1
    L_0042c633:
        mov dword ptr [eax+2B4h],edx
    L_0042c639:
        mov dword ptr [eax+2B0h],0FFF0BDC1h
    L_0042c643:
        mov dword ptr [eax+2B8h],edx
    L_0042c649:
        mov dword ptr [eax+2BCh],476F78h
    L_0042c653:
        mov dword ptr [eax+2C0h],ecx
    L_0042c659:
        mov dword ptr [eax+2B4h],edx
    L_0042c65f:
        mov dword ptr [eax+2B8h],edx
    L_0042c665:
        mov dword ptr [eax+2B0h],0FFFFFFFFh
    L_0042c66f:
        ret
    }
}

// 0x0044BF40..0x0044BF97: ?FrameTimer_Advance@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FrameTimer_Advance_0044bf40() {
    __asm {
    L_0044bf40:
        mov eax,dword ptr [esi+4]
    L_0044bf43:
        mov ecx,dword ptr [esi+0Ch]
    L_0044bf46:
        mov dword ptr [esi],eax
    L_0044bf48:
        fld dword ptr [ecx]
    L_0044bf4a:
        fcomp dword ptr [data_00470b68]
    L_0044bf50:
        fnstsw ax
    L_0044bf52:
        test ah,41h
    L_0044bf55:
        jne short L_0044bf7e
    L_0044bf57:
        fld dword ptr [ecx]
    L_0044bf59:
        fcomp dword ptr [data_00470b64]
    L_0044bf5f:
        fnstsw ax
    L_0044bf61:
        test ah,5
    L_0044bf64:
        jp short L_0044bf7e
    L_0044bf66:
        fld dword ptr [esp+4]
    L_0044bf6a:
        fadd dword ptr [esi+8]
    L_0044bf6d:
        fstp dword ptr [esi+8]
    L_0044bf70:
        fld dword ptr [esi+8]
    L_0044bf73:
        call asm_FUN_00463b2c_00463b2c
    L_0044bf78:
        mov dword ptr [esi+4],eax
    L_0044bf7b:
        ret 4
    L_0044bf7e:
        fld dword ptr [esp+4]
    L_0044bf82:
        fmul dword ptr [ecx]
    L_0044bf84:
        fadd dword ptr [esi+8]
    L_0044bf87:
        fstp dword ptr [esi+8]
    L_0044bf8a:
        fld dword ptr [esi+8]
    L_0044bf8d:
        call asm_FUN_00463b2c_00463b2c
    L_0044bf92:
        mov dword ptr [esi+4],eax
    L_0044bf95:
        ret 4
    }
}
