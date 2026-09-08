#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421300..0x00421349: FUN_00421300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421300_00421300() {
    __asm {
    L_00421300:
        push ebp
    L_00421301:
        mov ebp,dword ptr [esp+8]
    L_00421305:
        mov eax,dword ptr [ebp+6FCh]
    L_0042130b:
        push edi
    L_0042130c:
        xor edi,edi
    L_0042130e:
        cmp eax,1
    L_00421311:
        jne asm_target_004213fa
    L_00421317:
        mov eax,dword ptr [data_00477824]
    L_0042131c:
        push ebx
    L_0042131d:
        mov ebx,dword ptr [data_00491c10]
    L_00421323:
        push esi
    L_00421324:
        push eax
    L_00421325:
        mov edx,ebx
    L_00421327:
        call asm_AnimationManager_Find_004491c0
    L_0042132c:
        cmp eax,edi
    L_0042132e:
        mov esi,2
    L_00421333:
        TH10_REL8(0x74, 0x00421333, VA_asm_target_00421360)
    L_00421335:
        cmp dword ptr [eax+18h],edi
    L_00421338:
        mov word ptr [eax+304h],si
    L_0042133f:
        TH10_REL8(0x75, 0x0042133f, VA_asm_target_00421360)
    L_00421341:
        mov eax,dword ptr [eax+14h]
    L_00421344:
        cmp eax,edi
    L_00421346:
        TH10_REL8(0x74, 0x00421346, VA_asm_target_00421360)
    L_00421348:
        TH10_REL8(0xeb, 0x00421348, VA_asm_FUN_00421300_part_00421350)
    }
}

// 0x00421350..0x00421386: FUN_00421300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421300_part_00421350() {
    __asm {
    L_00421350:
        mov ecx,dword ptr [eax]
    L_00421352:
        mov word ptr [ecx+304h],si
    L_00421359:
        mov eax,dword ptr [eax+4]
    L_0042135c:
        cmp eax,edi
    L_0042135e:
        jne short L_00421350
    L_00421360:
        mov edx,dword ptr [data_00477828]
    L_00421366:
        push edx
    L_00421367:
        mov edx,ebx
    L_00421369:
        call asm_AnimationManager_Find_004491c0
    L_0042136e:
        cmp eax,edi
    L_00421370:
        TH10_REL8(0x74, 0x00421370, VA_asm_target_004213a0)
    L_00421372:
        cmp dword ptr [eax+18h],edi
    L_00421375:
        mov word ptr [eax+304h],si
    L_0042137c:
        TH10_REL8(0x75, 0x0042137c, VA_asm_target_004213a0)
    L_0042137e:
        mov eax,dword ptr [eax+14h]
    L_00421381:
        cmp eax,edi
    L_00421383:
        TH10_REL8(0x74, 0x00421383, VA_asm_target_004213a0)
    L_00421385:
        TH10_REL8(0xeb, 0x00421385, VA_asm_FUN_00421300_part_00421390)
    }
}

// 0x00421390..0x004213C6: FUN_00421300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421300_part_00421390() {
    __asm {
    L_00421390:
        mov ecx,dword ptr [eax]
    L_00421392:
        mov word ptr [ecx+304h],si
    L_00421399:
        mov eax,dword ptr [eax+4]
    L_0042139c:
        cmp eax,edi
    L_0042139e:
        jne short L_00421390
    L_004213a0:
        mov edx,dword ptr [data_0047782c]
    L_004213a6:
        push edx
    L_004213a7:
        mov edx,ebx
    L_004213a9:
        call asm_AnimationManager_Find_004491c0
    L_004213ae:
        cmp eax,edi
    L_004213b0:
        TH10_REL8(0x74, 0x004213b0, VA_asm_target_004213e0)
    L_004213b2:
        cmp dword ptr [eax+18h],edi
    L_004213b5:
        mov word ptr [eax+304h],si
    L_004213bc:
        TH10_REL8(0x75, 0x004213bc, VA_asm_target_004213e0)
    L_004213be:
        mov eax,dword ptr [eax+14h]
    L_004213c1:
        cmp eax,edi
    L_004213c3:
        TH10_REL8(0x74, 0x004213c3, VA_asm_target_004213e0)
    L_004213c5:
        TH10_REL8(0xeb, 0x004213c5, VA_asm_FUN_00421300_part_004213d0)
    }
}

// 0x004213D0..0x0042140C: FUN_00421300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421300_part_004213d0() {
    __asm {
    L_004213d0:
        mov ecx,dword ptr [eax]
    L_004213d2:
        mov word ptr [ecx+304h],si
    L_004213d9:
        mov eax,dword ptr [eax+4]
    L_004213dc:
        cmp eax,edi
    L_004213de:
        jne short L_004213d0
    L_004213e0:
        mov dword ptr [data_00477824],edi
    L_004213e6:
        mov dword ptr [data_00477828],edi
    L_004213ec:
        mov dword ptr [data_0047782c],edi
    L_004213f2:
        mov dword ptr [ebp+6FCh],esi
    L_004213f8:
        pop esi
    L_004213f9:
        pop ebx
    L_004213fa:
        cmp dword ptr [data_00491bec],edi
    L_00421400:
        je short L_00421408
    L_00421402:
        mov dword ptr [data_00491bec],edi
    L_00421408:
        pop edi
    L_00421409:
        pop ebp
    L_0042140a:
        ret 4
    }
}
