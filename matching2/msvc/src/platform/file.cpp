#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435370..0x004353AC: FileHandle_OpenRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FileHandle_OpenRetail_00435370() {
    __asm {
    L_00435370:
        sub esp,10Ch
    L_00435376:
        mov eax,dword ptr [data_00473660]
    L_0043537b:
        xor eax,esp
    L_0043537d:
        push ebx
    L_0043537e:
        push ebp
    L_0043537f:
        mov ebp,dword ptr [esp+118h]
    L_00435386:
        push esi
    L_00435387:
        push edi
    L_00435388:
        mov esi,ecx
    L_0043538a:
        mov dword ptr [esp+118h],eax
    L_00435391:
        mov eax,dword ptr [esi]
    L_00435393:
        xor edi,edi
    L_00435395:
        mov dword ptr [esp+10h],edi
    L_00435399:
        call dword ptr [eax+4]
    L_0043539c:
        mov eax,dword ptr [esp+124h]
    L_004353a3:
        mov ebx,eax
    L_004353a5:
        mov al,byte ptr [eax]
    L_004353a7:
        test al,al
    L_004353a9:
        TH10_REL8(0x74, 0x004353a9, VA_asm_target_004353f6)
    L_004353ab:
        TH10_REL8(0xeb, 0x004353ab, VA_asm_FileHandle_OpenRetail_part_004353b0)
    }
}

// 0x004353B0..0x0043545E: FileHandle_OpenRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FileHandle_OpenRetail_part_004353b0() {
    __asm {
    L_004353b0:
        cmp al,72h
    L_004353b2:
        je short L_004353c6
    L_004353b4:
        cmp al,77h
    L_004353b6:
        je short L_004353d4
    L_004353b8:
        cmp al,61h
    L_004353ba:
        je short L_004353e2
    L_004353bc:
        mov al,byte ptr [ebx+1]
    L_004353bf:
        inc ebx
    L_004353c0:
        test al,al
    L_004353c2:
        jne short L_004353b0
    L_004353c4:
        jmp short L_00435444
    L_004353c6:
        mov dword ptr [esi+8],80000000h
    L_004353cd:
        mov edi,3
    L_004353d2:
        jmp short L_004353f6
    L_004353d4:
        push ebp
    L_004353d5:
        call dword ptr [data_004660c0]
    L_004353db:
        mov edi,2
    L_004353e0:
        jmp short L_004353ef
    L_004353e2:
        mov dword ptr [esp+10h],1
    L_004353ea:
        mov edi,4
    L_004353ef:
        mov dword ptr [esi+8],40000000h
    L_004353f6:
        cmp byte ptr [ebx],0
    L_004353f9:
        je short L_00435429
    L_004353fb:
        mov eax,ebp
    L_004353fd:
        lea ecx,[esp+14h]
    L_00435401:
        call asm_File_ResolvePath_00435610
    L_00435406:
        mov ecx,dword ptr [esi+8]
    L_00435409:
        push 0
    L_0043540b:
        push 8000080h
    L_00435410:
        push edi
    L_00435411:
        push 0
    L_00435413:
        push 1
    L_00435415:
        push ecx
    L_00435416:
        lea edx,[esp+2Ch]
    L_0043541a:
        push edx
    L_0043541b:
        call dword ptr [data_004660c4]
    L_00435421:
        cmp eax,0FFFFFFFFh
    L_00435424:
        mov dword ptr [esi+4],eax
    L_00435427:
        jne short L_0043542d
    L_00435429:
        xor al,al
    L_0043542b:
        jmp short L_00435444
    L_0043542d:
        mov ecx,dword ptr [esp+10h]
    L_00435431:
        test ecx,ecx
    L_00435433:
        je short L_00435442
    L_00435435:
        push 2
    L_00435437:
        push 0
    L_00435439:
        push 0
    L_0043543b:
        push eax
    L_0043543c:
        call dword ptr [data_004660c8]
    L_00435442:
        mov al,1
    L_00435444:
        mov ecx,dword ptr [esp+118h]
    L_0043544b:
        pop edi
    L_0043544c:
        pop esi
    L_0043544d:
        pop ebp
    L_0043544e:
        pop ebx
    L_0043544f:
        xor ecx,esp
    L_00435451:
        call asm_security_check_cookie_00458ea5
    L_00435456:
        add esp,10Ch
    L_0043545c:
        ret 8
    }
}

