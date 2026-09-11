#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A940..0x0040ABC6: FUN_0040a940
// Naked body preserves the retail register/stack ABI.

// 0x0042C360..0x0042C572: FUN_0042c360
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042c360_0042c360() {
    __asm {
    L_0042c360:
        sub esp,0Ch
    L_0042c363:
        push ebx
    L_0042c364:
        push esi
    L_0042c365:
        mov esi,dword ptr [data_004776e0]
    L_0042c36b:
        push 46E8D4h
    L_0042c370:
        lea ebx,[esp+0Ch]
    L_0042c374:
        mov dword ptr [esp+0Ch],0
    L_0042c37c:
        mov dword ptr [esp+10h],0
    L_0042c384:
        mov dword ptr [esp+14h],0
    L_0042c38c:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c391:
        mov eax,dword ptr [edi+30h]
    L_0042c394:
        add esp,4
    L_0042c397:
        dec eax
    L_0042c398:
        je asm_target_0042c474
    L_0042c39e:
        dec eax
    L_0042c39f:
        je short L_0042c413
    L_0042c3a1:
        dec eax
    L_0042c3a2:
        jne asm_target_0042c568
    L_0042c3a8:
        mov esi,dword ptr [data_004776e0]
    L_0042c3ae:
        mov dword ptr [esi+8974h],0FFA0A0A0h
    L_0042c3b8:
        fld dword ptr [edi+2C8h]
    L_0042c3be:
        mov dword ptr [esp+8],42000000h
    L_0042c3c6:
        mov dword ptr [esp+0Ch],41800000h
    L_0042c3ce:
        mov dword ptr [esp+10h],0
    L_0042c3d6:
        call asm_FUN_00463b2c_00463b2c
    L_0042c3db:
        fld dword ptr [edi+2C4h]
    L_0042c3e1:
        push eax
    L_0042c3e2:
        call asm_FUN_00463b2c_00463b2c
    L_0042c3e7:
        push eax
    L_0042c3e8:
        push 46CDF4h
    L_0042c3ed:
        lea ebx,[esp+14h]
    L_0042c3f1:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c3f6:
        mov eax,dword ptr [data_004776e0]
    L_0042c3fb:
        add esp,0Ch
    L_0042c3fe:
        pop esi
    L_0042c3ff:
        mov dword ptr [eax+8974h],0FFFFFFFFh
    L_0042c409:
        mov eax,1
    L_0042c40e:
        pop ebx
    L_0042c40f:
        add esp,0Ch
    L_0042c412:
        ret
    L_0042c413:
        mov esi,dword ptr [data_004776e0]
    L_0042c419:
        mov dword ptr [esi+8974h],0FFFF4040h
    L_0042c423:
        mov ecx,dword ptr [edi+114h]
    L_0042c429:
        mov edx,dword ptr [edi+34h]
    L_0042c42c:
        mov eax,dword ptr [edx+ecx*4]
    L_0042c42f:
        push eax
    L_0042c430:
        push 46CE44h
    L_0042c435:
        lea ebx,[esp+10h]
    L_0042c439:
        mov dword ptr [esp+10h],42000000h
    L_0042c441:
        mov dword ptr [esp+14h],41800000h
    L_0042c449:
        mov dword ptr [esp+18h],0
    L_0042c451:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c456:
        mov ecx,dword ptr [data_004776e0]
    L_0042c45c:
        add esp,8
    L_0042c45f:
        pop esi
    L_0042c460:
        mov dword ptr [ecx+8974h],0FFFFFFFFh
    L_0042c46a:
        mov eax,1
    L_0042c46f:
        pop ebx
    L_0042c470:
        add esp,0Ch
    L_0042c473:
        ret
    L_0042c474:
        mov eax,dword ptr [edi+38h]
    L_0042c477:
        test eax,eax
    L_0042c479:
        mov esi,dword ptr [data_004776e0]
    L_0042c47f:
        mov dword ptr [esp+8],42280000h
    L_0042c487:
        mov dword ptr [esp+0Ch],41800000h
    L_0042c48f:
        mov dword ptr [esp+10h],0
    L_0042c497:
        lea ebx,[esp+8]
    L_0042c49b:
        je short L_0042c4b9
    L_0042c49d:
        mov edx,dword ptr [edi+114h]
    L_0042c4a3:
        mov eax,dword ptr [edi+34h]
    L_0042c4a6:
        mov ecx,dword ptr [eax+edx*4]
    L_0042c4a9:
        push ecx
    L_0042c4aa:
        push 46CE3Ch
    L_0042c4af:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c4b4:
        add esp,8
    L_0042c4b7:
        jmp short L_0042c4c6
    L_0042c4b9:
        push 46CE2Ch
    L_0042c4be:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c4c3:
        add esp,4
    L_0042c4c6:
        mov eax,dword ptr [edi+2D8h]
    L_0042c4cc:
        test eax,eax
    L_0042c4ce:
        mov esi,dword ptr [data_004776e0]
    L_0042c4d4:
        mov dword ptr [esp+0Ch],41D00000h
    L_0042c4dc:
        lea ebx,[esp+8]
    L_0042c4e0:
        je short L_0042c501
    L_0042c4e2:
        mov edx,dword ptr [edi+1ECh]
    L_0042c4e8:
        mov eax,dword ptr [eax+8Ch]
    L_0042c4ee:
        mov ecx,dword ptr [eax+edx*8]
    L_0042c4f1:
        push ecx
    L_0042c4f2:
        push 46CE24h
    L_0042c4f7:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c4fc:
        add esp,8
    L_0042c4ff:
        jmp short L_0042c50e
    L_0042c501:
        push 46E8C4h
    L_0042c506:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c50b:
        add esp,4
    L_0042c50e:
        mov esi,dword ptr [data_004776e0]
    L_0042c514:
        push 46CE14h
    L_0042c519:
        lea ebx,[esp+0Ch]
    L_0042c51d:
        mov dword ptr [esp+10h],42100000h
    L_0042c525:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c52a:
        fild dword ptr [edi+3Ch]
    L_0042c52d:
        mov esi,dword ptr [data_004776e0]
    L_0042c533:
        push 46CE10h
    L_0042c538:
        fmul dword ptr [data_00470c1c]
    L_0042c53e:
        mov dword ptr [esp+10h],42000000h
    L_0042c546:
        fadd dword ptr [data_00470b48]
    L_0042c54c:
        fstp dword ptr [esp+14h]
    L_0042c550:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0042c555:
        mov edx,dword ptr [data_004776e0]
    L_0042c55b:
        mov dword ptr [edx+8974h],0FFFFFFFFh
    L_0042c565:
        add esp,8
    L_0042c568:
        pop esi
    L_0042c569:
        mov eax,1
    L_0042c56e:
        pop ebx
    L_0042c56f:
        add esp,0Ch
    L_0042c572:
        ret
    }
}
