#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3403): closest_byte_count=411/411; first_diff=none
// residual_class=private_EDI_menu_receiver_with_ECX_environment_and_multiple
// animation/resource helper ABIs; live Ghidra decompile confirms the full
// control flow, but a readable standalone body cannot name the EDI receiver.
// variants_tested=live Ghidra decompile, caller/callee inspection at
// 0x00416C4C/0x00416E55 and 0x00449950/0x00449870, plus native-LTCG schema2
// feasibility analysis. next_lever=co-compile both real callers and the menu
// helper family in one schema2 cluster, preserving EDI and validating all
// resource-manager receiver conventions.
// 0x00423370..0x0042350A: FUN_00423370
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00423370_00423370() {
    __asm {
    L_00423370:
        push ecx
    L_00423371:
        mov eax,dword ptr [data_00477810]
    L_00423376:
        cmp dword ptr [eax+5Ch],1
    L_0042337a:
        jne short L_00423397
    L_0042337c:
        mov eax,dword ptr [data_00491ff4]
    L_00423381:
        and eax,1000h
    L_00423386:
        neg eax
    L_00423388:
        sbb eax,eax
    L_0042338a:
        and eax,0FFFFFFFEh
    L_0042338d:
        add eax,4
    L_00423390:
        mov dword ptr [data_00491fb8],eax
    L_00423395:
        pop ecx
    L_00423396:
        ret
    L_00423397:
        mov dword ptr [edi+4],6
    L_0042339e:
        mov ecx,dword ptr [edi+20h]
    L_004233a1:
        xor edx,edx
    L_004233a3:
        test cl,1
    L_004233a6:
        jne short L_004233c2
    L_004233a8:
        or ecx,1
    L_004233ab:
        mov dword ptr [edi+14h],edx
    L_004233ae:
        mov dword ptr [edi+10h],0FFF0BDC1h
    L_004233b5:
        mov dword ptr [edi+18h],edx
    L_004233b8:
        mov dword ptr [edi+1Ch],476F78h
    L_004233bf:
        mov dword ptr [edi+20h],ecx
    L_004233c2:
        mov ecx,dword ptr [data_004776e0]
    L_004233c8:
        mov dword ptr [edi+14h],edx
    L_004233cb:
        mov dword ptr [edi+18h],edx
    L_004233ce:
        mov dword ptr [edi+10h],0FFFFFFFFh
    L_004233d5:
        mov edx,dword ptr [eax+58h]
    L_004233d8:
        push ebx
    L_004233d9:
        push ebp
    L_004233da:
        or edx,10h
    L_004233dd:
        push esi
    L_004233de:
        mov esi,dword ptr [data_00491c10]
    L_004233e4:
        mov dword ptr [eax+58h],edx
    L_004233e7:
        mov ebp,dword ptr [ecx+8998h]
    L_004233ed:
        call asm_FUN_00449950_00449950
    L_004233f2:
        mov ebx,eax
    L_004233f4:
        mov ecx,dword ptr [ebx+35Ch]
    L_004233fa:
        or ecx,40000000h
    L_00423400:
        push 0
    L_00423402:
        mov dword ptr [ebx+35Ch],ecx
    L_00423408:
        push ebx
    L_00423409:
        mov ecx,ebp
    L_0042340b:
        mov dword ptr [ebx+20h],0Fh
    L_00423412:
        call asm_FUN_00449870_00449870
    L_00423417:
        mov esi,dword ptr [data_00491c10]
    L_0042341d:
        lea eax,[esp+0Ch]
    L_00423421:
        mov edx,esi
    L_00423423:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00423428:
        mov eax,dword ptr [esp+0Ch]
    L_0042342c:
        push 1C0h
    L_00423431:
        push 180h
    L_00423436:
        push 10h
    L_00423438:
        push 20h
    L_0042343a:
        push eax
    L_0042343b:
        mov dword ptr [edi+1D8h],eax
    L_00423441:
        call asm_FUN_00424480_00424480
    L_00423446:
        mov edx,dword ptr [data_0047770c]
    L_0042344c:
        mov ebp,dword ptr [edx+9EC8h]
    L_00423452:
        mov dword ptr [edi+2C4h],ebp
    L_00423458:
        call asm_FUN_00449950_00449950
    L_0042345d:
        mov ebx,eax
    L_0042345f:
        mov ecx,dword ptr [ebx+35Ch]
    L_00423465:
        or ecx,40000000h
    L_0042346b:
        push 81h
    L_00423470:
        mov dword ptr [ebx+35Ch],ecx
    L_00423476:
        push ebx
    L_00423477:
        mov ecx,ebp
    L_00423479:
        mov dword ptr [ebx+20h],0Fh
    L_00423480:
        call asm_FUN_00449870_00449870
    L_00423485:
        mov edx,dword ptr [data_00491c10]
    L_0042348b:
        lea eax,[esp+0Ch]
    L_0042348f:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00423494:
        mov eax,dword ptr [esp+0Ch]
    L_00423498:
        push 46E0D8h
    L_0042349d:
        push 0
    L_0042349f:
        mov dword ptr [edi+1D4h],eax
    L_004234a5:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_004234aa:
        test byte ptr [data_00491d78],10h
    L_004234b1:
        pop esi
    L_004234b2:
        pop ebp
    L_004234b3:
        pop ebx
    L_004234b4:
        je short L_004234c9
    L_004234b6:
        push 0
    L_004234b8:
        push 4
    L_004234ba:
        mov edx,46DF98h
    L_004234bf:
        mov eax,492590h
    L_004234c4:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004234c9:
        push 0
    L_004234cb:
        push 2
    L_004234cd:
        mov edx,46DF98h
    L_004234d2:
        mov eax,492590h
    L_004234d7:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004234dc:
        mov ecx,dword ptr [data_0047783c]
    L_004234e2:
        mov eax,1
    L_004234e7:
        mov byte ptr [ecx+1D8A3h],al
    L_004234ed:
        mov dword ptr [edi+1E4h],eax
    L_004234f3:
        mov edx,dword ptr [data_00476f78]
    L_004234f9:
        mov dword ptr [edi+2C0h],edx
    L_004234ff:
        mov dword ptr [data_00476f78],3F800000h
    L_00423509:
        pop ecx
    L_0042350a:
        ret
    }
}