// 0x00435610..0x00435688: ?File_ResolvePath@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_File_ResolvePath_00435610() {
    __asm {
    L_00435610:
        push esi
    L_00435611:
        push edi
    L_00435612:
        mov esi,eax
    L_00435614:
        push 3Ah
    L_00435616:
        push esi
    L_00435617:
        mov edi,ecx
    L_00435619:
        call asm_FUN_00452730_00452730
    L_0043561e:
        add esp,8
    L_00435621:
        test eax,eax
    L_00435623:
        je short L_0043563d
    L_00435625:
        mov eax,esi
    L_00435627:
        sub edi,esi
    L_00435629:
        lea esp,[esp+force_disp32_zero]
    L_00435630:
        mov cl,byte ptr [eax]
    L_00435632:
        mov byte ptr [edi+eax],cl
    L_00435635:
        inc eax
    L_00435636:
        test cl,cl
    L_00435638:
        jne short L_00435630
    L_0043563a:
        pop edi
    L_0043563b:
        pop esi
    L_0043563c:
        ret
    L_0043563d:
        push 104h
    L_00435642:
        push edi
    L_00435643:
        push 0
    L_00435645:
        call dword ptr [data_004660dc]
    L_0043564b:
        push 5Ch
    L_0043564d:
        push edi
    L_0043564e:
        call asm_strrchr_00452930
    L_00435653:
        add esp,8
    L_00435656:
        test eax,eax
    L_00435658:
        jne short L_0043565c
    L_0043565a:
        mov byte ptr [edi],al
    L_0043565c:
        mov byte ptr [eax+1],0
    L_00435660:
        mov eax,esi
    L_00435662:
        mov ecx,esi
    L_00435664:
        mov dl,byte ptr [eax]
    L_00435666:
        inc eax
    L_00435667:
        test dl,dl
    L_00435669:
        jne short L_00435664
    L_0043566b:
        sub eax,ecx
    L_0043566d:
        mov esi,ecx
    L_0043566f:
        dec edi
    L_00435670:
        mov cl,byte ptr [edi+1]
    L_00435673:
        inc edi
    L_00435674:
        test cl,cl
    L_00435676:
        jne short L_00435670
    L_00435678:
        mov ecx,eax
    L_0043567a:
        shr ecx,2
    L_0043567d:
        rep movsd
    L_0043567f:
        mov ecx,eax
    L_00435681:
        and ecx,3
    L_00435684:
        rep movsb
    L_00435686:
        pop edi
    L_00435687:
        pop esi
    L_00435688:
        ret
    }
}

