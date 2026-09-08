#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043B7A0..0x0043B82B: FUN_0043b7a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043b7a0_0043b7a0() {
    __asm {
    L_0043b7a0:
        mov eax,dword ptr [edi+2D4h]
    L_0043b7a6:
        sub esp,8
    L_0043b7a9:
        test eax,eax
    L_0043b7ab:
        push ebp
    L_0043b7ac:
        mov ebp,dword ptr [esp+10h]
    L_0043b7b0:
        jne short L_0043b825
    L_0043b7b2:
        push ebx
    L_0043b7b3:
        push esi
    L_0043b7b4:
        xor ebx,ebx
    L_0043b7b6:
        lea esi,[edi+169h]
    L_0043b7bc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0043b7c0:
        movzx edx,byte ptr [esi]
    L_0043b7c3:
        mov dword ptr [esp+0Ch],edx
    L_0043b7c7:
        mov al,bl
    L_0043b7c9:
        sub al,50h
    L_0043b7cb:
        fild dword ptr [esp+0Ch]
    L_0043b7cf:
        movzx ecx,al
    L_0043b7d2:
        fmul dword ptr [edi+2C8h]
    L_0043b7d8:
        mov dword ptr [esp+10h],ecx
    L_0043b7dc:
        call asm_FUN_00463b2c_00463b2c
    L_0043b7e1:
        add eax,ebp
    L_0043b7e3:
        jns short L_0043b7e9
    L_0043b7e5:
        xor eax,eax
    L_0043b7e7:
        jmp short L_0043b7f3
    L_0043b7e9:
        cmp eax,7Fh
    L_0043b7ec:
        jle short L_0043b7f3
    L_0043b7ee:
        mov eax,7Fh
    L_0043b7f3:
        mov ecx,dword ptr [edi+13Ch]
    L_0043b7f9:
        test ecx,ecx
    L_0043b7fb:
        je short L_0043b81a
    L_0043b7fd:
        mov dl,byte ptr [esp+10h]
    L_0043b801:
        mov byte ptr [esp+18h],dl
    L_0043b805:
        mov byte ptr [esp+1Ah],al
    L_0043b809:
        mov byte ptr [esp+19h],7
    L_0043b80e:
        mov eax,dword ptr [esp+18h]
    L_0043b812:
        push eax
    L_0043b813:
        push ecx
    L_0043b814:
        call dword ptr [data_00466298]
    L_0043b81a:
        inc ebx
    L_0043b81b:
        add esi,17h
    L_0043b81e:
        cmp ebx,10h
    L_0043b821:
        jl short L_0043b7c0
    L_0043b823:
        pop esi
    L_0043b824:
        pop ebx
    L_0043b825:
        pop ebp
    L_0043b826:
        add esp,8
    L_0043b829:
        ret 4
    }
}

// 0x0043E3A0..0x0043E45C: MidiWorker_MessageLoopRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MidiWorker_MessageLoopRetail_0043e3a0() {
    __asm {
    L_0043e3a0:
        sub esp,20h
    L_0043e3a3:
        push ebx
    L_0043e3a4:
        mov ebx,dword ptr [data_0046623c]
    L_0043e3aa:
        push ebp
    L_0043e3ab:
        mov ebp,dword ptr [data_0046620c]
    L_0043e3b1:
        push esi
    L_0043e3b2:
        mov dword ptr [esp+0Ch],0
    L_0043e3ba:
        mov esi,1
    L_0043e3bf:
        nop
    L_0043e3c0:
        push 0BFh
    L_0043e3c5:
        push 0FFFFFFFFh
    L_0043e3c7:
        push 0
    L_0043e3c9:
        push 49779Ch
    L_0043e3ce:
        push esi
    L_0043e3cf:
        call ebp
    L_0043e3d1:
        mov ecx,dword ptr [data_00497798]
    L_0043e3d7:
        test ecx,ecx
    L_0043e3d9:
        jne short L_0043e3df
    L_0043e3db:
        mov dword ptr [esp+0Ch],esi
    L_0043e3df:
        sub eax,0
    L_0043e3e2:
        je short L_0043e41f
    L_0043e3e4:
        dec eax
    L_0043e3e5:
        jne short L_0043e446
    L_0043e3e7:
        push esi
    L_0043e3e8:
        push 0
    L_0043e3ea:
        push 0
    L_0043e3ec:
        push 0
    L_0043e3ee:
        lea eax,[esp+20h]
    L_0043e3f2:
        push eax
    L_0043e3f3:
        call ebx
    L_0043e3f5:
        test eax,eax
    L_0043e3f7:
        je short L_0043e446
    L_0043e3f9:
        lea esp,[esp+force_disp32_zero]
    L_0043e400:
        cmp dword ptr [esp+14h],12h
    L_0043e405:
        jne short L_0043e40b
    L_0043e407:
        mov dword ptr [esp+0Ch],esi
    L_0043e40b:
        push esi
    L_0043e40c:
        push 0
    L_0043e40e:
        push 0
    L_0043e410:
        push 0
    L_0043e412:
        lea ecx,[esp+20h]
    L_0043e416:
        push ecx
    L_0043e417:
        call ebx
    L_0043e419:
        test eax,eax
    L_0043e41b:
        jne short L_0043e400
    L_0043e41d:
        jmp short L_0043e446
    L_0043e41f:
        test ecx,ecx
    L_0043e421:
        je short L_0043e446
    L_0043e423:
        mov eax,dword ptr [ecx+30h]
    L_0043e426:
        test eax,eax
    L_0043e428:
        je short L_0043e446
    L_0043e42a:
        mov dword ptr [ecx+74h],esi
    L_0043e42d:
        mov edx,dword ptr [data_00497798]
    L_0043e433:
        push esi
    L_0043e434:
        push edx
    L_0043e435:
        call asm_FUN_0044d850_0044d850
    L_0043e43a:
        mov eax,dword ptr [data_00497798]
    L_0043e43f:
        mov dword ptr [eax+74h],0
    L_0043e446:
        mov eax,dword ptr [esp+0Ch]
    L_0043e44a:
        test eax,eax
    L_0043e44c:
        je asm_target_0043e3c0
    L_0043e452:
        pop esi
    L_0043e453:
        pop ebp
    L_0043e454:
        xor eax,eax
    L_0043e456:
        pop ebx
    L_0043e457:
        add esp,20h
    L_0043e45a:
        ret 4
    }
}
