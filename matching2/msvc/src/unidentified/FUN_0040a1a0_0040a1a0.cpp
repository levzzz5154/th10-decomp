#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A1A0..0x0040A33B: FUN_0040a1a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a1a0_0040a1a0() {
    __asm {
    L_0040a1a0:
        mov eax,dword ptr fs:[0]
    L_0040a1a6:
        push 0FFFFFFFFh
    L_0040a1a8:
        push 4657E9h
    L_0040a1ad:
        push eax
    L_0040a1ae:
        mov dword ptr fs:[0],esp
    L_0040a1b5:
        push ebx
    L_0040a1b6:
        push ebp
    L_0040a1b7:
        push esi
    L_0040a1b8:
        push edi
    L_0040a1b9:
        mov dword ptr [esp+18h],1
    L_0040a1c1:
        mov esi,dword ptr [esp+20h]
    L_0040a1c5:
        call asm_FUN_00409eb0_00409eb0
    L_0040a1ca:
        mov edi,dword ptr [esi+8]
    L_0040a1cd:
        test edi,edi
    L_0040a1cf:
        mov ebx,dword ptr [data_00491be4]
    L_0040a1d5:
        mov ebp,dword ptr [data_004660b0]
    L_0040a1db:
        mov esi,dword ptr [data_004660b4]
    L_0040a1e1:
        je short L_0040a206
    L_0040a1e3:
        push 492274h
    L_0040a1e8:
        call ebp
    L_0040a1ea:
        inc byte ptr [data_0049231c]
    L_0040a1f0:
        mov ecx,edi
    L_0040a1f2:
        mov edx,ebx
    L_0040a1f4:
        call asm_Scheduler_Remove_00449f60
    L_0040a1f9:
        push 492274h
    L_0040a1fe:
        call esi
    L_0040a200:
        dec byte ptr [data_0049231c]
    L_0040a206:
        mov eax,dword ptr [esp+20h]
    L_0040a20a:
        mov edi,dword ptr [eax+0Ch]
    L_0040a20d:
        test edi,edi
    L_0040a20f:
        mov ebx,dword ptr [data_00491be4]
    L_0040a215:
        je short L_0040a23a
    L_0040a217:
        push 492274h
    L_0040a21c:
        call ebp
    L_0040a21e:
        inc byte ptr [data_0049231c]
    L_0040a224:
        mov ecx,edi
    L_0040a226:
        mov edx,ebx
    L_0040a228:
        call asm_Scheduler_Remove_00449f60
    L_0040a22d:
        push 492274h
    L_0040a232:
        call esi
    L_0040a234:
        dec byte ptr [data_0049231c]
    L_0040a23a:
        mov esi,dword ptr [data_0047770c]
    L_0040a240:
        test esi,esi
    L_0040a242:
        je short L_0040a253
    L_0040a244:
        push esi
    L_0040a245:
        call asm_FUN_004145f0_004145f0
    L_0040a24a:
        push esi
    L_0040a24b:
        call asm_free_004524a1
    L_0040a250:
        add esp,4
    L_0040a253:
        mov esi,dword ptr [data_00477834]
    L_0040a259:
        test esi,esi
    L_0040a25b:
        je short L_0040a26c
    L_0040a25d:
        push esi
    L_0040a25e:
        call asm_FUN_00424ed0_00424ed0
    L_0040a263:
        push esi
    L_0040a264:
        call asm_free_004524a1
    L_0040a269:
        add esp,4
    L_0040a26c:
        mov esi,dword ptr [data_004776f0]
    L_0040a272:
        test esi,esi
    L_0040a274:
        je short L_0040a285
    L_0040a276:
        push esi
    L_0040a277:
        call asm_ItemManager_DestroyRetail_00405f70
    L_0040a27c:
        push esi
    L_0040a27d:
        call asm_free_004524a1
    L_0040a282:
        add esp,4
    L_0040a285:
        mov esi,dword ptr [data_00477704]
    L_0040a28b:
        test esi,esi
    L_0040a28d:
        je short L_0040a29f
    L_0040a28f:
        mov eax,esi
    L_0040a291:
        call asm_FUN_0040d530_0040d530
    L_0040a296:
        push esi
    L_0040a297:
        call asm_free_004524a1
    L_0040a29c:
        add esp,4
    L_0040a29f:
        mov esi,dword ptr [data_004776ec]
    L_0040a2a5:
        test esi,esi
    L_0040a2a7:
        je short L_0040a2b8
    L_0040a2a9:
        push esi
    L_0040a2aa:
        call asm_Recovery_ReleaseRawPairAndReset_00405620
    L_0040a2af:
        push esi
    L_0040a2b0:
        call asm_free_004524a1
    L_0040a2b5:
        add esp,4
    L_0040a2b8:
        mov esi,dword ptr [data_00477818]
    L_0040a2be:
        test esi,esi
    L_0040a2c0:
        je short L_0040a2d1
    L_0040a2c2:
        push esi
    L_0040a2c3:
        call asm_FUN_0041adf0_0041adf0
    L_0040a2c8:
        push esi
    L_0040a2c9:
        call asm_free_004524a1
    L_0040a2ce:
        add esp,4
    L_0040a2d1:
        mov esi,dword ptr [data_00477840]
    L_0040a2d7:
        test esi,esi
    L_0040a2d9:
        je short L_0040a2ea
    L_0040a2db:
        push esi
    L_0040a2dc:
        call asm_FUN_0042b570_0042b570
    L_0040a2e1:
        push esi
    L_0040a2e2:
        call asm_free_004524a1
    L_0040a2e7:
        add esp,4
    L_0040a2ea:
        mov ecx,dword ptr [esp+20h]
    L_0040a2ee:
        mov eax,dword ptr [ecx+620h]
    L_0040a2f4:
        test eax,eax
    L_0040a2f6:
        mov dword ptr [data_004776f8],0
    L_0040a300:
        je short L_0040a30b
    L_0040a302:
        push eax
    L_0040a303:
        call asm_free_00452422
    L_0040a308:
        add esp,4
    L_0040a30b:
        mov esi,dword ptr [esp+20h]
    L_0040a30f:
        mov dword ptr [esi+620h],0
    L_0040a319:
        add esi,10h
    L_0040a31c:
        mov dword ptr [esi],4703E4h
    L_0040a322:
        call asm_Platform_StopWorker_0044c150
    L_0040a327:
        mov ecx,dword ptr [esp+10h]
    L_0040a32b:
        pop edi
    L_0040a32c:
        pop esi
    L_0040a32d:
        pop ebp
    L_0040a32e:
        mov dword ptr fs:[0],ecx
    L_0040a335:
        pop ebx
    L_0040a336:
        add esp,0Ch
    L_0040a339:
        ret 4
    }
}
