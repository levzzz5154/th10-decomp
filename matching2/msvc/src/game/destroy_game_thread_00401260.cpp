#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401000..0x004010FA: GameThread_ConstructOverlay
// Naked body preserves the retail register/stack ABI.

// 0x00401260..0x00401432: DestroyGameThread
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DestroyGameThread_00401260() {
    __asm {
    L_00401260:
        push 0FFFFFFFFh
    L_00401262:
        push 4652F9h
    L_00401267:
        mov eax,dword ptr fs:[0]
    L_0040126d:
        push eax
    L_0040126e:
        mov dword ptr fs:[0],esp
    L_00401275:
        push ecx
    L_00401276:
        push ebx
    L_00401277:
        push ebp
    L_00401278:
        mov ebp,dword ptr [esp+1Ch]
    L_0040127c:
        push esi
    L_0040127d:
        push edi
    L_0040127e:
        mov dword ptr [ebp],46CB14h
    L_00401285:
        mov dword ptr [esp+1Ch],1
    L_0040128d:
        mov esi,dword ptr [ebp+0Ch]
    L_00401290:
        test esi,esi
    L_00401292:
        mov eax,dword ptr [data_00491be4]
    L_00401297:
        mov edi,dword ptr [data_004660b0]
    L_0040129d:
        mov ebx,dword ptr [data_004660b4]
    L_004012a3:
        mov dword ptr [esp+10h],eax
    L_004012a7:
        je short L_004012ce
    L_004012a9:
        push 492274h
    L_004012ae:
        call edi
    L_004012b0:
        inc byte ptr [data_0049231c]
    L_004012b6:
        mov edx,dword ptr [esp+10h]
    L_004012ba:
        mov ecx,esi
    L_004012bc:
        call asm_Scheduler_Remove_00449f60
    L_004012c1:
        push 492274h
    L_004012c6:
        call ebx
    L_004012c8:
        dec byte ptr [data_0049231c]
    L_004012ce:
        mov esi,dword ptr [ebp+10h]
    L_004012d1:
        test esi,esi
    L_004012d3:
        mov ecx,dword ptr [data_00491be4]
    L_004012d9:
        mov dword ptr [esp+10h],ecx
    L_004012dd:
        je short L_00401304
    L_004012df:
        push 492274h
    L_004012e4:
        call edi
    L_004012e6:
        inc byte ptr [data_0049231c]
    L_004012ec:
        mov edx,dword ptr [esp+10h]
    L_004012f0:
        mov ecx,esi
    L_004012f2:
        call asm_Scheduler_Remove_00449f60
    L_004012f7:
        push 492274h
    L_004012fc:
        call ebx
    L_004012fe:
        dec byte ptr [data_0049231c]
    L_00401304:
        mov esi,dword ptr [ebp+89A8h]
    L_0040130a:
        test esi,esi
    L_0040130c:
        mov edx,dword ptr [data_00491be4]
    L_00401312:
        mov dword ptr [esp+10h],edx
    L_00401316:
        je short L_0040133d
    L_00401318:
        push 492274h
    L_0040131d:
        call edi
    L_0040131f:
        inc byte ptr [data_0049231c]
    L_00401325:
        mov edx,dword ptr [esp+10h]
    L_00401329:
        mov ecx,esi
    L_0040132b:
        call asm_Scheduler_Remove_00449f60
    L_00401330:
        push 492274h
    L_00401335:
        call ebx
    L_00401337:
        dec byte ptr [data_0049231c]
    L_0040133d:
        mov esi,dword ptr [data_00491c10]
    L_00401343:
        mov edi,dword ptr [esi+3AD074h]
    L_00401349:
        add esi,3AD074h
    L_0040134f:
        test edi,edi
    L_00401351:
        je short L_00401369
    L_00401353:
        call asm_FUN_00447810_00447810
    L_00401358:
        mov eax,dword ptr [esi]
    L_0040135a:
        push eax
    L_0040135b:
        call asm_free_004524a1
    L_00401360:
        add esp,4
    L_00401363:
        mov dword ptr [esi],0
    L_00401369:
        mov esi,dword ptr [data_00491c10]
    L_0040136f:
        mov edi,dword ptr [esi+3AD06Ch]
    L_00401375:
        add esi,3AD06Ch
    L_0040137b:
        test edi,edi
    L_0040137d:
        je short L_00401395
    L_0040137f:
        call asm_FUN_00447810_00447810
    L_00401384:
        mov ecx,dword ptr [esi]
    L_00401386:
        push ecx
    L_00401387:
        call asm_free_004524a1
    L_0040138c:
        add esp,4
    L_0040138f:
        mov dword ptr [esi],0
    L_00401395:
        mov esi,dword ptr [data_00491c10]
    L_0040139b:
        mov edi,dword ptr [esi+3AD078h]
    L_004013a1:
        add esi,3AD078h
    L_004013a7:
        test edi,edi
    L_004013a9:
        je short L_004013c1
    L_004013ab:
        call asm_FUN_00447810_00447810
    L_004013b0:
        mov edx,dword ptr [esi]
    L_004013b2:
        push edx
    L_004013b3:
        call asm_free_004524a1
    L_004013b8:
        add esp,4
    L_004013bb:
        mov dword ptr [esi],0
    L_004013c1:
        mov eax,dword ptr [ebp+718h]
    L_004013c7:
        test eax,eax
    L_004013c9:
        mov dword ptr [data_004776e0],0
    L_004013d3:
        je short L_004013de
    L_004013d5:
        push eax
    L_004013d6:
        call asm_free_00452422
    L_004013db:
        add esp,4
    L_004013de:
        xor ecx,ecx
    L_004013e0:
        mov dword ptr [ebp+718h],ecx
    L_004013e6:
        mov eax,dword ptr [ebp+36Ch]
    L_004013ec:
        cmp eax,ecx
    L_004013ee:
        je short L_00401418
    L_004013f0:
        push eax
    L_004013f1:
        call asm_free_00452422
    L_004013f6:
        add esp,4
    L_004013f9:
        pop edi
    L_004013fa:
        pop esi
    L_004013fb:
        mov dword ptr [ebp+36Ch],0
    L_00401405:
        pop ebp
    L_00401406:
        pop ebx
    L_00401407:
        mov ecx,dword ptr [esp+4]
    L_0040140b:
        mov dword ptr fs:[0],ecx
    L_00401412:
        add esp,10h
    L_00401415:
        ret 4
    L_00401418:
        pop edi
    L_00401419:
        mov dword ptr [ebp+36Ch],ecx
    L_0040141f:
        mov ecx,dword ptr [esp+10h]
    L_00401423:
        pop esi
    L_00401424:
        pop ebp
    L_00401425:
        pop ebx
    L_00401426:
        mov dword ptr fs:[0],ecx
    L_0040142d:
        add esp,10h
    L_00401430:
        ret 4
    }
}