// 0x0044B540..0x0044B619: ?File_WriteWholeFile@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_File_WriteWholeFile_0044b540() {
    __asm {
    L_0044b540:
        push ecx
    L_0044b541:
        push esi
    L_0044b542:
        push 4922A4h
    L_0044b547:
        call dword ptr [data_004660b0]
    L_0044b54d:
        mov al,byte ptr [data_0049231e]
    L_0044b552:
        push 0
    L_0044b554:
        push 80h
    L_0044b559:
        push 2
    L_0044b55b:
        push 0
    L_0044b55d:
        inc al
    L_0044b55f:
        push 1
    L_0044b561:
        mov byte ptr [data_0049231e],al
    L_0044b566:
        mov eax,dword ptr [esp+20h]
    L_0044b56a:
        push 40000000h
    L_0044b56f:
        push eax
    L_0044b570:
        call dword ptr [data_004660c4]
    L_0044b576:
        mov esi,eax
    L_0044b578:
        cmp esi,0FFFFFFFFh
    L_0044b57b:
        push 0
    L_0044b57d:
        jne short L_0044b5c2
    L_0044b57f:
        push 0
    L_0044b581:
        lea ecx,[esp+14h]
    L_0044b585:
        push ecx
    L_0044b586:
        push 400h
    L_0044b58b:
        call dword ptr [data_0046610c]
    L_0044b591:
        push eax
    L_0044b592:
        push 0
    L_0044b594:
        push 1300h
    L_0044b599:
        call dword ptr [data_00466124]
    L_0044b59f:
        mov edx,dword ptr [esp+0Ch]
    L_0044b5a3:
        push edx
    L_0044b5a4:
        call dword ptr [data_00466128]
    L_0044b5aa:
        push 4922A4h
    L_0044b5af:
        call dword ptr [data_004660b4]
    L_0044b5b5:
        dec byte ptr [data_0049231e]
    L_0044b5bb:
        mov eax,esi
    L_0044b5bd:
        pop esi
    L_0044b5be:
        pop ecx
    L_0044b5bf:
        ret 8
    L_0044b5c2:
        mov ecx,dword ptr [esp+14h]
    L_0044b5c6:
        lea eax,[esp+8]
    L_0044b5ca:
        push eax
    L_0044b5cb:
        push edi
    L_0044b5cc:
        push ecx
    L_0044b5cd:
        push esi
    L_0044b5ce:
        call dword ptr [data_004660d4]
    L_0044b5d4:
        cmp edi,dword ptr [esp+4]
    L_0044b5d8:
        push esi
    L_0044b5d9:
        je short L_0044b5fc
    L_0044b5db:
        call dword ptr [data_004660cc]
    L_0044b5e1:
        push 4922A4h
    L_0044b5e6:
        call dword ptr [data_004660b4]
    L_0044b5ec:
        dec byte ptr [data_0049231e]
    L_0044b5f2:
        mov eax,0FFFFFFFEh
    L_0044b5f7:
        pop esi
    L_0044b5f8:
        pop ecx
    L_0044b5f9:
        ret 8
    L_0044b5fc:
        call dword ptr [data_004660cc]
    L_0044b602:
        push 4922A4h
    L_0044b607:
        call dword ptr [data_004660b4]
    L_0044b60d:
        dec byte ptr [data_0049231e]
    L_0044b613:
        xor eax,eax
    L_0044b615:
        pop esi
    L_0044b616:
        pop ecx
    L_0044b617:
        ret 8
    }
}

// 0x0044B740..0x0044B78B: ?File_WriteShared@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_File_WriteShared_0044b740() {
    __asm {
    L_0044b740:
        push ecx
    L_0044b741:
        mov eax,dword ptr [data_00474c38]
    L_0044b746:
        cmp eax,0FFFFFFFFh
    L_0044b749:
        jne short L_0044b74f
    L_0044b74b:
        or eax,eax
    L_0044b74d:
        pop ecx
    L_0044b74e:
        ret
    L_0044b74f:
        push 0
    L_0044b751:
        lea ecx,[esp+4]
    L_0044b755:
        push ecx
    L_0044b756:
        push esi
    L_0044b757:
        push edx
    L_0044b758:
        push eax
    L_0044b759:
        call dword ptr [data_004660d4]
    L_0044b75f:
        cmp esi,dword ptr [esp]
    L_0044b762:
        je short L_0044b788
    L_0044b764:
        mov eax,dword ptr [data_00474c38]
    L_0044b769:
        push eax
    L_0044b76a:
        call dword ptr [data_004660cc]
    L_0044b770:
        push 4922A4h
    L_0044b775:
        call dword ptr [data_004660b4]
    L_0044b77b:
        dec byte ptr [data_0049231e]
    L_0044b781:
        mov eax,0FFFFFFFEh
    L_0044b786:
        pop ecx
    L_0044b787:
        ret
    L_0044b788:
        xor eax,eax
    L_0044b78a:
        pop ecx
    L_0044b78b:
        ret
    }
}

