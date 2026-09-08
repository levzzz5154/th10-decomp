#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004231D0..0x0042336A: FUN_004231d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004231d0_004231d0() {
    __asm {
    L_004231d0:
        push ecx
    L_004231d1:
        mov eax,dword ptr [data_00477810]
    L_004231d6:
        cmp dword ptr [eax+5Ch],1
    L_004231da:
        jne short L_004231f7
    L_004231dc:
        mov eax,dword ptr [data_00491ff4]
    L_004231e1:
        and eax,1000h
    L_004231e6:
        neg eax
    L_004231e8:
        sbb eax,eax
    L_004231ea:
        and eax,0FFFFFFFEh
    L_004231ed:
        add eax,4
    L_004231f0:
        mov dword ptr [data_00491fb8],eax
    L_004231f5:
        pop ecx
    L_004231f6:
        ret
    L_004231f7:
        mov dword ptr [edi+4],6
    L_004231fe:
        mov ecx,dword ptr [edi+20h]
    L_00423201:
        xor edx,edx
    L_00423203:
        test cl,1
    L_00423206:
        jne short L_00423222
    L_00423208:
        or ecx,1
    L_0042320b:
        mov dword ptr [edi+14h],edx
    L_0042320e:
        mov dword ptr [edi+10h],0FFF0BDC1h
    L_00423215:
        mov dword ptr [edi+18h],edx
    L_00423218:
        mov dword ptr [edi+1Ch],476F78h
    L_0042321f:
        mov dword ptr [edi+20h],ecx
    L_00423222:
        mov ecx,dword ptr [data_004776e0]
    L_00423228:
        mov dword ptr [edi+14h],edx
    L_0042322b:
        mov dword ptr [edi+18h],edx
    L_0042322e:
        mov dword ptr [edi+10h],0FFFFFFFFh
    L_00423235:
        mov edx,dword ptr [eax+58h]
    L_00423238:
        push ebx
    L_00423239:
        push ebp
    L_0042323a:
        or edx,10h
    L_0042323d:
        push esi
    L_0042323e:
        mov esi,dword ptr [data_00491c10]
    L_00423244:
        mov dword ptr [eax+58h],edx
    L_00423247:
        mov ebp,dword ptr [ecx+8998h]
    L_0042324d:
        call asm_FUN_00449950_00449950
    L_00423252:
        mov ebx,eax
    L_00423254:
        mov ecx,dword ptr [ebx+35Ch]
    L_0042325a:
        or ecx,40000000h
    L_00423260:
        push 0
    L_00423262:
        mov dword ptr [ebx+35Ch],ecx
    L_00423268:
        push ebx
    L_00423269:
        mov ecx,ebp
    L_0042326b:
        mov dword ptr [ebx+20h],0Fh
    L_00423272:
        call asm_FUN_00449870_00449870
    L_00423277:
        mov esi,dword ptr [data_00491c10]
    L_0042327d:
        lea eax,[esp+0Ch]
    L_00423281:
        mov edx,esi
    L_00423283:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00423288:
        mov eax,dword ptr [esp+0Ch]
    L_0042328c:
        push 1C0h
    L_00423291:
        push 180h
    L_00423296:
        push 10h
    L_00423298:
        push 20h
    L_0042329a:
        push eax
    L_0042329b:
        mov dword ptr [edi+1D8h],eax
    L_004232a1:
        call asm_FUN_00424480_00424480
    L_004232a6:
        mov edx,dword ptr [data_0047770c]
    L_004232ac:
        mov ebp,dword ptr [edx+9EC8h]
    L_004232b2:
        mov dword ptr [edi+2C4h],ebp
    L_004232b8:
        call asm_FUN_00449950_00449950
    L_004232bd:
        mov ebx,eax
    L_004232bf:
        mov ecx,dword ptr [ebx+35Ch]
    L_004232c5:
        or ecx,40000000h
    L_004232cb:
        push 80h
    L_004232d0:
        mov dword ptr [ebx+35Ch],ecx
    L_004232d6:
        push ebx
    L_004232d7:
        mov ecx,ebp
    L_004232d9:
        mov dword ptr [ebx+20h],0Fh
    L_004232e0:
        call asm_FUN_00449870_00449870
    L_004232e5:
        mov edx,dword ptr [data_00491c10]
    L_004232eb:
        lea eax,[esp+0Ch]
    L_004232ef:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_004232f4:
        mov eax,dword ptr [esp+0Ch]
    L_004232f8:
        push 46E0D8h
    L_004232fd:
        push 0
    L_004232ff:
        mov dword ptr [edi+1D4h],eax
    L_00423305:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_0042330a:
        test byte ptr [data_00491d78],10h
    L_00423311:
        pop esi
    L_00423312:
        pop ebp
    L_00423313:
        pop ebx
    L_00423314:
        je short L_00423329
    L_00423316:
        push 0
    L_00423318:
        push 4
    L_0042331a:
        mov edx,46DF98h
    L_0042331f:
        mov eax,492590h
    L_00423324:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00423329:
        push 0
    L_0042332b:
        push 2
    L_0042332d:
        mov edx,46DF98h
    L_00423332:
        mov eax,492590h
    L_00423337:
        call asm_AnimationManager_RegisterResource_0043e460
    L_0042333c:
        mov ecx,dword ptr [data_0047783c]
    L_00423342:
        mov byte ptr [ecx+1D8A3h],1
    L_00423349:
        mov dword ptr [edi+1E4h],0
    L_00423353:
        mov edx,dword ptr [data_00476f78]
    L_00423359:
        mov dword ptr [edi+2C0h],edx
    L_0042335f:
        mov dword ptr [data_00476f78],3F800000h
    L_00423369:
        pop ecx
    L_0042336a:
        ret
    }
}
