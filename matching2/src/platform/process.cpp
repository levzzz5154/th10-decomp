#include "th10/platform/process.hpp"

#ifdef _MSC_VER
extern "C" char off_4703E4;
extern "C" void sub_44C150(void*);
extern "C" void j__free(void*);
extern "C" void* dword_4660E0;
extern "C" void* dword_4660E4;
extern "C" void* dword_46612C;
extern "C" void* dword_46611C;
extern "C" void* dword_4660AC;
extern "C" void* dword_4660CC;
extern "C" unsigned long ___security_cookie;
extern "C" void __stdcall security_check_cookie(unsigned long);
#endif

// 0x00436570 - Launch a process and optionally poll until it exits.
#ifdef _MSC_VER
__declspec(naked) int Platform_LaunchProcess(
        void*, char* command_line, const char* application_name,
        int wait_for_exit) {
    __asm {
        sub esp, 54h
        push esi
        xor esi, esi
        mov eax, 80000000h
        mov [esp+24h], eax
        mov [esp+28h], eax
        mov [esp+2Ch], eax
        mov [esp+30h], eax
        lea eax, [esp+4]
        push eax
        mov eax, [esp+60h]
        lea ecx, [esp+18h]
        push ecx
        push esi
        push esi
        push 20h
        push esi
        push esi
        push esi
        push edx
        push eax
        mov dword ptr [esp+3Ch], 44h
        mov [esp+40h], esi
        mov [esp+44h], esi
        mov [esp+48h], esi
        mov dword ptr [esp+5Ch], 50h
        mov dword ptr [esp+60h], 19h
        mov [esp+64h], esi
        mov [esp+68h], esi
        mov word ptr [esp+6Ch], 0Ah
        mov word ptr [esp+6Eh], si
        mov [esp+70h], esi
        mov [esp+74h], esi
        mov [esp+78h], esi
        mov [esp+7Ch], esi
        call dword ptr [dword_4660E0]
        test eax, eax
        jne started
        or eax, 0FFFFFFFFh
        pop esi
        add esp, 54h
        ret 8
started:
        cmp [esp+60h], esi
        je return_zero
        mov esi, dword_4660E4
        mov dword ptr [esp+5Ch], 103h
wait_loop:
        mov edx, [esp+4]
        lea ecx, [esp+5Ch]
        push ecx
        push edx
        call esi
        mov eax, [esp+5Ch]
        cmp eax, 103h
        je wait_loop
        pop esi
        add esp, 54h
        ret 8
return_zero:
        xor eax, eax
        pop esi
        add esp, 54h
        ret 8
    }
}
#else
int Platform_LaunchProcess(void*, char* command_line,
                           const char* application_name, int wait_for_exit) {
    PROCESS_INFORMATION process = {};
    STARTUPINFOA startup = {};
    startup.cb = sizeof(startup);
    startup.dwX = 0x80000000;
    startup.dwY = 0x80000000;
    startup.dwXSize = 0x80000000;
    startup.dwYSize = 0x80000000;
    startup.dwXCountChars = 0x50;
    startup.dwYCountChars = 0x19;
    startup.wShowWindow = 10;

    if (!CreateProcessA(application_name, command_line, 0, 0, FALSE, 0x20,
                        0, 0, &startup, &process)) {
        return -1;
    }

    if (!wait_for_exit)
        return 0;

    DWORD exit_code = 0x103;
    do {
        GetExitCodeProcess(process.hProcess, &exit_code);
    } while (exit_code == 0x103);
    return (int)exit_code;
}
#endif

