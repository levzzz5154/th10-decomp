#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// BLOCKED (D3502): closest_byte_count=0/174; first_diff=0x004281D0;
// residual_class=private EAX receiver, hidden EBX/ESI schedule state, and
// private helper call conventions across the stage-dispatch branch.
// variants_tested=live Ghidra complete decompile with caller/callees
// (0x004262C7, 0x00428160, 0x00427E90), plus MSVC 13.10 readable explicit
// state-parameter candidate (161-byte extent; no comparable bytes).
// next_lever=native-LTCG cluster compiling the real 0x00425730 caller with
// 0x00428160/0x00427E90 so private register inputs remain live.

// 0x004281D0..0x0042827D: Recovery_UpdateStageSequence
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_UpdateStageSequence_004281d0() {
    __asm {
    L_004281d0:
        push ebx
    L_004281d1:
        push edi
    L_004281d2:
        mov edi,eax
    L_004281d4:
        mov eax,dword ptr [edi+458h]
    L_004281da:
        mov ebx,1
    L_004281df:
        cmp eax,ebx
    L_004281e1:
        jne asm_target_00428268
    L_004281e7:
        mov eax,dword ptr [edi+464h]
    L_004281ed:
        test eax,eax
    L_004281ef:
        jge short L_00428206
    L_004281f1:
        test byte ptr [data_00474e5c],bl
    L_004281f7:
        je short L_00428249
    L_004281f9:
        push 0
    L_004281fb:
        lea eax,[edi+460h]
    L_00428201:
        call asm_Player_SetSchedulerValue_00405410
    L_00428206:
        mov eax,dword ptr [edi+464h]
    L_0042820c:
        mov ecx,dword ptr [edi+460h]
    L_00428212:
        cmp eax,ecx
    L_00428214:
        push esi
    L_00428215:
        lea esi,[edi+460h]
    L_0042821b:
        je short L_0042822d
    L_0042821d:
        mov ebx,dword ptr [edi+464h]
    L_00428223:
        call asm_Recovery_DispatchSchedule_00428160
    L_00428228:
        mov ebx,1
    L_0042822d:
        cmp dword ptr [edi+464h],0Fh
    L_00428234:
        jl short L_0042825d
    L_00428236:
        test byte ptr [data_00474e5c],bl
    L_0042823c:
        je short L_0042824e
    L_0042823e:
        push 0C1700000h
    L_00428243:
        call asm_FrameTimer_Advance_0044bf40
    L_00428248:
        pop esi
    L_00428249:
        pop edi
    L_0042824a:
        xor eax,eax
    L_0042824c:
        pop ebx
    L_0042824d:
        ret
    L_0042824e:
        push 0FFFFFFFFh
    L_00428250:
        mov eax,esi
    L_00428252:
        call asm_Player_SetSchedulerValue_00405410
    L_00428257:
        pop esi
    L_00428258:
        pop edi
    L_00428259:
        xor eax,eax
    L_0042825b:
        pop ebx
    L_0042825c:
        ret
    L_0042825d:
        call asm_FrameTimer_Tick_00404ed0
    L_00428262:
        pop esi
    L_00428263:
        pop edi
    L_00428264:
        xor eax,eax
    L_00428266:
        pop ebx
    L_00428267:
        ret
    L_00428268:
        mov dword ptr [edi+3504h],0
    L_00428272:
        mov byte ptr [edi+3508h],0
    L_00428279:
        pop edi
    L_0042827a:
        xor eax,eax
    L_0042827c:
        pop ebx
    L_0042827d:
        ret
    }
}
