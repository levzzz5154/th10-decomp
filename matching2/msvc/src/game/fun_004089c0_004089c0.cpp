// BLOCKED (D3802): closest_byte_count=0/211; first_diff=0x004089C0;
// residual_class=private EBX receiver, callback-function address escapes,
// EDI priorities, and scheduler registration ABI. Live Ghidra decompilation
// confirms three callback registrations at 0x00449ED0/0x00449AE0/
// 0x00449B70 and the trailing frame-timer flag initialization.
// variants_tested=live Ghidra decompile with callers 0x00408C90 and
// callees 0x00409220, 0x00409230, 0x00409270, 0x00449AE0, 0x00449B70;
// archived PlayerScoreRuntime semantic source; no standalone readable
// candidate retained because the public declaration cannot express EBX/EDI.
// next_lever=promote the three callback leaves and this initializer in one
// real-caller schema-2/native-LTCG cluster, leaving the initializer selected
// from 0x00408C90 so LTCG can infer the retail private receiver.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x004089C0..0x00408A92: FUN_004089c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004089c0_004089c0() {
    __asm {
    L_004089c0:
        push esi
    L_004089c1:
        push edi
    L_004089c2:
        push 409220h
    L_004089c7:
        call asm_SchedulerCallback_Create_00449ed0
    L_004089cc:
        mov esi,eax
    L_004089ce:
        mov edx,dword ptr [esi+4]
    L_004089d1:
        mov eax,dword ptr [data_00491be4]
    L_004089d6:
        and edx,0FFFFFFFDh
    L_004089d9:
        push eax
    L_004089da:
        mov edi,16h
    L_004089df:
        mov dword ptr [esi+20h],ebx
    L_004089e2:
        mov dword ptr [esi+4],edx
    L_004089e5:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004089ea:
        push 409230h
    L_004089ef:
        mov dword ptr [ebx+8],esi
    L_004089f2:
        call asm_SchedulerCallback_Create_00449ed0
    L_004089f7:
        mov ecx,dword ptr [data_00491be4]
    L_004089fd:
        mov esi,eax
    L_004089ff:
        and dword ptr [esi+4],0FFFFFFFDh
    L_00408a03:
        push ecx
    L_00408a04:
        mov edi,0Eh
    L_00408a09:
        mov dword ptr [esi+20h],ebx
    L_00408a0c:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00408a11:
        push 409270h
    L_00408a16:
        mov dword ptr [ebx+0Ch],esi
    L_00408a19:
        call asm_SchedulerCallback_Create_00449ed0
    L_00408a1e:
        mov edx,dword ptr [data_00491be4]
    L_00408a24:
        mov esi,eax
    L_00408a26:
        mov eax,dword ptr [esi+4]
    L_00408a29:
        and eax,0FFFFFFFDh
    L_00408a2c:
        push edx
    L_00408a2d:
        mov edi,25h
    L_00408a32:
        mov dword ptr [esi+20h],ebx
    L_00408a35:
        mov dword ptr [esi+4],eax
    L_00408a38:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00408a3d:
        mov dword ptr [ebx+37ACh],esi
    L_00408a43:
        mov eax,dword ptr [ebx+3744h]
    L_00408a49:
        xor ecx,ecx
    L_00408a4b:
        test al,1
    L_00408a4d:
        pop edi
    L_00408a4e:
        pop esi
    L_00408a4f:
        jne short L_00408a7a
    L_00408a51:
        or eax,1
    L_00408a54:
        mov dword ptr [ebx+3738h],ecx
    L_00408a5a:
        mov dword ptr [ebx+3734h],0FFF0BDC1h
    L_00408a64:
        mov dword ptr [ebx+373Ch],ecx
    L_00408a6a:
        mov dword ptr [ebx+3740h],476F78h
    L_00408a74:
        mov dword ptr [ebx+3744h],eax
    L_00408a7a:
        mov dword ptr [ebx+3738h],ecx
    L_00408a80:
        mov dword ptr [ebx+373Ch],ecx
    L_00408a86:
        mov dword ptr [ebx+3734h],0FFFFFFFFh
    L_00408a90:
        xor eax,eax
    L_00408a92:
        ret
    }
}