// 0x0044B790..0x0044B7D9: ?File_ReadShared@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_File_ReadShared_0044b790() {
    __asm {
    L_0044b790:
        push ecx
    L_0044b791:
        cmp dword ptr [data_00474c38],0FFFFFFFFh
    L_0044b798:
        jne short L_0044b79e
    L_0044b79a:
        xor eax,eax
    L_0044b79c:
        pop ecx
    L_0044b79d:
        ret
    L_0044b79e:
        push esi
    L_0044b79f:
        push edi
    L_0044b7a0:
        call asm_malloc_00452706
    L_0044b7a5:
        mov esi,eax
    L_0044b7a7:
        add esp,4
    L_0044b7aa:
        test esi,esi
    L_0044b7ac:
        jne short L_0044b7bf
    L_0044b7ae:
        mov eax,dword ptr [data_00474c38]
    L_0044b7b3:
        push eax
    L_0044b7b4:
        call dword ptr [data_004660cc]
    L_0044b7ba:
        xor eax,eax
    L_0044b7bc:
        pop esi
    L_0044b7bd:
        pop ecx
    L_0044b7be:
        ret
    L_0044b7bf:
        mov edx,dword ptr [data_00474c38]
    L_0044b7c5:
        push 0
    L_0044b7c7:
        lea ecx,[esp+8]
    L_0044b7cb:
        push ecx
    L_0044b7cc:
        push edi
    L_0044b7cd:
        push esi
    L_0044b7ce:
        push edx
    L_0044b7cf:
        call dword ptr [data_004660d0]
    L_0044b7d5:
        mov eax,esi
    L_0044b7d7:
        pop esi
    L_0044b7d8:
        pop ecx
    L_0044b7d9:
        ret
    }
}

// Recovered semantic C++ definitions.
#include "th10/platform/file.hpp"

extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE handle);
extern "C" __declspec(dllimport) BOOL __stdcall ReadFile(
    HANDLE handle, void* buffer, DWORD size, DWORD* bytes_read, void* overlapped);
extern "C" __declspec(dllimport) BOOL __stdcall WriteFile(
    HANDLE handle, const void* buffer, DWORD size, DWORD* bytes_written,
    void* overlapped);
extern "C" __declspec(dllimport) DWORD __stdcall SetFilePointer(
    HANDLE handle, LONG distance, LONG* distance_high, DWORD origin);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileSize(
    HANDLE handle, DWORD* size_high);

extern "C" void* __cdecl entry_malloc_00452706(unsigned int size);
extern "C" void __cdecl entry_free_00452422(void* memory);

struct FileCriticalSection;
extern "C" HANDLE g_file_probe_handle;
extern "C" FileCriticalSection g_file_critical_section;
extern "C" unsigned char g_file_critical_depth;
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
    FileCriticalSection* section);

// The KERNEL32 slots at 0x004660B0..0x00466128 are bound by the retail layout
// script under their slot names, so the calls go through the slot's stored
// pointer exactly as the retail import thunks do.
typedef void (__stdcall* EnterCriticalSectionFn)(void* section);
typedef HANDLE (__stdcall* CreateFileFn)(LPCSTR path, DWORD access, DWORD share,
                                         void* attributes, DWORD creation,
                                         DWORD flags, HANDLE template_file);
typedef DWORD (__stdcall* GetLastErrorFn)(void);
typedef DWORD (__stdcall* FormatMessageFn)(DWORD flags, void* source, DWORD message_id,
                                           DWORD language_id, LPSTR* buffer,
                                           DWORD buffer_size, void* arguments);
typedef HANDLE (__stdcall* LocalFreeFn)(void* memory);

namespace {
const DWORD kReadAccess = 0x80000000;
const DWORD kWriteAccess = 0x40000000;
const DWORD kCurrentPosition = 1;
} // namespace

FileHandle::FileHandle() : handle((HANDLE)-1), access(0) {
}

__declspec(noinline) FileHandle::~FileHandle() {
    Close();
}

void FileHandle::Close() {
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        handle = (HANDLE)-1;
        access = 0;
    }
}

DWORD FileHandle::Read(void* destination, DWORD size) {
    DWORD bytes_read = 0;
    if (access != kReadAccess)
        return 0;
    ReadFile(handle, destination, size, &bytes_read, 0);
    return bytes_read;
}

