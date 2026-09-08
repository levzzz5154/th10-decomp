#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"

// 0x00436570..0x00436638: ?Platform_LaunchProcess@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_LaunchProcess_00436570() {
    __asm {
    L_00436570:
        sub esp,54h
    L_00436573:
        push esi
    L_00436574:
        xor esi,esi
    L_00436576:
        mov eax,80000000h
    L_0043657b:
        mov dword ptr [esp+24h],eax
    L_0043657f:
        mov dword ptr [esp+28h],eax
    L_00436583:
        mov dword ptr [esp+2Ch],eax
    L_00436587:
        mov dword ptr [esp+30h],eax
    L_0043658b:
        lea eax,[esp+4]
    L_0043658f:
        push eax
    L_00436590:
        mov eax,dword ptr [esp+60h]
    L_00436594:
        lea ecx,[esp+18h]
    L_00436598:
        push ecx
    L_00436599:
        push esi
    L_0043659a:
        push esi
    L_0043659b:
        push 20h
    L_0043659d:
        push esi
    L_0043659e:
        push esi
    L_0043659f:
        push esi
    L_004365a0:
        push edx
    L_004365a1:
        push eax
    L_004365a2:
        mov dword ptr [esp+3Ch],44h
    L_004365aa:
        mov dword ptr [esp+40h],esi
    L_004365ae:
        mov dword ptr [esp+44h],esi
    L_004365b2:
        mov dword ptr [esp+48h],esi
    L_004365b6:
        mov dword ptr [esp+5Ch],50h
    L_004365be:
        mov dword ptr [esp+60h],19h
    L_004365c6:
        mov dword ptr [esp+64h],esi
    L_004365ca:
        mov dword ptr [esp+68h],esi
    L_004365ce:
        mov word ptr [esp+6Ch],0Ah
    L_004365d5:
        mov word ptr [esp+6Eh],si
    L_004365da:
        mov dword ptr [esp+70h],esi
    L_004365de:
        mov dword ptr [esp+74h],esi
    L_004365e2:
        mov dword ptr [esp+78h],esi
    L_004365e6:
        mov dword ptr [esp+7Ch],esi
    L_004365ea:
        call dword ptr [data_004660e0]
    L_004365f0:
        test eax,eax
    L_004365f2:
        jne short L_004365fe
    L_004365f4:
        or eax,0FFFFFFFFh
    L_004365f7:
        pop esi
    L_004365f8:
        add esp,54h
    L_004365fb:
        ret 8
    L_004365fe:
        cmp dword ptr [esp+60h],esi
    L_00436602:
        je short L_00436630
    L_00436604:
        mov esi,dword ptr [data_004660e4]
    L_0043660a:
        mov dword ptr [esp+5Ch],103h
    L_00436612:
        mov edx,dword ptr [esp+4]
    L_00436616:
        lea ecx,[esp+5Ch]
    L_0043661a:
        push ecx
    L_0043661b:
        push edx
    L_0043661c:
        call esi
    L_0043661e:
        mov eax,dword ptr [esp+5Ch]
    L_00436622:
        cmp eax,103h
    L_00436627:
        je short L_00436612
    L_00436629:
        pop esi
    L_0043662a:
        add esp,54h
    L_0043662d:
        ret 8
    L_00436630:
        xor eax,eax
    L_00436632:
        pop esi
    L_00436633:
        add esp,54h
    L_00436636:
        ret 8
    }
}

