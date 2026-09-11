#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF80..0x0041FFF0: FUN_0041ff80
// Naked body preserves the retail register/stack ABI.

// 0x00420270..0x00420394: FUN_00420270
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420270_00420270() {
    __asm {
    L_00420270:
        push ebp
    L_00420271:
        push esi
    L_00420272:
        push edi
    L_00420273:
        mov esi,474DD4h
    L_00420278:
        mov edi,eax
    L_0042027a:
        call asm_Platform_StopWorker_0044c150
    L_0042027f:
        mov esi,492254h
    L_00420284:
        mov dword ptr [data_004977b4],2
    L_0042028e:
        call asm_Platform_StopWorker_0044c150
    L_00420293:
        mov eax,dword ptr [data_0049238c]
    L_00420298:
        xor ebp,ebp
    L_0042029a:
        cmp eax,ebp
    L_0042029c:
        je short L_004202ad
    L_0042029e:
        push eax
    L_0042029f:
        call asm_free_00452422
    L_004202a4:
        add esp,4
    L_004202a7:
        mov dword ptr [data_0049238c],ebp
    L_004202ad:
        push ebx
    L_004202ae:
        call asm_Recovery_ReleaseGlobalStates_004203f0
    L_004202b3:
        mov ebx,dword ptr [data_00477708]
    L_004202b9:
        call asm_Platform_ReleaseOwnedHandle_00413450
    L_004202be:
        mov esi,dword ptr [data_00491c10]
    L_004202c4:
        mov eax,dword ptr [esi+3ADA74h]
    L_004202ca:
        add esi,3ADA74h
    L_004202d0:
        cmp eax,ebp
    L_004202d2:
        pop ebx
    L_004202d3:
        je short L_004202dd
    L_004202d5:
        mov ecx,dword ptr [eax]
    L_004202d7:
        push eax
    L_004202d8:
        call dword ptr [ecx+8]
    L_004202db:
        mov dword ptr [esi],ebp
    L_004202dd:
        push ebp
    L_004202de:
        push 4
    L_004202e0:
        mov edx,46DF98h
    L_004202e5:
        mov eax,492590h
    L_004202ea:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004202ef:
        call asm_FontCache_DeleteGdiObjectsRetail_00437d10
    L_004202f4:
        mov eax,dword ptr [edi+10h]
    L_004202f7:
        cmp eax,ebp
    L_004202f9:
        je short L_00420311
    L_004202fb:
        mov edx,dword ptr [eax]
    L_004202fd:
        push eax
    L_004202fe:
        call dword ptr [edx+20h]
    L_00420301:
        mov eax,dword ptr [edi+10h]
    L_00420304:
        cmp eax,ebp
    L_00420306:
        je short L_00420311
    L_00420308:
        mov ecx,dword ptr [eax]
    L_0042030a:
        push eax
    L_0042030b:
        call dword ptr [ecx+8]
    L_0042030e:
        mov dword ptr [edi+10h],ebp
    L_00420311:
        mov eax,dword ptr [edi+14h]
    L_00420314:
        cmp eax,ebp
    L_00420316:
        je short L_0042032e
    L_00420318:
        mov edx,dword ptr [eax]
    L_0042031a:
        push eax
    L_0042031b:
        call dword ptr [edx+20h]
    L_0042031e:
        mov eax,dword ptr [edi+14h]
    L_00420321:
        cmp eax,ebp
    L_00420323:
        je short L_0042032e
    L_00420325:
        mov ecx,dword ptr [eax]
    L_00420327:
        push eax
    L_00420328:
        call dword ptr [ecx+8]
    L_0042032b:
        mov dword ptr [edi+14h],ebp
    L_0042032e:
        mov eax,dword ptr [edi+0Ch]
    L_00420331:
        cmp eax,ebp
    L_00420333:
        je short L_0042033e
    L_00420335:
        mov edx,dword ptr [eax]
    L_00420337:
        push eax
    L_00420338:
        call dword ptr [edx+8]
    L_0042033b:
        mov dword ptr [edi+0Ch],ebp
    L_0042033e:
        mov eax,dword ptr [data_00491d44]
    L_00420343:
        cmp eax,ebp
    L_00420345:
        je short L_00420385
    L_00420347:
        lea esi,[eax+4]
    L_0042034a:
        mov edi,eax
    L_0042034c:
        mov eax,dword ptr [esi]
    L_0042034e:
        cmp eax,ebp
    L_00420350:
        je short L_00420359
    L_00420352:
        push eax
    L_00420353:
        call dword ptr [data_00466288]
    L_00420359:
        mov eax,dword ptr [edi+8]
    L_0042035c:
        push eax
    L_0042035d:
        call dword ptr [data_00466274]
    L_00420363:
        mov dword ptr [esi],ebp
    L_00420365:
        mov esi,dword ptr [data_00491d44]
    L_0042036b:
        cmp esi,ebp
    L_0042036d:
        mov edi,esi
    L_0042036f:
        je short L_0042037f
    L_00420371:
        call asm_TimerWin32_Release_004203c0
    L_00420376:
        push edi
    L_00420377:
        call asm_free_004524a1
    L_0042037c:
        add esp,4
    L_0042037f:
        mov dword ptr [data_00491d44],ebp
    L_00420385:
        mov esi,497990h
    L_0042038a:
        call asm_DatArchive_Close_00434d10
    L_0042038f:
        pop edi
    L_00420390:
        pop esi
    L_00420391:
        xor eax,eax
    L_00420393:
        pop ebp
    L_00420394:
        ret
    }
}
