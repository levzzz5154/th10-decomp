#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F259..0x0045F293: FUN_0045f259
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045f259_0045f259() {
    __asm {
    L_0045f259:
        push 118h
    L_0045f25e:
        push 46C810h
    L_0045f263:
        call asm_SEH_prolog_00454bbc
    L_0045f268:
        mov eax,dword ptr [data_00473660]
    L_0045f26d:
        xor eax,ebp
    L_0045f26f:
        mov dword ptr [ebp-1Ch],eax
    L_0045f272:
        mov ecx,dword ptr [ebp+0Ch]
    L_0045f275:
        mov eax,dword ptr [data_00477698]
    L_0045f27a:
        xor edx,edx
    L_0045f27c:
        cmp eax,edx
    L_0045f27e:
        TH10_REL8(0x74, 0x0045f27e, VA_asm_FUN_0045f259_part_0045f29d)
    L_0045f280:
        mov dword ptr [ebp-4],edx
    L_0045f283:
        push ecx
    L_0045f284:
        push dword ptr [ebp+8]
    L_0045f287:
        call eax
    L_0045f289:
        pop ecx
    L_0045f28a:
        pop ecx
    L_0045f28b:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045f28f:
        jmp asm_target_0045f39c
    }
}

// 0x0045F29D..0x0045F3A2: FUN_0045f259
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045f259_part_0045f29d() {
    __asm {
    L_0045f29d:
        mov eax,dword ptr [ebp+8]
    L_0045f2a0:
        dec eax
    L_0045f2a1:
        je short L_0045f2b9
    L_0045f2a3:
        mov edi,46C7ECh
    L_0045f2a8:
        mov dword ptr [ebp-128h],46C738h
    L_0045f2b2:
        mov esi,0D4h
    L_0045f2b7:
        jmp short L_0045f2cd
    L_0045f2b9:
        mov edi,46C718h
    L_0045f2be:
        mov dword ptr [ebp-128h],46C678h
    L_0045f2c8:
        mov esi,0B9h
    L_0045f2cd:
        mov byte ptr [ebp-20h],dl
    L_0045f2d0:
        push 104h
    L_0045f2d5:
        lea eax,[ebp-124h]
    L_0045f2db:
        push eax
    L_0045f2dc:
        push edx
    L_0045f2dd:
        call dword ptr [data_004660dc]
    L_0045f2e3:
        test eax,eax
    L_0045f2e5:
        jne short L_0045f2fa
    L_0045f2e7:
        push 46B02Ch
    L_0045f2ec:
        lea eax,[ebp-124h]
    L_0045f2f2:
        push eax
    L_0045f2f3:
        call asm_FUN_0045bd80_0045bd80
    L_0045f2f8:
        pop ecx
    L_0045f2f9:
        pop ecx
    L_0045f2fa:
        lea ebx,[ebp-124h]
    L_0045f300:
        mov eax,ebx
    L_0045f302:
        push eax
    L_0045f303:
        call asm_strlen_00456720
    L_0045f308:
        pop ecx
    L_0045f309:
        add eax,0Bh
    L_0045f30c:
        cmp eax,3Ch
    L_0045f30f:
        jbe short L_0045f336
    L_0045f311:
        mov eax,ebx
    L_0045f313:
        push eax
    L_0045f314:
        call asm_strlen_00456720
    L_0045f319:
        mov ebx,eax
    L_0045f31b:
        lea eax,[ebp-124h]
    L_0045f321:
        sub eax,31h
    L_0045f324:
        add ebx,eax
    L_0045f326:
        push 3
    L_0045f328:
        push 46B028h
    L_0045f32d:
        push ebx
    L_0045f32e:
        call asm_strncpy_00452960
    L_0045f333:
        add esp,10h
    L_0045f336:
        push ebx
    L_0045f337:
        call asm_strlen_00456720
    L_0045f33c:
        pop ecx
    L_0045f33d:
        lea eax,[eax+esi+0Ch]
    L_0045f341:
        add eax,3
    L_0045f344:
        and eax,0FFFFFFFCh
    L_0045f347:
        call asm_chkstk_00458ec0
    L_0045f34c:
        mov dword ptr [ebp-18h],esp
    L_0045f34f:
        mov esi,esp
    L_0045f351:
        push edi
    L_0045f352:
        push esi
    L_0045f353:
        call asm_FUN_0045bd80_0045bd80
    L_0045f358:
        mov edi,46B008h
    L_0045f35d:
        push edi
    L_0045f35e:
        push esi
    L_0045f35f:
        call asm_FUN_0045bd90_0045bd90
    L_0045f364:
        push 46C66Ch
    L_0045f369:
        push esi
    L_0045f36a:
        call asm_FUN_0045bd90_0045bd90
    L_0045f36f:
        push ebx
    L_0045f370:
        push esi
    L_0045f371:
        call asm_FUN_0045bd90_0045bd90
    L_0045f376:
        push edi
    L_0045f377:
        push esi
    L_0045f378:
        call asm_FUN_0045bd90_0045bd90
    L_0045f37d:
        push dword ptr [ebp-128h]
    L_0045f383:
        push esi
    L_0045f384:
        call asm_FUN_0045bd90_0045bd90
    L_0045f389:
        push 12010h
    L_0045f38e:
        push 46AFE0h
    L_0045f393:
        push esi
    L_0045f394:
        call asm_crtMessageBoxA_0045f3d0
    L_0045f399:
        add esp,3Ch
    L_0045f39c:
        push 3
    L_0045f39e:
        call asm_exit_004576fd
    }
}