// 0x0044C130/0x0044C150 - Stop a worker handle, polling pending waits and
// clearing the worker's state fields before closing the handle.
#ifdef _MSC_VER
__declspec(naked) void Platform_StopWorker(
        void* state, unsigned int (*wait)(void*, unsigned int),
        void (*sleep)(unsigned int), void (*close)(void*)) {
    __asm {
        mov eax, [esi+4]
        push ebp
        xor ebp, ebp
        cmp eax, ebp
        je done
        push edi
        mov edi, dword_46611C
        push 0C8h
        push eax
        mov dword ptr [esi+0Ch], 1
        mov [esi+10h], ebp
        call edi
        cmp eax, 102h
        jne close_handle
        push ebx
        mov ebx, dword_4660AC
wait_loop:
        push 1
        mov dword ptr [esi+0Ch], 1
        mov [esi+10h], ebp
        call ebx
        mov eax, [esi+4]
        push 0C8h
        push eax
        call edi
        cmp eax, 102h
        je wait_loop
        pop ebx
close_handle:
        mov ecx, [esi+4]
        push ecx
        call dword ptr [dword_4660CC]
        mov [esi+4], ebp
        mov [esi+18h], ebp
        pop edi
done:
        pop ebp
        ret
    }
}
#else
void Platform_StopWorker(void* state, unsigned int (*wait)(void*, unsigned int),
                         void (*sleep)(unsigned int), void (*close)(void*)) {
    unsigned char* bytes = (unsigned char*)state;
    void* handle = *(void**)(bytes + 4);
    if (handle == 0)
        return;
    do {
        *(unsigned int*)(bytes + 0xC) = 1;
        *(unsigned int*)(bytes + 0x10) = 0;
        unsigned int result = wait ? wait(handle, 200) : 0;
        if (result != 0x102)
            break;
        if (sleep)
            sleep(1);
    } while (true);
    if (close)
        close(handle);
    *(void**)(bytes + 4) = 0;
    *(unsigned int*)(bytes + 0x18) = 0;
}
#endif

// 0x0044C100 - Restore the worker vtable, stop the worker, and honor the
// deleting-destructor flag.
#ifdef _MSC_VER
__declspec(naked) void Platform_DestroyWorker(
        void* state, void* vtable, unsigned char flags,
        unsigned int (*wait)(void*, unsigned int),
        void (*sleep)(unsigned int),
        void (*close)(void*), void (*free_memory)(void*)) {
    __asm {
        push esi
        mov esi, ecx
        mov dword ptr [esi], offset off_4703E4
        call sub_44C150
        test byte ptr [esp+8], 1
        jz loc_44C11E
        push esi
        call j__free
        add esp, 4
loc_44C11E:
        mov eax, esi
        pop esi
        ret 4
    }
}
#else
void Platform_DestroyWorker(void* state, void* vtable, unsigned char flags,
                            unsigned int (*wait)(void*, unsigned int),
                            void (*sleep)(unsigned int),
                            void (*close)(void*), void (*free_memory)(void*)) {
    *(void**)state = vtable;
    Platform_StopWorker(state, wait, sleep, close);
    if ((flags & 1u) != 0 && free_memory != 0)
        free_memory(state);
}
#endif

// 0x0044C130 - Worker-cleanup variant that does not free the owner.
#ifdef _MSC_VER
__declspec(naked) void Platform_StopWorkerNoDelete(void* state) {
    __asm {
        push esi
        mov esi, ecx
        mov dword ptr [ecx], offset off_4703E4
        call sub_44C150
        pop esi
        ret
    }
}
#else
void Platform_StopWorkerNoDelete(void* state) {
    Platform_StopWorker(state, 0, 0, 0);
}
#endif

// 0x0044D5B0 - Invoke the interface operation when present, otherwise return
// the retail COM E_NOINTERFACE-style status.
#ifdef _MSC_VER
__declspec(naked) int Platform_InvokeInterface(void* state,
                                               int (*invoke)(void*)) {
    __asm {
        mov eax, [ecx+4]
        test eax, eax
        jnz loc_44D5BD
        mov eax, 800401F0h
        ret
loc_44D5BD:
        mov dword ptr [ecx+30h], 0
        mov eax, [eax]
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+48h]
        ret
    }
}
#else
int Platform_InvokeInterface(void* state, int (*invoke)(void*)) {
    unsigned char* bytes = (unsigned char*)state;
    void* interface_ptr = *(void**)(bytes + 4);
    if (interface_ptr == 0)
        return (int)0x800401F0u;
    *(int*)(bytes + 0x30) = 0;
    return invoke != 0 ? invoke(interface_ptr) : 0;
}
#endif

extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(
    OSVERSIONINFOA* version_info);

// 0x0044BD10 - Map the GetVersionExA result onto the game's numeric OS
// codes: Win32s reports 31, Windows 95/98 report 95/98 (any other 9x 4.x
// minor collapses to 98), NT 5.x reports 2000, other NT releases report
// (major * 100 + minor) * 10, non-4.x 9x releases report major * 100 +
// minor, and unknown platforms report -1. No surviving retail caller.
#ifdef _MSC_VER
__declspec(naked) int Platform_GetOsVersionCode(void) {
    __asm {
        push ebp
        mov ebp, esp
        and esp, 0FFFFFFF8h
        sub esp, 0A4h
        mov eax, ___security_cookie
        xor eax, ebp
        push edi
        mov [esp+0A4h], eax
        xor eax, eax
        mov ecx, 25h
        lea edi, [esp+8]
        rep stosd
        lea eax, [esp+8]
        push eax
        mov dword ptr [esp+0Ch], 94h
        call dword ptr [dword_46612C]
        mov eax, [esp+18h]
        sub eax, 0
        je platform_zero
        dec eax
        je platform_one
        dec eax
        je platform_two
        or eax, 0FFFFFFFFh
return_common:
        pop edi
        mov ecx, [esp+0A0h]
        xor ecx, ebp
        call security_check_cookie
        mov esp, ebp
        pop ebp
        ret
platform_two:
        mov eax, [esp+0Ch]
        cmp eax, 5
        jne nt_other
        mov eax, 7D0h
        pop edi
        mov ecx, [esp+0A0h]
        xor ecx, ebp
        call security_check_cookie
        mov esp, ebp
        pop ebp
        ret
nt_other:
        mov edx, [esp+10h]
        imul eax, eax, 64h
        add eax, edx
        lea eax, [eax+eax*4]
        shl eax, 1
        pop edi
        mov ecx, [esp+0A0h]
        xor ecx, ebp
        call security_check_cookie
        mov esp, ebp
        pop ebp
        ret
platform_one:
        mov eax, [esp+0Ch]
        cmp eax, 4
        jne win_other
        mov eax, [esp+10h]
        neg eax
        sbb eax, eax
        and eax, 3
        add eax, 5Fh
        pop edi
        mov ecx, [esp+0A0h]
        xor ecx, ebp
        call security_check_cookie
        mov esp, ebp
        pop ebp
        ret
win_other:
        mov ecx, [esp+10h]
        imul eax, eax, 64h
        add eax, ecx
        pop edi
        mov ecx, [esp+0A0h]
        xor ecx, ebp
        call security_check_cookie
        mov esp, ebp
        pop ebp
        ret
platform_zero:
        mov ecx, [esp+0A4h]
        xor ecx, ebp
        mov eax, 1Fh
        pop edi
        call security_check_cookie
        mov esp, ebp
        pop ebp
        ret
    }
}
#else
int Platform_GetOsVersionCode(void) {
    OSVERSIONINFOA info = {};
    info.dwOSVersionInfoSize = sizeof(info);
    GetVersionExA(&info);
    switch (info.dwPlatformId) {
    case 0:
        return 31;
    case 1:
        if (info.dwMajorVersion == 4)
            return info.dwMinorVersion == 0 ? 95 : 98;
        return (int)(info.dwMajorVersion * 100 + info.dwMinorVersion);
    case 2:
        if (info.dwMajorVersion == 5)
            return 2000;
        return (int)(info.dwMajorVersion * 100 + info.dwMinorVersion) * 10;
    default:
        return -1;
    }
}
#endif
