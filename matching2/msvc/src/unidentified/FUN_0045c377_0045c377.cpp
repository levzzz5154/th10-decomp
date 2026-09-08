#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C377..0x0045C3F0: FUN_0045c377
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045c377_0045c377() {
    __asm {
    L_0045c377:
        push ebp
    L_0045c378:
        mov ebp,esp
    L_0045c37a:
        sub esp,0Ch
    L_0045c37d:
        mov eax,dword ptr [data_00473660]
    L_0045c382:
        push esi
    L_0045c383:
        xor eax,ebp
    L_0045c385:
        mov esi,ecx
    L_0045c387:
        test esi,esi
    L_0045c389:
        mov dword ptr [ebp-4],eax
    L_0045c38c:
        je short L_0045c3bf
    L_0045c38e:
        cmp byte ptr [esi],0
    L_0045c391:
        je short L_0045c3bf
    L_0045c393:
        push 46C520h
    L_0045c398:
        push esi
    L_0045c399:
        call asm_strcmp_0045bf30
    L_0045c39e:
        test eax,eax
    L_0045c3a0:
        pop ecx
    L_0045c3a1:
        pop ecx
    L_0045c3a2:
        je short L_0045c3bf
    L_0045c3a4:
        push 46C51Ch
    L_0045c3a9:
        push esi
    L_0045c3aa:
        call asm_strcmp_0045bf30
    L_0045c3af:
        test eax,eax
    L_0045c3b1:
        pop ecx
    L_0045c3b2:
        pop ecx
    L_0045c3b3:
        jne short L_0045c3dd
    L_0045c3b5:
        push 8
    L_0045c3b7:
        lea eax,[ebp-0Ch]
    L_0045c3ba:
        push eax
    L_0045c3bb:
        push 0Bh
    L_0045c3bd:
        jmp short L_0045c3ca
    L_0045c3bf:
        push 8
    L_0045c3c1:
        lea eax,[ebp-0Ch]
    L_0045c3c4:
        push eax
    L_0045c3c5:
        push 1004h
    L_0045c3ca:
        push dword ptr [data_00477630]
    L_0045c3d0:
        call dword ptr [data_00477648]
    L_0045c3d6:
        test eax,eax
    L_0045c3d8:
        je short L_0045c3e4
    L_0045c3da:
        lea esi,[ebp-0Ch]
    L_0045c3dd:
        push esi
    L_0045c3de:
        call asm_atol_004527ee
    L_0045c3e3:
        pop ecx
    L_0045c3e4:
        mov ecx,dword ptr [ebp-4]
    L_0045c3e7:
        xor ecx,ebp
    L_0045c3e9:
        pop esi
    L_0045c3ea:
        call asm_security_check_cookie_00458ea5
    L_0045c3ef:
        leave
    L_0045c3f0:
        ret
    }
}
