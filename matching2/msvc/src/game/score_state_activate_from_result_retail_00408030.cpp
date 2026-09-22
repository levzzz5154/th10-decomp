#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// BLOCKED (D2701): closest_byte_count=219 (retail extent 199);
// first_diff=0x00408030; residual_class=private-ABI/cluster.  A readable
// typed state-field candidate with cdecl helper calls emitted 219 bytes and
// diverged immediately because the retail object arrives in ESI while the
// ordinary declaration receives it from the stack.
// variants_tested=the corrected state layout with cdecl bounds/animation
// helper pointers and native MSVC 13.10 probe (219-byte extent, first diff at
// entry); the exact naked ESI/ECX overlay remains the only exact body.
// next_lever=native-LTCG compilation of this function with its real callers
// and recovered helper member declarations, preserving ESI as the object
// register without inline assembly.
// 0x00408030..0x004080F6: ScoreState_ActivateFromResultRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreState_ActivateFromResultRetail_00408030() {
    __asm {
    L_00408030:
        push ecx
    L_00408031:
        mov ax,word ptr [esi+446h]
    L_00408038:
        cmp ax,2
    L_0040803c:
        je short L_00408048
    L_0040803e:
        cmp ax,1
    L_00408042:
        je short L_00408048
    L_00408044:
        xor eax,eax
    L_00408046:
        pop ecx
    L_00408047:
        ret
    L_00408048:
        push 41000000h
    L_0040804d:
        lea ecx,[esi+3B4h]
    L_00408053:
        push 41000000h
    L_00408058:
        call asm_OutsideAxisAlignedBounds_004086b0
    L_0040805d:
        test eax,eax
    L_0040805f:
        mov word ptr [esi+30Ch],1
    L_00408068:
        mov word ptr [esi+446h],3
    L_00408071:
        jne short L_004080ed
    L_00408073:
        mov eax,dword ptr [esi+438h]
    L_00408079:
        push ebp
    L_0040807a:
        xor ebp,ebp
    L_0040807c:
        cmp eax,ebp
    L_0040807e:
        jl short L_0040809c
    L_00408080:
        mov edx,dword ptr [data_004776f0]
    L_00408086:
        push edi
    L_00408087:
        push eax
    L_00408088:
        lea eax,[esp+0Ch]
    L_0040808c:
        push eax
    L_0040808d:
        mov eax,dword ptr [edx+3E0B50h]
    L_00408093:
        push eax
    L_00408094:
        mov edi,ecx
    L_00408096:
        call asm_PlayerAnimation_Create_00448db0
    L_0040809b:
        pop edi
    L_0040809c:
        mov eax,dword ptr [esi+408h]
    L_004080a2:
        test al,1
    L_004080a4:
        jne short L_004080cf
    L_004080a6:
        or eax,1
    L_004080a9:
        mov dword ptr [esi+3FCh],ebp
    L_004080af:
        mov dword ptr [esi+3F8h],0FFF0BDC1h
    L_004080b9:
        mov dword ptr [esi+400h],ebp
    L_004080bf:
        mov dword ptr [esi+404h],476F78h
    L_004080c9:
        mov dword ptr [esi+408h],eax
    L_004080cf:
        mov dword ptr [esi+3FCh],ebp
    L_004080d5:
        mov dword ptr [esi+400h],ebp
    L_004080db:
        mov dword ptr [esi+3F8h],0FFFFFFFFh
    L_004080e5:
        pop ebp
    L_004080e6:
        mov eax,1
    L_004080eb:
        pop ecx
    L_004080ec:
        ret
    L_004080ed:
        or dword ptr [esi],8
    L_004080f0:
        mov eax,1
    L_004080f5:
        pop ecx
    L_004080f6:
        ret
    }
}
