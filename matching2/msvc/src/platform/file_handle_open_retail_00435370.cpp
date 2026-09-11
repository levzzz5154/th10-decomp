#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435370..0x004353AC: FileHandle_OpenRetail
// Naked body preserves the retail register/stack ABI.

// 0x00435370..0x004353AC: FileHandle_OpenRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FileHandle_OpenRetail_00435370() {
    __asm {
    L_00435370:
        sub esp,10Ch
    L_00435376:
        mov eax,dword ptr [data_00473660]
    L_0043537b:
        xor eax,esp
    L_0043537d:
        push ebx
    L_0043537e:
        push ebp
    L_0043537f:
        mov ebp,dword ptr [esp+118h]
    L_00435386:
        push esi
    L_00435387:
        push edi
    L_00435388:
        mov esi,ecx
    L_0043538a:
        mov dword ptr [esp+118h],eax
    L_00435391:
        mov eax,dword ptr [esi]
    L_00435393:
        xor edi,edi
    L_00435395:
        mov dword ptr [esp+10h],edi
    L_00435399:
        call dword ptr [eax+4]
    L_0043539c:
        mov eax,dword ptr [esp+124h]
    L_004353a3:
        mov ebx,eax
    L_004353a5:
        mov al,byte ptr [eax]
    L_004353a7:
        test al,al
    L_004353a9:
        TH10_REL8(0x74, 0x004353a9, VA_asm_target_004353f6)
    L_004353ab:
        TH10_REL8(0xeb, 0x004353ab, VA_asm_FileHandle_OpenRetail_part_004353b0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004353b0:
        cmp al,72h
    L_004353b2:
        je short L_004353c6
    L_004353b4:
        cmp al,77h
    L_004353b6:
        je short L_004353d4
    L_004353b8:
        cmp al,61h
    L_004353ba:
        je short L_004353e2
    L_004353bc:
        mov al,byte ptr [ebx+1]
    L_004353bf:
        inc ebx
    L_004353c0:
        test al,al
    L_004353c2:
        jne short L_004353b0
    L_004353c4:
        jmp short L_00435444
    L_004353c6:
        mov dword ptr [esi+8],80000000h
    L_004353cd:
        mov edi,3
    L_004353d2:
        jmp short L_004353f6
    L_004353d4:
        push ebp
    L_004353d5:
        call dword ptr [data_004660c0]
    L_004353db:
        mov edi,2
    L_004353e0:
        jmp short L_004353ef
    L_004353e2:
        mov dword ptr [esp+10h],1
    L_004353ea:
        mov edi,4
    L_004353ef:
        mov dword ptr [esi+8],40000000h
    L_004353f6:
        cmp byte ptr [ebx],0
    L_004353f9:
        je short L_00435429
    L_004353fb:
        mov eax,ebp
    L_004353fd:
        lea ecx,[esp+14h]
    L_00435401:
        call asm_File_ResolvePath_00435610
    L_00435406:
        mov ecx,dword ptr [esi+8]
    L_00435409:
        push 0
    L_0043540b:
        push 8000080h
    L_00435410:
        push edi
    L_00435411:
        push 0
    L_00435413:
        push 1
    L_00435415:
        push ecx
    L_00435416:
        lea edx,[esp+2Ch]
    L_0043541a:
        push edx
    L_0043541b:
        call dword ptr [data_004660c4]
    L_00435421:
        cmp eax,0FFFFFFFFh
    L_00435424:
        mov dword ptr [esi+4],eax
    L_00435427:
        jne short L_0043542d
    L_00435429:
        xor al,al
    L_0043542b:
        jmp short L_00435444
    L_0043542d:
        mov ecx,dword ptr [esp+10h]
    L_00435431:
        test ecx,ecx
    L_00435433:
        je short L_00435442
    L_00435435:
        push 2
    L_00435437:
        push 0
    L_00435439:
        push 0
    L_0043543b:
        push eax
    L_0043543c:
        call dword ptr [data_004660c8]
    L_00435442:
        mov al,1
    L_00435444:
        mov ecx,dword ptr [esp+118h]
    L_0043544b:
        pop edi
    L_0043544c:
        pop esi
    L_0043544d:
        pop ebp
    L_0043544e:
        pop ebx
    L_0043544f:
        xor ecx,esp
    L_00435451:
        call asm_security_check_cookie_00458ea5
    L_00435456:
        add esp,10Ch
    L_0043545c:
        ret 8
    }
}