// 0x0044BD10..0x0044BE13: ?Platform_GetOsVersionCode@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_GetOsVersionCode_0044bd10() {
    __asm {
    L_0044bd10:
        push ebp
    L_0044bd11:
        mov ebp,esp
    L_0044bd13:
        and esp,0FFFFFFF8h
    L_0044bd16:
        sub esp,0A4h
    L_0044bd1c:
        mov eax,dword ptr [data_00473660]
    L_0044bd21:
        xor eax,ebp
    L_0044bd23:
        push edi
    L_0044bd24:
        mov dword ptr [esp+0A4h],eax
    L_0044bd2b:
        xor eax,eax
    L_0044bd2d:
        mov ecx,25h
    L_0044bd32:
        lea edi,[esp+8]
    L_0044bd36:
        rep stosd
    L_0044bd38:
        lea eax,[esp+8]
    L_0044bd3c:
        push eax
    L_0044bd3d:
        mov dword ptr [esp+0Ch],94h
    L_0044bd45:
        call dword ptr [data_0046612c]
    L_0044bd4b:
        mov eax,dword ptr [esp+18h]
    L_0044bd4f:
        sub eax,0
    L_0044bd52:
        je asm_target_0044bdfc
    L_0044bd58:
        dec eax
    L_0044bd59:
        je short L_0044bdb6
    L_0044bd5b:
        dec eax
    L_0044bd5c:
        je short L_0044bd74
    L_0044bd5e:
        or eax,0FFFFFFFFh
    L_0044bd61:
        pop edi
    L_0044bd62:
        mov ecx,dword ptr [esp+0A0h]
    L_0044bd69:
        xor ecx,ebp
    L_0044bd6b:
        call asm_security_check_cookie_00458ea5
    L_0044bd70:
        mov esp,ebp
    L_0044bd72:
        pop ebp
    L_0044bd73:
        ret
    L_0044bd74:
        mov eax,dword ptr [esp+0Ch]
    L_0044bd78:
        cmp eax,5
    L_0044bd7b:
        jne short L_0044bd95
    L_0044bd7d:
        mov eax,7D0h
    L_0044bd82:
        pop edi
    L_0044bd83:
        mov ecx,dword ptr [esp+0A0h]
    L_0044bd8a:
        xor ecx,ebp
    L_0044bd8c:
        call asm_security_check_cookie_00458ea5
    L_0044bd91:
        mov esp,ebp
    L_0044bd93:
        pop ebp
    L_0044bd94:
        ret
    L_0044bd95:
        mov edx,dword ptr [esp+10h]
    L_0044bd99:
        imul eax,64h
    L_0044bd9c:
        add eax,edx
    L_0044bd9e:
        lea eax,[eax+eax*4]
    L_0044bda1:
        shl eax,1
    L_0044bda3:
        pop edi
    L_0044bda4:
        mov ecx,dword ptr [esp+0A0h]
    L_0044bdab:
        xor ecx,ebp
    L_0044bdad:
        call asm_security_check_cookie_00458ea5
    L_0044bdb2:
        mov esp,ebp
    L_0044bdb4:
        pop ebp
    L_0044bdb5:
        ret
    L_0044bdb6:
        mov eax,dword ptr [esp+0Ch]
    L_0044bdba:
        cmp eax,4
    L_0044bdbd:
        jne short L_0044bde0
    L_0044bdbf:
        mov eax,dword ptr [esp+10h]
    L_0044bdc3:
        neg eax
    L_0044bdc5:
        sbb eax,eax
    L_0044bdc7:
        and eax,3
    L_0044bdca:
        add eax,5Fh
    L_0044bdcd:
        pop edi
    L_0044bdce:
        mov ecx,dword ptr [esp+0A0h]
    L_0044bdd5:
        xor ecx,ebp
    L_0044bdd7:
        call asm_security_check_cookie_00458ea5
    L_0044bddc:
        mov esp,ebp
    L_0044bdde:
        pop ebp
    L_0044bddf:
        ret
    L_0044bde0:
        mov ecx,dword ptr [esp+10h]
    L_0044bde4:
        imul eax,64h
    L_0044bde7:
        add eax,ecx
    L_0044bde9:
        pop edi
    L_0044bdea:
        mov ecx,dword ptr [esp+0A0h]
    L_0044bdf1:
        xor ecx,ebp
    L_0044bdf3:
        call asm_security_check_cookie_00458ea5
    L_0044bdf8:
        mov esp,ebp
    L_0044bdfa:
        pop ebp
    L_0044bdfb:
        ret
    L_0044bdfc:
        mov ecx,dword ptr [esp+0A4h]
    L_0044be03:
        xor ecx,ebp
    L_0044be05:
        mov eax,1Fh
    L_0044be0a:
        pop edi
    L_0044be0b:
        call asm_security_check_cookie_00458ea5
    L_0044be10:
        mov esp,ebp
    L_0044be12:
        pop ebp
    L_0044be13:
        ret
    }
}

// 0x0044C100..0x0044C123: ?Platform_DestroyWorker@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_DestroyWorker_0044c100() {
    __asm {
    L_0044c100:
        push esi
    L_0044c101:
        mov esi,ecx
    L_0044c103:
        mov dword ptr [esi],4703E4h
    L_0044c109:
        call asm_Platform_StopWorker_0044c150
    L_0044c10e:
        test byte ptr [esp+8],1
    L_0044c113:
        je short L_0044c11e
    L_0044c115:
        push esi
    L_0044c116:
        call asm_free_004524a1
    L_0044c11b:
        add esp,4
    L_0044c11e:
        mov eax,esi
    L_0044c120:
        pop esi
    L_0044c121:
        ret 4
    }
}

// 0x0044C130..0x0044C13F: ?Platform_StopWorkerNoDelete@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_StopWorkerNoDelete_0044c130() {
    __asm {
    L_0044c130:
        push esi
    L_0044c131:
        mov esi,ecx
    L_0044c133:
        mov dword ptr [ecx],4703E4h
    L_0044c139:
        call asm_Platform_StopWorker_0044c150
    L_0044c13e:
        pop esi
    L_0044c13f:
        ret
    }
}

// 0x0044D5B0..0x0044D5CC: stop the first DirectSound buffer and clear the
// wrapper's playing flag. DirectSound methods use their stdcall COM ABI.
int __fastcall Platform_InvokeInterface(SoundBuffer* sound_buffer) {
    DirectSoundBuffer** const buffers = sound_buffer->buffers;
    if (buffers == 0)
        return (int)0x800401F0u;

    sound_buffer->is_playing = 0;
    DirectSoundBuffer* const buffer = buffers[0];
    return buffer->vtable->stop(buffer);
}
