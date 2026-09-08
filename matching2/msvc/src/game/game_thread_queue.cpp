#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401530..0x004015B3: ?GameThread_AppendRecord@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_AppendRecord_00401530() {
    __asm {
    L_00401530:
        mov edx,dword ptr [ecx+896Ch]
    L_00401536:
        cmp edx,100h
    L_0040153c:
        push esi
    L_0040153d:
        mov esi,eax
    L_0040153f:
        jge short L_004015b2
    L_00401541:
        mov eax,edx
    L_00401543:
        imul eax,68h
    L_00401546:
        push edi
    L_00401547:
        lea eax,[eax+ecx+76Ch]
    L_0040154e:
        inc edx
    L_0040154f:
        mov edi,eax
    L_00401551:
        mov dword ptr [ecx+896Ch],edx
    L_00401557:
        sub edi,esi
    L_00401559:
        lea esp,[esp+force_disp32_zero]
    L_00401560:
        mov dl,byte ptr [esi]
    L_00401562:
        mov byte ptr [edi+esi],dl
    L_00401565:
        inc esi
    L_00401566:
        test dl,dl
    L_00401568:
        jne short L_00401560
    L_0040156a:
        mov esi,dword ptr [ebx]
    L_0040156c:
        lea edx,[eax+40h]
    L_0040156f:
        mov dword ptr [edx],esi
    L_00401571:
        mov esi,dword ptr [ebx+4]
    L_00401574:
        mov dword ptr [edx+4],esi
    L_00401577:
        mov esi,dword ptr [ebx+8]
    L_0040157a:
        mov dword ptr [edx+8],esi
    L_0040157d:
        mov edx,dword ptr [ecx+8974h]
    L_00401583:
        mov dword ptr [eax+4Ch],edx
    L_00401586:
        mov edx,dword ptr [ecx+8978h]
    L_0040158c:
        mov dword ptr [eax+50h],edx
    L_0040158f:
        mov edx,dword ptr [ecx+897Ch]
    L_00401595:
        mov dword ptr [eax+54h],edx
    L_00401598:
        mov edx,dword ptr [ecx+8980h]
    L_0040159e:
        mov dword ptr [eax+5Ch],edx
    L_004015a1:
        mov dword ptr [eax+60h],0
    L_004015a8:
        mov ecx,dword ptr [ecx+8988h]
    L_004015ae:
        mov dword ptr [eax+64h],ecx
    L_004015b1:
        pop edi
    L_004015b2:
        pop esi
    L_004015b3:
        ret
    }
}

// 0x00401630..0x00401684: ?GameThread_AppendFormatted@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_AppendFormatted_00401630() {
    __asm {
    L_00401630:
        sub esp,204h
    L_00401636:
        mov eax,dword ptr [data_00473660]
    L_0040163b:
        mov ecx,dword ptr [esp+20Ch]
    L_00401642:
        xor eax,esp
    L_00401644:
        mov dword ptr [esp+200h],eax
    L_0040164b:
        lea eax,[esp+210h]
    L_00401652:
        push eax
    L_00401653:
        push ecx
    L_00401654:
        lea edx,[esp+8]
    L_00401658:
        push edx
    L_00401659:
        call asm_vsprintf_004524a6
    L_0040165e:
        mov ecx,dword ptr [esp+214h]
    L_00401665:
        add esp,0Ch
    L_00401668:
        lea eax,[esp]
    L_0040166b:
        call asm_GameThread_AppendRecord_00401530
    L_00401670:
        mov ecx,dword ptr [esp+200h]
    L_00401677:
        xor ecx,esp
    L_00401679:
        call asm_security_check_cookie_00458ea5
    L_0040167e:
        add esp,204h
    L_00401684:
        ret
    }
}

// 0x00401690..0x004016F3: GameThread_AppendFormattedMarkedRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_AppendFormattedMarkedRetail_00401690() {
    __asm {
    L_00401690:
        sub esp,204h
    L_00401696:
        mov eax,dword ptr [data_00473660]
    L_0040169b:
        mov ecx,dword ptr [esp+208h]
    L_004016a2:
        xor eax,esp
    L_004016a4:
        mov dword ptr [esp+200h],eax
    L_004016ab:
        lea eax,[esp+20Ch]
    L_004016b2:
        push eax
    L_004016b3:
        push ecx
    L_004016b4:
        lea edx,[esp+8]
    L_004016b8:
        push edx
    L_004016b9:
        call asm_vsprintf_004524a6
    L_004016be:
        add esp,0Ch
    L_004016c1:
        lea eax,[esp]
    L_004016c4:
        mov ecx,esi
    L_004016c6:
        call asm_GameThread_AppendRecord_00401530
    L_004016cb:
        mov eax,dword ptr [esi+896Ch]
    L_004016d1:
        mov ecx,dword ptr [esp+200h]
    L_004016d8:
        imul eax,68h
    L_004016db:
        xor ecx,esp
    L_004016dd:
        mov dword ptr [eax+esi+764h],1
    L_004016e8:
        call asm_security_check_cookie_00458ea5
    L_004016ed:
        add esp,204h
    L_004016f3:
        ret
    }
}
