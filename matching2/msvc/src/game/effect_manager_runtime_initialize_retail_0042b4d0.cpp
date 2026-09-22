// BLOCKED (D3803): closest_byte_count=0/145; first_diff=0x0042B4D0
// (no readable native-LTCG body retained).
// residual_class=private EAX receiver/EBX manager state, ESI callback state,
// EDI registration priorities, and the private scheduler/entity/animation
// callee conventions at 0x00449AE0, 0x00449B70, 0x0043E5A0 and 0x00401DE0.
// variants_tested=live Ghidra complete decompile with caller 0x0042B683 and
// callees 0x00449ED0/0x00449AE0/0x00449B70/0x00401DE0/0x0043E5A0; MSVC
// 13.10.6030 authoritative production probe (145/145 exact); native-LTCG
// cluster feasibility review of the real caller/callee register topology.
// next_lever=compile a schema-2 native-LTCG cluster containing the real
// 0x0042B683 caller and all five private callees, then measure the complete
// body before changing production metadata.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x0042B4D0..0x0042B560: EffectManagerRuntime_InitializeRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EffectManagerRuntime_InitializeRetail_0042b4d0() {
    __asm {
    L_0042b4d0:
        push ebx
    L_0042b4d1:
        push esi
    L_0042b4d2:
        mov ebx,eax
    L_0042b4d4:
        mov eax,dword ptr [data_004776e0]
    L_0042b4d9:
        mov ecx,dword ptr [eax+8994h]
    L_0042b4df:
        push edi
    L_0042b4e0:
        push 42B9A0h
    L_0042b4e5:
        mov dword ptr [ebx+10h],ecx
    L_0042b4e8:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042b4ed:
        mov edx,dword ptr [data_00491be4]
    L_0042b4f3:
        mov esi,eax
    L_0042b4f5:
        mov eax,dword ptr [esi+4]
    L_0042b4f8:
        and eax,0FFFFFFFDh
    L_0042b4fb:
        push edx
    L_0042b4fc:
        mov edi,0Fh
    L_0042b501:
        mov dword ptr [esi+20h],ebx
    L_0042b504:
        mov dword ptr [esi+4],eax
    L_0042b507:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0042b50c:
        push 42B9B0h
    L_0042b511:
        mov dword ptr [ebx+8],esi
    L_0042b514:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042b519:
        mov esi,eax
    L_0042b51b:
        mov edx,dword ptr [esi+4]
    L_0042b51e:
        mov eax,dword ptr [data_00491be4]
    L_0042b523:
        and edx,0FFFFFFFDh
    L_0042b526:
        push eax
    L_0042b527:
        mov edi,23h
    L_0042b52c:
        mov dword ptr [esi+20h],ebx
    L_0042b52f:
        mov dword ptr [esi+4],edx
    L_0042b532:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0042b537:
        mov dword ptr [ebx+0Ch],esi
    L_0042b53a:
        lea esi,[ebx+18h]
    L_0042b53d:
        mov ebx,dword ptr [ebx+10h]
    L_0042b540:
        mov edx,esi
    L_0042b542:
        call asm_InitializeEntity_00401de0
    L_0042b547:
        mov edx,0C4h
    L_0042b54c:
        mov eax,esi
    L_0042b54e:
        mov ecx,ebx
    L_0042b550:
        mov dword ptr [esi+308h],ebx
    L_0042b556:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042b55b:
        pop edi
    L_0042b55c:
        pop esi
    L_0042b55d:
        xor eax,eax
    L_0042b55f:
        pop ebx
    L_0042b560:
        ret
    }
}
