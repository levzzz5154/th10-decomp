#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B3A0..0x0040B429: FUN_0040b3a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b3a0_0040b3a0() {
    __asm {
    L_0040b3a0:
        push ecx
    L_0040b3a1:
        push ebx
    L_0040b3a2:
        push ebp
    L_0040b3a3:
        push esi
    L_0040b3a4:
        push edi
    L_0040b3a5:
        mov edi,eax
    L_0040b3a7:
        lea esi,[edi+0D0h]
    L_0040b3ad:
        mov dword ptr [esp+10h],esi
    L_0040b3b1:
        call asm_Platform_StopWorker_0044c150
    L_0040b3b6:
        mov ebx,dword ptr [data_00491c10]
    L_0040b3bc:
        lea edx,[edi+40h]
    L_0040b3bf:
        mov ebp,5
    L_0040b3c4:
        mov edi,4000000h
    L_0040b3c9:
        lea esp,[esp+force_disp32_zero]
    L_0040b3d0:
        mov ecx,dword ptr [edx]
    L_0040b3d2:
        test ecx,ecx
    L_0040b3d4:
        TH10_REL8(0x74, 0x0040b3d4, VA_asm_target_0040b43f)
    L_0040b3d6:
        mov eax,dword ptr [ebx+72DAD4h]
    L_0040b3dc:
        test eax,eax
    L_0040b3de:
        je short L_0040b3ed
    L_0040b3e0:
        mov esi,dword ptr [eax]
    L_0040b3e2:
        cmp dword ptr [esi],ecx
    L_0040b3e4:
        je short L_0040b406
    L_0040b3e6:
        mov eax,dword ptr [eax+4]
    L_0040b3e9:
        test eax,eax
    L_0040b3eb:
        jne short L_0040b3e0
    L_0040b3ed:
        mov eax,dword ptr [ebx+72DADCh]
    L_0040b3f3:
        test eax,eax
    L_0040b3f5:
        TH10_REL8(0x74, 0x0040b3f5, VA_asm_target_0040b43f)
    L_0040b3f7:
        mov esi,dword ptr [eax]
    L_0040b3f9:
        cmp dword ptr [esi],ecx
    L_0040b3fb:
        je short L_0040b406
    L_0040b3fd:
        mov eax,dword ptr [eax+4]
    L_0040b400:
        test eax,eax
    L_0040b402:
        jne short L_0040b3f7
    L_0040b404:
        TH10_REL8(0xeb, 0x0040b404, VA_asm_target_0040b43f)
    L_0040b406:
        mov eax,dword ptr [eax]
    L_0040b408:
        test eax,eax
    L_0040b40a:
        TH10_REL8(0x74, 0x0040b40a, VA_asm_target_0040b43f)
    L_0040b40c:
        mov esi,dword ptr [eax+35Ch]
    L_0040b412:
        mov ecx,dword ptr [eax+18h]
    L_0040b415:
        or esi,edi
    L_0040b417:
        test ecx,ecx
    L_0040b419:
        mov dword ptr [eax+35Ch],esi
    L_0040b41f:
        TH10_REL8(0x75, 0x0040b41f, VA_asm_target_0040b43f)
    L_0040b421:
        mov eax,dword ptr [eax+14h]
    L_0040b424:
        test eax,eax
    L_0040b426:
        TH10_REL8(0x74, 0x0040b426, VA_asm_target_0040b43f)
    L_0040b428:
        TH10_REL8(0xeb, 0x0040b428, VA_asm_FUN_0040b3a0_part_0040b430)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0040b430:
        mov ecx,dword ptr [eax]
    L_0040b432:
        or dword ptr [ecx+35Ch],edi
    L_0040b438:
        mov eax,dword ptr [eax+4]
    L_0040b43b:
        test eax,eax
    L_0040b43d:
        jne short L_0040b430
    L_0040b43f:
        mov dword ptr [edx],0
    L_0040b445:
        add edx,4
    L_0040b448:
        dec ebp
    L_0040b449:
        TH10_REL8(0x75, 0x0040b449, VA_asm_target_0040b3d0)
    L_0040b44b:
        mov esi,dword ptr [esp+10h]
    L_0040b44f:
        mov dword ptr [esi],4703E4h
    L_0040b455:
        call asm_Platform_StopWorker_0044c150
    L_0040b45a:
        pop edi
    L_0040b45b:
        pop esi
    L_0040b45c:
        pop ebp
    L_0040b45d:
        pop ebx
    L_0040b45e:
        pop ecx
    L_0040b45f:
        ret
    }
}
