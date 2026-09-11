#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418D40..0x00418E2C: StageTipManager_Construct
// Naked body preserves the retail register/stack ABI.

// 0x00424650..0x004246B7: StageTip_CreateUrgent
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageTip_CreateUrgent_00424650() {
    __asm {
    L_00424650:
        mov eax,dword ptr [data_00474c7c]
    L_00424655:
        lea eax,[eax+eax*2]
    L_00424658:
        mov eax,dword ptr [esi+eax*4+7Ch]
    L_0042465c:
        test eax,eax
    L_0042465e:
        je short L_00424676
    L_00424660:
        mov edx,dword ptr [eax+4]
    L_00424663:
        mov eax,dword ptr [eax]
    L_00424665:
        mov ecx,dword ptr [eax+70h]
    L_00424668:
        test ecx,ecx
    L_0042466a:
        jle short L_00424670
    L_0042466c:
        dec ecx
    L_0042466d:
        mov dword ptr [eax+70h],ecx
    L_00424670:
        test edx,edx
    L_00424672:
        mov eax,edx
    L_00424674:
        jne short L_00424660
    L_00424676:
        mov ecx,dword ptr [esp+4]
    L_0042467a:
        push ebx
    L_0042467b:
        mov ebx,dword ptr [esp+0Ch]
    L_0042467f:
        push ecx
    L_00424680:
        push esi
    L_00424681:
        call asm_StageTip_CreateRetail_0041a120
    L_00424686:
        mov edx,dword ptr [eax+60h]
    L_00424689:
        add edx,0FFFFFFC4h
    L_0042468c:
        mov ecx,edx
    L_0042468e:
        test ecx,ecx
    L_00424690:
        mov dword ptr [eax+60h],edx
    L_00424693:
        pop ebx
    L_00424694:
        jg short L_0042469d
    L_00424696:
        mov dword ptr [eax+60h],1
    L_0042469d:
        mov dword ptr [eax+6Ch],5Ah
    L_004246a4:
        mov dword ptr [eax+84h],0FFFF8080h
    L_004246ae:
        mov dword ptr [eax+70h],1Eh
    L_004246b5:
        ret 8
    }
}
