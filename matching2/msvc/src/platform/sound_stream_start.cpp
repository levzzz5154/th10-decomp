#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044D440..0x0044D4D0: SoundStream_Start
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_SoundStream_Start_0044d440() {
    __asm {
    L_0044d440:
        push ecx
    L_0044d441:
        push ebp
    L_0044d442:
        push edi
    L_0044d443:
        mov edi,eax
    L_0044d445:
        mov eax,dword ptr [edi+4]
    L_0044d448:
        xor ebp,ebp
    L_0044d44a:
        cmp eax,ebp
    L_0044d44c:
        jne short L_0044d459
    L_0044d44e:
        pop edi
    L_0044d44f:
        mov eax,800401F0h
    L_0044d454:
        pop ebp
    L_0044d455:
        pop ecx
    L_0044d456:
        ret 8
    L_0044d459:
        push esi
    L_0044d45a:
        call asm_Platform_FindAvailable_0044d370
    L_0044d45f:
        mov esi,eax
    L_0044d461:
        cmp esi,ebp
    L_0044d463:
        jne short L_0044d471
    L_0044d465:
        pop esi
    L_0044d466:
        pop edi
    L_0044d467:
        mov eax,80004005h
    L_0044d46c:
        pop ebp
    L_0044d46d:
        pop ecx
    L_0044d46e:
        ret 8
    L_0044d471:
        push ebx
    L_0044d472:
        lea ebx,[esp+10h]
    L_0044d476:
        call asm_Platform_RunInterface_0044d300
    L_0044d47b:
        cmp eax,ebp
    L_0044d47d:
        pop ebx
    L_0044d47e:
        jl short L_0044d4ca
    L_0044d480:
        cmp dword ptr [esp+0Ch],ebp
    L_0044d484:
        je short L_0044d498
    L_0044d486:
        push ebp
    L_0044d487:
        push esi
    L_0044d488:
        mov eax,edi
    L_0044d48a:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0044d48f:
        cmp eax,ebp
    L_0044d491:
        jl short L_0044d4ca
    L_0044d493:
        call asm_Platform_QueryInterfaces_0044d600
    L_0044d498:
        push ebp
    L_0044d499:
        mov eax,edi
    L_0044d49b:
        mov dword ptr [edi+1Ch],ebp
    L_0044d49e:
        mov dword ptr [edi+14h],ebp
    L_0044d4a1:
        mov dword ptr [edi+18h],ebp
    L_0044d4a4:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_0044d4a9:
        mov eax,dword ptr [esp+18h]
    L_0044d4ad:
        mov ecx,dword ptr [esp+14h]
    L_0044d4b1:
        push eax
    L_0044d4b2:
        push ecx
    L_0044d4b3:
        push ebp
    L_0044d4b4:
        mov dword ptr [edi+30h],1
    L_0044d4bb:
        mov dword ptr [edi+20h],ecx
    L_0044d4be:
        mov dword ptr [edi+24h],eax
    L_0044d4c1:
        mov dword ptr [edi+2Ch],ebp
    L_0044d4c4:
        mov edx,dword ptr [esi]
    L_0044d4c6:
        push esi
    L_0044d4c7:
        call dword ptr [edx+30h]
    L_0044d4ca:
        pop esi
    L_0044d4cb:
        pop edi
    L_0044d4cc:
        pop ebp
    L_0044d4cd:
        pop ecx
    L_0044d4ce:
        ret 8
    }
}
