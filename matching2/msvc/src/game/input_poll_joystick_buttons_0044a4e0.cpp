#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

// 0x0044A4E0..0x0044A5E7: Input_PollJoystickButtons
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Input_PollJoystickButtons_0044a4e0() {
    __asm {
    L_0044a4e0:
        sub esp,148h
    L_0044a4e6:
        mov eax,dword ptr [data_00473660]
    L_0044a4eb:
        xor eax,esp
    L_0044a4ed:
        push ebx
    L_0044a4ee:
        mov dword ptr [esp+148h],eax
    L_0044a4f5:
        push edi
    L_0044a4f6:
        mov ebx,ecx
    L_0044a4f8:
        xor eax,eax
    L_0044a4fa:
        mov ecx,20h
    L_0044a4ff:
        mov edi,497BB0h
    L_0044a504:
        rep stosd
    L_0044a506:
        mov eax,dword ptr [data_00491ff4]
    L_0044a50b:
        test ah,4
    L_0044a50e:
        jne short L_0044a55d
    L_0044a510:
        xor eax,eax
    L_0044a512:
        mov ecx,0Dh
    L_0044a517:
        lea edi,[esp+8]
    L_0044a51b:
        rep stosd
    L_0044a51d:
        lea eax,[esp+8]
    L_0044a521:
        push eax
    L_0044a522:
        push 0
    L_0044a524:
        mov dword ptr [esp+10h],34h
    L_0044a52c:
        mov dword ptr [esp+14h],0FFh
    L_0044a534:
        call dword ptr [data_00466280]
    L_0044a53a:
        test eax,eax
    L_0044a53c:
        jne asm_target_0044a5cc
    L_0044a542:
        mov ecx,dword ptr [esp+28h]
    L_0044a546:
        mov dl,80h
    L_0044a548:
        test cl,1
    L_0044a54b:
        je short L_0044a553
    L_0044a54d:
        mov byte ptr [eax+497BB0h],dl
    L_0044a553:
        inc eax
    L_0044a554:
        shr ecx,1
    L_0044a556:
        cmp eax,20h
    L_0044a559:
        jb short L_0044a548
    L_0044a55b:
        jmp short L_0044a5cc
    L_0044a55d:
        mov eax,dword ptr [ebx*4+491C3Ch]
    L_0044a564:
        mov ecx,dword ptr [eax]
    L_0044a566:
        push esi
    L_0044a567:
        push eax
    L_0044a568:
        call dword ptr [ecx+64h]
    L_0044a56b:
        test eax,eax
    L_0044a56d:
        jge short L_0044a5a4
    L_0044a56f:
        mov eax,dword ptr [ebx*4+491C3Ch]
    L_0044a576:
        mov edx,dword ptr [eax]
    L_0044a578:
        push eax
    L_0044a579:
        xor esi,esi
    L_0044a57b:
        call dword ptr [edx+1Ch]
    L_0044a57e:
        cmp eax,8007001Eh
    L_0044a583:
        jne short L_0044a5cb
    L_0044a585:
        mov eax,dword ptr [ebx*4+491C3Ch]
    L_0044a58c:
        mov ecx,dword ptr [eax]
    L_0044a58e:
        push eax
    L_0044a58f:
        call dword ptr [ecx+1Ch]
    L_0044a592:
        inc esi
    L_0044a593:
        cmp esi,190h
    L_0044a599:
        jge short L_0044a5cb
    L_0044a59b:
        cmp eax,8007001Eh
    L_0044a5a0:
        je short L_0044a585
    L_0044a5a2:
        jmp short L_0044a5cb
    L_0044a5a4:
        mov ebx,dword ptr [ebx*4+491C3Ch]
    L_0044a5ab:
        mov edx,dword ptr [ebx]
    L_0044a5ad:
        lea eax,[esp+40h]
    L_0044a5b1:
        push eax
    L_0044a5b2:
        push 110h
    L_0044a5b7:
        push ebx
    L_0044a5b8:
        call dword ptr [edx+24h]
    L_0044a5bb:
        mov ecx,20h
    L_0044a5c0:
        lea esi,[esp+70h]
    L_0044a5c4:
        mov edi,497BB0h
    L_0044a5c9:
        rep movsd
    L_0044a5cb:
        pop esi
    L_0044a5cc:
        mov ecx,dword ptr [esp+14Ch]
    L_0044a5d3:
        pop edi
    L_0044a5d4:
        pop ebx
    L_0044a5d5:
        xor ecx,esp
    L_0044a5d7:
        mov eax,497BB0h
    L_0044a5dc:
        call asm_security_check_cookie_00458ea5
    L_0044a5e1:
        add esp,148h
    L_0044a5e7:
        ret
    }
}
