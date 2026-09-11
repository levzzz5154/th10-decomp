#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041A200..0x0041AAC6: FUN_0041a200
// Naked body preserves the retail register/stack ABI.

// 0x0042B1E0..0x0042B413: FUN_0042b1e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b1e0_0042b1e0() {
    __asm {
    L_0042b1e0:
        mov eax,dword ptr [ebx]
    L_0042b1e2:
        sub esp,0Ch
    L_0042b1e5:
        test eax,eax
    L_0042b1e7:
        jne short L_0042b1f0
    L_0042b1e9:
        or eax,0FFFFFFFFh
    L_0042b1ec:
        add esp,0Ch
    L_0042b1ef:
        ret
    L_0042b1f0:
        push ebp
    L_0042b1f1:
        push 200000h
    L_0042b1f6:
        call asm_malloc_00452706
    L_0042b1fb:
        mov ecx,dword ptr [ebx]
    L_0042b1fd:
        mov edx,dword ptr [ecx]
    L_0042b1ff:
        mov dword ptr [esp+8],eax
    L_0042b203:
        mov dword ptr [eax],edx
    L_0042b205:
        mov edx,dword ptr [ecx+4]
    L_0042b208:
        mov dword ptr [eax+4],edx
    L_0042b20b:
        mov edx,dword ptr [ecx+8]
    L_0042b20e:
        mov dword ptr [eax+8],edx
    L_0042b211:
        mov edx,dword ptr [ecx+0Ch]
    L_0042b214:
        mov dword ptr [eax+0Ch],edx
    L_0042b217:
        mov edx,dword ptr [ecx+10h]
    L_0042b21a:
        mov dword ptr [eax+10h],edx
    L_0042b21d:
        mov ecx,dword ptr [ecx+14h]
    L_0042b220:
        add esp,4
    L_0042b223:
        mov dword ptr [eax+14h],ecx
    L_0042b226:
        mov ebp,18h
    L_0042b22b:
        xor eax,eax
    L_0042b22d:
        push esi
    L_0042b22e:
        mov dword ptr [esp+0Ch],ebp
    L_0042b232:
        mov dword ptr [esp+10h],eax
    L_0042b236:
        lea edx,[ebx+14h]
    L_0042b239:
        push edi
    L_0042b23a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042b240:
        cmp word ptr [edx-0Ch],5243h
    L_0042b246:
        jne short L_0042b2a3
    L_0042b248:
        mov dword ptr [edx],eax
    L_0042b24a:
        xor ecx,ecx
    L_0042b24c:
        mov eax,edx
    L_0042b24e:
        mov edi,0B3Eh
    L_0042b253:
        movzx ebp,byte ptr [eax-3]
    L_0042b257:
        movzx esi,byte ptr [eax-4]
    L_0042b25b:
        add esi,ebp
    L_0042b25d:
        movzx ebp,byte ptr [eax-2]
    L_0042b261:
        add esi,ebp
    L_0042b263:
        movzx ebp,byte ptr [eax-1]
    L_0042b267:
        add esi,ebp
    L_0042b269:
        movzx ebp,byte ptr [eax+1]
    L_0042b26d:
        add esi,ebp
    L_0042b26f:
        movzx ebp,byte ptr [eax]
    L_0042b272:
        add ebp,ecx
    L_0042b274:
        add eax,6
    L_0042b277:
        dec edi
    L_0042b278:
        lea ecx,[esi+ebp]
    L_0042b27b:
        jne short L_0042b253
    L_0042b27d:
        mov ebp,dword ptr [esp+10h]
    L_0042b281:
        mov eax,dword ptr [esp+0Ch]
    L_0042b285:
        lea edi,[eax+ebp]
    L_0042b288:
        mov eax,dword ptr [esp+14h]
    L_0042b28c:
        mov dword ptr [edx-8],ecx
    L_0042b28f:
        mov ecx,10DFh
    L_0042b294:
        lea esi,[edx-0Ch]
    L_0042b297:
        add ebp,437Ch
    L_0042b29d:
        rep movsd
    L_0042b29f:
        mov dword ptr [esp+10h],ebp
    L_0042b2a3:
        inc eax
    L_0042b2a4:
        add edx,437Ch
    L_0042b2aa:
        cmp eax,7
    L_0042b2ad:
        mov dword ptr [esp+14h],eax
    L_0042b2b1:
        jb short L_0042b240
    L_0042b2b3:
        xor ecx,ecx
    L_0042b2b5:
        lea eax,[ebx+1D876h]
    L_0042b2bb:
        mov edx,110h
    L_0042b2c0:
        movzx edi,byte ptr [eax-1]
    L_0042b2c4:
        movzx esi,byte ptr [eax-2]
    L_0042b2c8:
        add esi,edi
    L_0042b2ca:
        movzx edi,byte ptr [eax+1]
    L_0042b2ce:
        add esi,edi
    L_0042b2d0:
        movzx edi,byte ptr [eax]
    L_0042b2d3:
        add edi,ecx
    L_0042b2d5:
        add eax,4
    L_0042b2d8:
        dec edx
    L_0042b2d9:
        lea ecx,[edi+esi]
    L_0042b2dc:
        jne short L_0042b2c0
    L_0042b2de:
        mov dword ptr [ebx+1D870h],ecx
    L_0042b2e4:
        mov ecx,dword ptr [esp+0Ch]
    L_0042b2e8:
        lea edi,[ecx+ebp]
    L_0042b2eb:
        lea esi,[ebx+1D86Ch]
    L_0042b2f1:
        mov ecx,112h
    L_0042b2f6:
        rep movsd
    L_0042b2f8:
        mov edx,dword ptr [ebx]
    L_0042b2fa:
        add ebp,430h
    L_0042b300:
        mov dword ptr [edx+14h],ebp
    L_0042b303:
        mov eax,dword ptr [ebx]
    L_0042b305:
        mov edx,dword ptr [eax+14h]
    L_0042b308:
        lea ecx,[eax+10h]
    L_0042b30b:
        mov eax,dword ptr [esp+0Ch]
    L_0042b30f:
        push ecx
    L_0042b310:
        push edx
    L_0042b311:
        add eax,18h
    L_0042b314:
        push eax
    L_0042b315:
        call asm_FUN_004359b0_004359b0
    L_0042b31a:
        mov edi,eax
    L_0042b31c:
        mov eax,dword ptr [ebx]
    L_0042b31e:
        mov ecx,dword ptr [eax+10h]
    L_0042b321:
        add ecx,18h
    L_0042b324:
        mov dword ptr [eax+4],ecx
    L_0042b327:
        mov edx,dword ptr [ebx]
    L_0042b329:
        mov eax,dword ptr [edx+10h]
    L_0042b32c:
        push eax
    L_0042b32d:
        push 10h
    L_0042b32f:
        push 35h
    L_0042b331:
        push eax
    L_0042b332:
        push edi
    L_0042b333:
        mov al,0ACh
    L_0042b335:
        call asm_EncryptDatBuffer_0044b220
    L_0042b33a:
        push 46E848h
    L_0042b33f:
        call asm_File_OpenSharedWrite_0044b620
    L_0042b344:
        test eax,eax
    L_0042b346:
        je short L_0042b352
    L_0042b348:
        pop edi
    L_0042b349:
        pop esi
    L_0042b34a:
        or eax,0FFFFFFFFh
    L_0042b34d:
        pop ebp
    L_0042b34e:
        add esp,0Ch
    L_0042b351:
        ret
    L_0042b352:
        mov eax,dword ptr [data_00474c38]
    L_0042b357:
        cmp eax,0FFFFFFFFh
    L_0042b35a:
        mov ebp,dword ptr [data_004660cc]
    L_0042b360:
        je short L_0042b39a
    L_0042b362:
        mov edx,dword ptr [ebx]
    L_0042b364:
        push 0
    L_0042b366:
        lea ecx,[esp+18h]
    L_0042b36a:
        push ecx
    L_0042b36b:
        push 18h
    L_0042b36d:
        push edx
    L_0042b36e:
        push eax
    L_0042b36f:
        call dword ptr [data_004660d4]
    L_0042b375:
        cmp dword ptr [esp+14h],18h
    L_0042b37a:
        mov eax,dword ptr [data_00474c38]
    L_0042b37f:
        je short L_0042b39a
    L_0042b381:
        push eax
    L_0042b382:
        call ebp
    L_0042b384:
        push 4922A4h
    L_0042b389:
        call dword ptr [data_004660b4]
    L_0042b38f:
        dec byte ptr [data_0049231e]
    L_0042b395:
        mov eax,dword ptr [data_00474c38]
    L_0042b39a:
        cmp eax,0FFFFFFFFh
    L_0042b39d:
        mov ecx,dword ptr [ebx]
    L_0042b39f:
        mov esi,dword ptr [ecx+10h]
    L_0042b3a2:
        je short L_0042b3f1
    L_0042b3a4:
        push 0
    L_0042b3a6:
        lea edx,[esp+18h]
    L_0042b3aa:
        push edx
    L_0042b3ab:
        push esi
    L_0042b3ac:
        push edi
    L_0042b3ad:
        push eax
    L_0042b3ae:
        call dword ptr [data_004660d4]
    L_0042b3b4:
        cmp esi,dword ptr [esp+14h]
    L_0042b3b8:
        je short L_0042b3d3
    L_0042b3ba:
        mov eax,dword ptr [data_00474c38]
    L_0042b3bf:
        push eax
    L_0042b3c0:
        call ebp
    L_0042b3c2:
        push 4922A4h
    L_0042b3c7:
        call dword ptr [data_004660b4]
    L_0042b3cd:
        dec byte ptr [data_0049231e]
    L_0042b3d3:
        mov eax,dword ptr [data_00474c38]
    L_0042b3d8:
        cmp eax,0FFFFFFFFh
    L_0042b3db:
        je short L_0042b3f1
    L_0042b3dd:
        push eax
    L_0042b3de:
        call ebp
    L_0042b3e0:
        push 4922A4h
    L_0042b3e5:
        call dword ptr [data_004660b4]
    L_0042b3eb:
        dec byte ptr [data_0049231e]
    L_0042b3f1:
        test edi,edi
    L_0042b3f3:
        je short L_0042b3fe
    L_0042b3f5:
        push edi
    L_0042b3f6:
        call asm_free_00452422
    L_0042b3fb:
        add esp,4
    L_0042b3fe:
        mov ecx,dword ptr [esp+0Ch]
    L_0042b402:
        push ecx
    L_0042b403:
        call asm_free_00452422
    L_0042b408:
        add esp,4
    L_0042b40b:
        pop edi
    L_0042b40c:
        pop esi
    L_0042b40d:
        xor eax,eax
    L_0042b40f:
        pop ebp
    L_0042b410:
        add esp,0Ch
    L_0042b413:
        ret
    }
}
