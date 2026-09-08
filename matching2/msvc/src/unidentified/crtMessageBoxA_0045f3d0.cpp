#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F3D0..0x0045F4C8: ___crtMessageBoxA
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtMessageBoxA_0045f3d0() {
    __asm {
    L_0045f3d0:
        push ebp
    L_0045f3d1:
        mov ebp,esp
    L_0045f3d3:
        sub esp,10h
    L_0045f3d6:
        push ebx
    L_0045f3d7:
        xor ebx,ebx
    L_0045f3d9:
        cmp dword ptr [data_0047769c],ebx
    L_0045f3df:
        push esi
    L_0045f3e0:
        push edi
    L_0045f3e1:
        jne short L_0045f450
    L_0045f3e3:
        push 46C880h
    L_0045f3e8:
        call dword ptr [data_004661b8]
    L_0045f3ee:
        mov edi,eax
    L_0045f3f0:
        cmp edi,ebx
    L_0045f3f2:
        je asm_target_0045f48b
    L_0045f3f8:
        mov esi,dword ptr [data_00466158]
    L_0045f3fe:
        push 46C874h
    L_0045f403:
        push edi
    L_0045f404:
        call esi
    L_0045f406:
        test eax,eax
    L_0045f408:
        mov dword ptr [data_0047769c],eax
    L_0045f40d:
        je short L_0045f48b
    L_0045f40f:
        push 46C864h
    L_0045f414:
        push edi
    L_0045f415:
        call esi
    L_0045f417:
        push 46C850h
    L_0045f41c:
        push edi
    L_0045f41d:
        mov dword ptr [data_004776a0],eax
    L_0045f422:
        call esi
    L_0045f424:
        cmp dword ptr [data_00477470],2
    L_0045f42b:
        mov dword ptr [data_004776a4],eax
    L_0045f430:
        jne short L_0045f450
    L_0045f432:
        push 46C834h
    L_0045f437:
        push edi
    L_0045f438:
        call esi
    L_0045f43a:
        test eax,eax
    L_0045f43c:
        mov dword ptr [data_004776ac],eax
    L_0045f441:
        je short L_0045f450
    L_0045f443:
        push 46C81Ch
    L_0045f448:
        push edi
    L_0045f449:
        call esi
    L_0045f44b:
        mov dword ptr [data_004776a8],eax
    L_0045f450:
        mov eax,dword ptr [data_004776a8]
    L_0045f455:
        test eax,eax
    L_0045f457:
        je short L_0045f495
    L_0045f459:
        call eax
    L_0045f45b:
        test eax,eax
    L_0045f45d:
        je short L_0045f47c
    L_0045f45f:
        lea ecx,[ebp-4]
    L_0045f462:
        push ecx
    L_0045f463:
        push 0Ch
    L_0045f465:
        lea ecx,[ebp-10h]
    L_0045f468:
        push ecx
    L_0045f469:
        push 1
    L_0045f46b:
        push eax
    L_0045f46c:
        call dword ptr [data_004776ac]
    L_0045f472:
        test eax,eax
    L_0045f474:
        je short L_0045f47c
    L_0045f476:
        test byte ptr [ebp-8],1
    L_0045f47a:
        jne short L_0045f495
    L_0045f47c:
        cmp dword ptr [data_0047747c],4
    L_0045f483:
        jb short L_0045f48f
    L_0045f485:
        or byte ptr [ebp+12h],20h
    L_0045f489:
        jmp short L_0045f4b4
    L_0045f48b:
        xor eax,eax
    L_0045f48d:
        jmp short L_0045f4c4
    L_0045f48f:
        or byte ptr [ebp+12h],4
    L_0045f493:
        jmp short L_0045f4b4
    L_0045f495:
        mov eax,dword ptr [data_004776a0]
    L_0045f49a:
        test eax,eax
    L_0045f49c:
        je short L_0045f4b4
    L_0045f49e:
        call eax
    L_0045f4a0:
        mov ebx,eax
    L_0045f4a2:
        test ebx,ebx
    L_0045f4a4:
        je short L_0045f4b4
    L_0045f4a6:
        mov eax,dword ptr [data_004776a4]
    L_0045f4ab:
        test eax,eax
    L_0045f4ad:
        je short L_0045f4b4
    L_0045f4af:
        push ebx
    L_0045f4b0:
        call eax
    L_0045f4b2:
        mov ebx,eax
    L_0045f4b4:
        push dword ptr [ebp+10h]
    L_0045f4b7:
        push dword ptr [ebp+0Ch]
    L_0045f4ba:
        push dword ptr [ebp+8]
    L_0045f4bd:
        push ebx
    L_0045f4be:
        call dword ptr [data_0047769c]
    L_0045f4c4:
        pop edi
    L_0045f4c5:
        pop esi
    L_0045f4c6:
        pop ebx
    L_0045f4c7:
        leave
    L_0045f4c8:
        ret
    }
}