BYTE FileHandle::Write(const void* source, DWORD size) {
    DWORD bytes_written = 0;
    if (access != kWriteAccess)
        return 0;
    WriteFile(handle, source, size, &bytes_written, 0);
    return (BYTE)(size == bytes_written);
}

DWORD FileHandle::Tell() const {
    if (handle == (HANDLE)-1)
        return 0;
    return SetFilePointer(handle, 0, 0, kCurrentPosition);
}

DWORD FileHandle::GetSize() const {
    if (handle == (HANDLE)-1)
        return 0;
    return GetFileSize(handle, 0);
}

BYTE FileHandle::Seek(LONG distance, DWORD origin) {
    if (handle == (HANDLE)-1)
        return 0;
    SetFilePointer(handle, distance, 0, origin);
    return 1;
}

// 0x00435580 - Read the whole file into a fresh heap block when the file is
// no larger than the caller's capacity; the position is restored around the
// read and the block is released if either step fails.
void* FileHandle::ReadWhole(DWORD capacity) {
    if (access != kReadAccess)
        return 0;
    DWORD size = GetSize();
    if (size > capacity)
        return 0;
    void* buffer = entry_malloc_00452706(size);
    if (buffer == 0)
        return 0;
    DWORD position = Tell();
    if (Seek(position, 0) == 0)
        return 0;
    if (Read(buffer, size) == 0) {
        entry_free_00452422(buffer);
        return 0;
    }
    Seek(position, 0);
    return buffer;
}

// 0x0044B4D0 - Probe one path inside the file subsystem's critical section:
// open it for reading, close it at once and report whether it was there. The
// nesting counter brackets the whole probe.
int __stdcall asm_File_ProbeExists_0044b4d0(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&data_004660b0)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&data_004660c4)(
        path, 0x80000000, 1, 0, 3, 0x8000080, 0);
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
        return 1;
    }
    LeaveCriticalSection(&g_file_critical_section);
    --g_file_critical_depth;
    return 0;
}

// 0x0044B620 - Open the shared probe file for writing, truncating it. A
// failure formats the Win32 error text, releases it again and unwinds the
// critical section, reporting -1; the shared handle is -1 after a failure.
int __stdcall asm_File_OpenSharedWrite_0044b620(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&data_004660b0)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&data_004660c4)(
        path, 0x40000000, 1, 0, 2, 0x80, 0);
    g_file_probe_handle = handle;
    if (handle == (HANDLE)-1) {
        LPSTR message;
        (*(FormatMessageFn*)&data_00466124)(
            0x1300, 0, (*(GetLastErrorFn*)&data_0046610c)(), 0x400, &message, 0, 0);
        (*(LocalFreeFn*)&data_00466128)(message);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
        return -1;
    }
    return 0;
}

// 0x0044B6B0 - Open the shared probe file for reading, failing the same way as
// the write open does.
int __stdcall asm_File_OpenSharedRead_0044b6b0(LPCSTR path) {
    (*(EnterCriticalSectionFn*)&data_004660b0)(&g_file_critical_section);
    ++g_file_critical_depth;
    HANDLE handle = (*(CreateFileFn*)&data_004660c4)(
        path, 0x80000000, 1, 0, 3, 0x8000080, 0);
    g_file_probe_handle = handle;
    if (handle == (HANDLE)-1) {
        LPSTR message;
        (*(FormatMessageFn*)&data_00466124)(
            0x1300, 0, (*(GetLastErrorFn*)&data_0046610c)(), 0x400, &message, 0, 0);
        (*(LocalFreeFn*)&data_00466128)(message);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
        return -1;
    }
    return 0;
}

// 0x0044B7E0 - Close the shared probe handle, release the file subsystem's
// critical section, and balance its nesting counter.
int File_CloseProbeHandle() {
    HANDLE handle = g_file_probe_handle;
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        LeaveCriticalSection(&g_file_critical_section);
        --g_file_critical_depth;
    }
    return 0;
}
