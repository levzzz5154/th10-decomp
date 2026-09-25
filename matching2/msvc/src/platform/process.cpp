#include <string.h>
#include "asm_encoding.hpp"
#include "th10/platform/windows_types.hpp"
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

extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(OSVERSIONINFOA*);

int Platform_GetOsVersionCode() {
    OSVERSIONINFOA version_info;
    memset(&version_info, 0, sizeof(version_info));
    version_info.dwOSVersionInfoSize = sizeof(version_info);
    GetVersionExA(&version_info);

    switch (version_info.dwPlatformId) {
    case 0:
        return 31;
    case 1:
        if (version_info.dwMajorVersion == 4)
            return version_info.dwMinorVersion != 0 ? 98 : 95;
        return version_info.dwMajorVersion * 100 + version_info.dwMinorVersion;
    case 2:
        if (version_info.dwMajorVersion == 5)
            return 2000;
        return (version_info.dwMajorVersion * 100 + version_info.dwMinorVersion) * 10;
    default:
        return -1;
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
