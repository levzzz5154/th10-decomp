#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B39A..0x0045B529: ___free_lc_time
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_free_lc_time_0045b39a() {
    __asm {
    L_0045b39a:
        push esi
    L_0045b39b:
        mov esi,dword ptr [esp+8]
    L_0045b39f:
        test esi,esi
    L_0045b3a1:
        je asm_target_0045b528
    L_0045b3a7:
        push dword ptr [esi+4]
    L_0045b3aa:
        call asm_free_00452422
    L_0045b3af:
        push dword ptr [esi+8]
    L_0045b3b2:
        call asm_free_00452422
    L_0045b3b7:
        push dword ptr [esi+0Ch]
    L_0045b3ba:
        call asm_free_00452422
    L_0045b3bf:
        push dword ptr [esi+10h]
    L_0045b3c2:
        call asm_free_00452422
    L_0045b3c7:
        push dword ptr [esi+14h]
    L_0045b3ca:
        call asm_free_00452422
    L_0045b3cf:
        push dword ptr [esi+18h]
    L_0045b3d2:
        call asm_free_00452422
    L_0045b3d7:
        push dword ptr [esi]
    L_0045b3d9:
        call asm_free_00452422
    L_0045b3de:
        push dword ptr [esi+20h]
    L_0045b3e1:
        call asm_free_00452422
    L_0045b3e6:
        push dword ptr [esi+24h]
    L_0045b3e9:
        call asm_free_00452422
    L_0045b3ee:
        push dword ptr [esi+28h]
    L_0045b3f1:
        call asm_free_00452422
    L_0045b3f6:
        push dword ptr [esi+2Ch]
    L_0045b3f9:
        call asm_free_00452422
    L_0045b3fe:
        push dword ptr [esi+30h]
    L_0045b401:
        call asm_free_00452422
    L_0045b406:
        push dword ptr [esi+34h]
    L_0045b409:
        call asm_free_00452422
    L_0045b40e:
        push dword ptr [esi+1Ch]
    L_0045b411:
        call asm_free_00452422
    L_0045b416:
        push dword ptr [esi+38h]
    L_0045b419:
        call asm_free_00452422
    L_0045b41e:
        push dword ptr [esi+3Ch]
    L_0045b421:
        call asm_free_00452422
    L_0045b426:
        add esp,40h
    L_0045b429:
        push dword ptr [esi+40h]
    L_0045b42c:
        call asm_free_00452422
    L_0045b431:
        push dword ptr [esi+44h]
    L_0045b434:
        call asm_free_00452422
    L_0045b439:
        push dword ptr [esi+48h]
    L_0045b43c:
        call asm_free_00452422
    L_0045b441:
        push dword ptr [esi+4Ch]
    L_0045b444:
        call asm_free_00452422
    L_0045b449:
        push dword ptr [esi+50h]
    L_0045b44c:
        call asm_free_00452422
    L_0045b451:
        push dword ptr [esi+54h]
    L_0045b454:
        call asm_free_00452422
    L_0045b459:
        push dword ptr [esi+58h]
    L_0045b45c:
        call asm_free_00452422
    L_0045b461:
        push dword ptr [esi+5Ch]
    L_0045b464:
        call asm_free_00452422
    L_0045b469:
        push dword ptr [esi+60h]
    L_0045b46c:
        call asm_free_00452422
    L_0045b471:
        push dword ptr [esi+64h]
    L_0045b474:
        call asm_free_00452422
    L_0045b479:
        push dword ptr [esi+68h]
    L_0045b47c:
        call asm_free_00452422
    L_0045b481:
        push dword ptr [esi+6Ch]
    L_0045b484:
        call asm_free_00452422
    L_0045b489:
        push dword ptr [esi+70h]
    L_0045b48c:
        call asm_free_00452422
    L_0045b491:
        push dword ptr [esi+74h]
    L_0045b494:
        call asm_free_00452422
    L_0045b499:
        push dword ptr [esi+78h]
    L_0045b49c:
        call asm_free_00452422
    L_0045b4a1:
        push dword ptr [esi+7Ch]
    L_0045b4a4:
        call asm_free_00452422
    L_0045b4a9:
        add esp,40h
    L_0045b4ac:
        push dword ptr [esi+80h]
    L_0045b4b2:
        call asm_free_00452422
    L_0045b4b7:
        push dword ptr [esi+84h]
    L_0045b4bd:
        call asm_free_00452422
    L_0045b4c2:
        push dword ptr [esi+88h]
    L_0045b4c8:
        call asm_free_00452422
    L_0045b4cd:
        push dword ptr [esi+8Ch]
    L_0045b4d3:
        call asm_free_00452422
    L_0045b4d8:
        push dword ptr [esi+90h]
    L_0045b4de:
        call asm_free_00452422
    L_0045b4e3:
        push dword ptr [esi+94h]
    L_0045b4e9:
        call asm_free_00452422
    L_0045b4ee:
        push dword ptr [esi+98h]
    L_0045b4f4:
        call asm_free_00452422
    L_0045b4f9:
        push dword ptr [esi+9Ch]
    L_0045b4ff:
        call asm_free_00452422
    L_0045b504:
        push dword ptr [esi+0A0h]
    L_0045b50a:
        call asm_free_00452422
    L_0045b50f:
        push dword ptr [esi+0A4h]
    L_0045b515:
        call asm_free_00452422
    L_0045b51a:
        push dword ptr [esi+0A8h]
    L_0045b520:
        call asm_free_00452422
    L_0045b525:
        add esp,2Ch
    L_0045b528:
        pop esi
    L_0045b529:
        ret
    }
}
