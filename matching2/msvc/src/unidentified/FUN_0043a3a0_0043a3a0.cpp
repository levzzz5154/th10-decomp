#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A3A0..0x0043A488: FUN_0043a3a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a3a0_0043a3a0() {
    __asm {
    L_0043a3a0:
        mov eax,dword ptr [esp+8]
    L_0043a3a4:
        sub eax,110h
    L_0043a3a9:
        je asm_target_0043a464
    L_0043a3af:
        dec eax
    L_0043a3b0:
        push esi
    L_0043a3b1:
        jne asm_target_0043a45e
    L_0043a3b7:
        movzx eax,word ptr [esp+10h]
    L_0043a3bc:
        sub eax,0C9h
    L_0043a3c1:
        je short L_0043a418
    L_0043a3c3:
        sub eax,2
    L_0043a3c6:
        jne asm_target_0043a45e
    L_0043a3cc:
        mov esi,dword ptr [esp+8]
    L_0043a3d0:
        push 0CAh
    L_0043a3d5:
        push esi
    L_0043a3d6:
        call dword ptr [data_00466250]
    L_0043a3dc:
        cmp eax,1
    L_0043a3df:
        mov eax,dword ptr [data_00491d78]
    L_0043a3e4:
        jne short L_0043a3ff
    L_0043a3e6:
        push 7
    L_0043a3e8:
        or eax,100h
    L_0043a3ed:
        push esi
    L_0043a3ee:
        mov dword ptr [data_00491d78],eax
    L_0043a3f3:
        call dword ptr [data_00466244]
    L_0043a3f9:
        xor eax,eax
    L_0043a3fb:
        pop esi
    L_0043a3fc:
        ret 10h
    L_0043a3ff:
        push 7
    L_0043a401:
        and eax,0FFFFFEFFh
    L_0043a406:
        push esi
    L_0043a407:
        mov dword ptr [data_00491d78],eax
    L_0043a40c:
        call dword ptr [data_00466244]
    L_0043a412:
        xor eax,eax
    L_0043a414:
        pop esi
    L_0043a415:
        ret 10h
    L_0043a418:
        mov esi,dword ptr [esp+8]
    L_0043a41c:
        push 0CAh
    L_0043a421:
        push esi
    L_0043a422:
        call dword ptr [data_00466250]
    L_0043a428:
        cmp eax,1
    L_0043a42b:
        mov eax,dword ptr [data_00491d78]
    L_0043a430:
        jne short L_0043a44b
    L_0043a432:
        push 6
    L_0043a434:
        or eax,100h
    L_0043a439:
        push esi
    L_0043a43a:
        mov dword ptr [data_00491d78],eax
    L_0043a43f:
        call dword ptr [data_00466244]
    L_0043a445:
        xor eax,eax
    L_0043a447:
        pop esi
    L_0043a448:
        ret 10h
    L_0043a44b:
        push 6
    L_0043a44d:
        and eax,0FFFFFEFFh
    L_0043a452:
        push esi
    L_0043a453:
        mov dword ptr [data_00491d78],eax
    L_0043a458:
        call dword ptr [data_00466244]
    L_0043a45e:
        xor eax,eax
    L_0043a460:
        pop esi
    L_0043a461:
        ret 10h
    L_0043a464:
        mov eax,dword ptr [esp+4]
    L_0043a468:
        push 0
    L_0043a46a:
        push 1
    L_0043a46c:
        push 0F1h
    L_0043a471:
        push 0CAh
    L_0043a476:
        push eax
    L_0043a477:
        call dword ptr [data_00466240]
    L_0043a47d:
        push eax
    L_0043a47e:
        call dword ptr [data_00466228]
    L_0043a484:
        xor eax,eax
    L_0043a486:
        ret 10h
    }
}
