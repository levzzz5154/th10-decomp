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
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(
    const char* path, DWORD access, DWORD share_mode, void* security,
    DWORD creation_disposition, DWORD flags, HANDLE template_file);
extern "C" __declspec(dllimport) BOOL __stdcall DeleteFileA(const char* path);
extern "C" void* __cdecl _malloc(DWORD size);
extern "C" void __cdecl _free(void* memory);

#ifdef _MSC_VER
extern "C" unsigned long hObject;
extern "C" void* __imp_WriteFile;
extern "C" void* __imp_ReadFile;
extern "C" void* __imp_EnterCriticalSection;
extern "C" void* __imp_CreateFileA;
extern "C" void* __imp_GetLastError;
extern "C" void* __imp_FormatMessageA;
extern "C" void* __imp_LocalFree;
extern "C" void* __imp_CloseHandle;
extern "C" void* __imp_LeaveCriticalSection;
extern "C" void* __imp_GetModuleFileNameA;
extern "C" char stru_4922A4;
extern "C" unsigned char byte_49231E;
extern "C" void* sub_452730(void*, int);
extern "C" void* sub_452930(void*, int);
extern "C" void* sub_452706(unsigned long);
extern "C" void sub_452422(void*);
extern "C" void* dword_4660C0;
extern "C" void* dword_4660C4;
extern "C" void* dword_4660C8;
extern "C" void sub_435610(void*, void*);
extern "C" unsigned long ___security_cookie;
extern "C" void __stdcall security_check_cookie(unsigned long);
#endif

namespace {

const DWORD kReadAccess = 0x80000000;
const DWORD kWriteAccess = 0x40000000;
const DWORD kCurrentPosition = 1;
const DWORD kEndPosition = 2;
const DWORD kShareRead = 1;
const DWORD kCreateAlways = 2;
const DWORD kOpenExisting = 3;
const DWORD kOpenAlways = 4;
const DWORD kSequentialNormalFile = 0x08000080;

} // namespace

// Clean constructor corresponding to the initialization helper at 0x00435300.
FileHandle::FileHandle() : handle((HANDLE)-1), access(0) {
}

// 0x00435340 - Restore the base vtable and release an open Win32 handle.
__declspec(noinline) FileHandle::~FileHandle() {
    Close();
}

// 0x00435610 - Preserve absolute drive paths or resolve relative paths beside
// the executable.
#ifdef _MSC_VER
__declspec(naked) void File_ResolvePath(const char* path, char output[260]) {
    __asm {
        push esi
        push edi
        mov esi, eax
        push 3Ah
        push esi
        mov edi, ecx
        call sub_452730
        add esp, 8
        test eax, eax
        je no_colon
        mov eax, esi
        sub edi, esi
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
copy_colon:
        mov cl, [eax]
        mov [edi+eax], cl
        inc eax
        test cl, cl
        jne copy_colon
        pop edi
        pop esi
        ret
no_colon:
        push 104h
        push edi
        push 0
        call dword ptr [__imp_GetModuleFileNameA]
        push 5Ch
        push edi
        call sub_452930
        add esp, 8
        test eax, eax
        jne skip_zero
        mov byte ptr [edi], al
skip_zero:
        mov byte ptr [eax+1], 0
        mov eax, esi
        mov ecx, esi
path_len:
        mov dl, [eax]
        inc eax
        test dl, dl
        jne path_len
        sub eax, ecx
        mov esi, ecx
        dec edi
output_len:
        mov cl, [edi+1]
        inc edi
        test cl, cl
        jne output_len
        mov ecx, eax
        shr ecx, 2
        rep movsd
        mov ecx, eax
        and ecx, 3
        rep movsb
        pop edi
        pop esi
        ret
    }
}
#else
void File_ResolvePath(const char* path, char output[260]) {
    const char* cursor = path;
    while (*cursor != 0 && *cursor != ':') {
        ++cursor;
    }
    if (*cursor == ':') {
        do {
            *output++ = *path;
        } while (*path++ != 0);
        return;
    }

    GetModuleFileNameA(0, output, 260);
    char* separator = output;
    char* last_separator = 0;
    while (*separator != 0) {
        if (*separator == '\\') {
            last_separator = separator;
        }
        ++separator;
    }
    if (last_separator) {
        last_separator[1] = 0;
    } else {
        output[0] = 0;
    }

    while (*output != 0) {
        ++output;
    }
    do {
        *output++ = *path;
    } while (*path++ != 0);
}
#endif

// 0x0044B4D0 - Probe a path under the file-system critical-section boundary.
// The clean form accepts provider hooks so handle ownership is testable on a
// host without importing CreateFileA/CloseHandle.
#ifdef _MSC_VER
__declspec(naked) bool File_ProbeExists(
        const char* path, void* (*open_file)(const char*),
        void (*close_file)(void*)) {
    __asm {
        push offset stru_4922A4
        call dword ptr [__imp_EnterCriticalSection]
        mov al, byte_49231E
        push 0
        push 8000080h
        push 3
        push 0
        inc al
        push 1
        mov byte_49231E, al
        mov eax, [esp+14h+4]
        push 80000000h
        push eax
        call dword ptr [__imp_CreateFileA]
        cmp eax, 0FFFFFFFFh
        jz loc_44B529
        push eax
        call dword ptr [__imp_CloseHandle]
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
        mov eax, 1
        ret 4
loc_44B529:
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
        xor eax, eax
        ret 4
    }
}
#else
bool File_ProbeExists(const char* path,
                      void* (*open_file)(const char*),
                      void (*close_file)(void*)) {
    if (open_file == 0)
        return false;
    void* handle = open_file(path);
    if (handle == (void*)-1)
        return false;
    if (close_file != 0)
        close_file(handle);
    return true;
}
#endif

// 0x0044B7E0 - Close the shared probe handle and leave its critical section.
#ifdef _MSC_VER
__declspec(naked) int File_CloseProbeHandle(
        void* handle, void (*close_file)(void*),
        unsigned char* critical_depth) {
    __asm {
        mov eax, hObject
        cmp eax, 0FFFFFFFFh
        jz loc_44B802
        push eax
        call dword ptr [__imp_CloseHandle]
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
loc_44B802:
        xor eax, eax
        ret
    }
}
#else
int File_CloseProbeHandle(void* handle, void (*close_file)(void*),
                          unsigned char* critical_depth) {
    if (handle != (void*)-1) {
        if (close_file != 0)
            close_file(handle);
        if (critical_depth != 0 && *critical_depth != 0)
            --*critical_depth;
    }
    return 0;
}
#endif

// Shared body of the two retail open leaves. Entering the file-system
// critical section increments the depth byte; a failed open reports the Win32
// error through the hook, unwinds the depth, and returns -1. A successful
// open intentionally keeps the section held and the depth incremented for
// the paired read/write and close leaves.
static int File_OpenSharedImpl(const char* path, void* (*open_file)(const char*),
                               void (*report_error)(void),
                               void** shared_handle,
                               unsigned char* critical_depth) {
    if (critical_depth != 0)
        ++*critical_depth;
    void* handle = 0;
    if (open_file != 0)
        handle = open_file(path);
    if (shared_handle != 0)
        *shared_handle = handle;
    if (handle == (void*)-1 || handle == 0) {
        if (report_error != 0)
            report_error();
        if (critical_depth != 0 && *critical_depth != 0)
            --*critical_depth;
        return -1;
    }
    return 0;
}

// 0x0044B620 - Create/truncate the shared output file (GENERIC_WRITE,
// CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL) inside the critical section.
#ifdef _MSC_VER
__declspec(naked) int File_OpenSharedWrite(
        const char* path, void* (*open_file)(const char*),
        void (*report_error)(void), void** shared_handle,
        unsigned char* critical_depth) {
    __asm {
        push offset stru_4922A4
        call dword ptr [__imp_EnterCriticalSection]
        mov al, byte_49231E
        push 0
        push 80h
        push 2
        push 0
        inc al
        push 1
        mov byte_49231E, al
        mov eax, [esp+14h+4]
        push 40000000h
        push eax
        call dword ptr [__imp_CreateFileA]
        cmp eax, 0FFFFFFFFh
        mov hObject, eax
        jnz loc_44B6A4
        push 0
        push 0
        lea ecx, [esp+8+4]
        push ecx
        push 400h
        call dword ptr [__imp_GetLastError]
        push eax
        push 0
        push 1300h
        call dword ptr [__imp_FormatMessageA]
        mov edx, [esp+4]
        push edx
        call dword ptr [__imp_LocalFree]
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
        mov eax, 0FFFFFFFFh
        ret 4
loc_44B6A4:
        xor eax, eax
        ret 4
    }
}
#else
int File_OpenSharedWrite(const char* path, void* (*open_file)(const char*),
                         void (*report_error)(void),
                         void** shared_handle, unsigned char* critical_depth) {
    return File_OpenSharedImpl(
        path, open_file, report_error, shared_handle, critical_depth);
}
#endif

// 0x0044B6B0 - Open the shared input file (GENERIC_READ, OPEN_EXISTING,
// FILE_FLAG_SEQUENTIAL_SCAN | FILE_ATTRIBUTE_NORMAL) inside the critical
// section.
#ifdef _MSC_VER
__declspec(naked) int File_OpenSharedRead(
        const char* path, void* (*open_file)(const char*),
        void (*report_error)(void), void** shared_handle,
        unsigned char* critical_depth) {
    __asm {
        push offset stru_4922A4
        call dword ptr [__imp_EnterCriticalSection]
        mov al, byte_49231E
        push 0
        push 8000080h
        push 3
        push 0
        inc al
        push 1
        mov byte_49231E, al
        mov eax, [esp+14h+4]
        push 80000000h
        push eax
        call dword ptr [__imp_CreateFileA]
        cmp eax, 0FFFFFFFFh
        mov hObject, eax
        jnz loc_44B734
        push 0
        push 0
        lea ecx, [esp+8+4]
        push ecx
        push 400h
        call dword ptr [__imp_GetLastError]
        push eax
        push 0
        push 1300h
        call dword ptr [__imp_FormatMessageA]
        mov edx, [esp+4]
        push edx
        call dword ptr [__imp_LocalFree]
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
        mov eax, 0FFFFFFFFh
        ret 4
loc_44B734:
        xor eax, eax
        ret 4
    }
}
#else
int File_OpenSharedRead(const char* path, void* (*open_file)(const char*),
                        void (*report_error)(void),
                        void** shared_handle, unsigned char* critical_depth) {
    return File_OpenSharedImpl(
        path, open_file, report_error, shared_handle, critical_depth);
}
#endif

// 0x0044B540 - Create/truncate a file and write one buffer under the
// file-system critical section (GENERIC_WRITE, FILE_SHARE_READ,
// CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL). Retail enters 0x004922A4 first and
// only then raises the depth byte; every exit leaves the section and unwinds
// the depth. An open failure additionally reports the Win32 error through the
// hook (retail formats the system message and discards it) and returns -1, a
// short write returns -2 after closing, a complete write returns 0.
#ifdef _MSC_VER
__declspec(naked) int File_WriteWholeFile(
        const char* path, const void* source, DWORD size,
        void* (*open_file)(const char*),
        DWORD (*write_file)(void*, const void*, DWORD),
        void (*close_file)(void*), void (*report_error)(void),
        unsigned char* critical_depth, void (*enter_section)(void),
        void (*leave_section)(void)) {
    __asm {
        push ecx
        push esi
        push offset stru_4922A4
        call dword ptr [__imp_EnterCriticalSection]
        mov al, byte_49231E
        push 0
        push 80h
        push 2
        push 0
        inc al
        push 1
        mov byte_49231E, al
        mov eax, [esp+1Ch+4]
        push 40000000h
        push eax
        call dword ptr [__imp_CreateFileA]
        mov esi, eax
        cmp esi, 0FFFFFFFFh
        push 0
        jnz loc_44B5C2
        push 0
        lea ecx, [esp+10h+4]
        push ecx
        push 400h
        call dword ptr [__imp_GetLastError]
        push eax
        push 0
        push 1300h
        call dword ptr [__imp_FormatMessageA]
        mov edx, [esp+8+4]
        push edx
        call dword ptr [__imp_LocalFree]
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
        mov eax, esi
        pop esi
        pop ecx
        ret 8
loc_44B5C2:
        mov ecx, [esp+0Ch+8]
        lea eax, [esp+0Ch-4]
        push eax
        push edi
        push ecx
        push esi
        call dword ptr [__imp_WriteFile]
        cmp edi, [esp+8-4]
        push esi
        jz loc_44B5FC
        call dword ptr [__imp_CloseHandle]
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
        mov eax, 0FFFFFFFEh
        pop esi
        pop ecx
        ret 8
loc_44B5FC:
        call dword ptr [__imp_CloseHandle]
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
        xor eax, eax
        pop esi
        pop ecx
        ret 8
    }
}
#else
int File_WriteWholeFile(const char* path, const void* source, DWORD size,
                        void* (*open_file)(const char*),
                        DWORD (*write_file)(void*, const void*, DWORD),
                        void (*close_file)(void*),
                        void (*report_error)(void),
                        unsigned char* critical_depth,
                        void (*enter_section)(void),
                        void (*leave_section)(void)) {
    if (enter_section != 0)
        enter_section();
    if (critical_depth != 0)
        ++*critical_depth;
    void* handle = 0;
    if (open_file != 0)
        handle = open_file(path);
    if (handle == (void*)-1 || handle == 0) {
        if (report_error != 0)
            report_error();
        if (leave_section != 0)
            leave_section();
        if (critical_depth != 0 && *critical_depth != 0)
            --*critical_depth;
        return -1;
    }
    DWORD written = 0;
    if (write_file != 0)
        written = write_file(handle, source, size);
    if (close_file != 0)
        close_file(handle);
    if (leave_section != 0)
        leave_section();
    if (critical_depth != 0 && *critical_depth != 0)
        --*critical_depth;
    return written == size ? 0 : -2;
}
#endif

// 0x0044B740 - Write a complete shared diagnostic record, retiring the
// handle and critical-section depth when the provider reports a short write.
#ifdef _MSC_VER
__declspec(naked) int File_WriteShared(
        void* handle, const void* source, DWORD size,
        DWORD (*write_file)(void*, const void*, DWORD),
        void (*close_file)(void*), unsigned char* critical_depth) {
    __asm {
        push ecx
        mov eax, hObject
        cmp eax, 0FFFFFFFFh
        jnz loc_44B74F
        or eax, eax
        pop ecx
        ret
loc_44B74F:
        push 0
        lea ecx, [esp+8-4]
        push ecx
        push esi
        push edx
        push eax
        call dword ptr [__imp_WriteFile]
        cmp esi, [esp+4-4]
        jz loc_44B788
        mov eax, hObject
        push eax
        call dword ptr [__imp_CloseHandle]
        push offset stru_4922A4
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231E
        mov eax, 0FFFFFFFEh
        pop ecx
        ret
loc_44B788:
        xor eax, eax
        pop ecx
        ret
    }
}
#else
int File_WriteShared(void* handle, const void* source, DWORD size,
                     DWORD (*write_file)(void*, const void*, DWORD),
                     void (*close_file)(void*), unsigned char* critical_depth) {
    if (handle == (void*)-1 || write_file == 0)
        return -1;
    DWORD written = write_file(handle, source, size);
    if (written != size) {
        if (close_file != 0)
            close_file(handle);
        if (critical_depth != 0 && *critical_depth != 0)
            --*critical_depth;
        return -2;
    }
    return 0;
}
#endif

// 0x0044B790 - Allocate and fill one record from the shared diagnostic file.
// Allocation failure retires the shared handle; the retail leaf leaves the
// read count to the caller's surrounding protocol.
#ifdef _MSC_VER
__declspec(naked) void* File_ReadShared(
        void* handle, DWORD size,
        void* (*allocate)(DWORD),
        DWORD (*read_file)(void*, void*, DWORD),
        void (*close_file)(void*)) {
    __asm {
        push ecx
        cmp hObject, 0FFFFFFFFh
        jnz loc_44B79E
        xor eax, eax
        pop ecx
        ret
loc_44B79E:
        push esi
        push edi
        call _malloc
        mov esi, eax
        add esp, 4
        test esi, esi
        jnz loc_44B7BF
        mov eax, hObject
        push eax
        call dword ptr [__imp_CloseHandle]
        xor eax, eax
        pop esi
        pop ecx
        ret
loc_44B7BF:
        mov edx, hObject
        push 0
        lea ecx, [esp+0Ch-4]
        push ecx
        push edi
        push esi
        push edx
        call dword ptr [__imp_ReadFile]
        mov eax, esi
        pop esi
        pop ecx
        ret
    }
}
#else
void* File_ReadShared(void* handle, DWORD size,
                      void* (*allocate)(DWORD),
                      DWORD (*read_file)(void*, void*, DWORD),
                      void (*close_file)(void*)) {
    if (handle == (void*)-1 || allocate == 0 || read_file == 0)
        return 0;
    void* buffer = allocate(size);
    if (buffer == 0) {
        if (close_file != 0)
            close_file(handle);
        return 0;
    }
    read_file(handle, buffer, size);
    return buffer;
}
#endif

// 0x00435370 - Open a Win32 file using TH10's fopen-like mode parsing.
#ifdef _MSC_VER
__declspec(naked) BYTE FileHandle_OpenRetail(
        const char* path, const char* mode) {
    __asm {
        sub esp, 10Ch
        mov eax, ___security_cookie
        xor eax, esp
        push ebx
        push ebp
        mov ebp, [esp+118h]
        push esi
        push edi
        mov esi, ecx
        mov [esp+118h], eax
        mov eax, [esi]
        xor edi, edi
        mov [esp+10h], edi
        call dword ptr [eax+4]
        mov eax, [esp+124h]
        mov ebx, eax
        mov al, [eax]
        test al, al
        je after_mode
        jmp mode_loop
        _emit 0x8D
        _emit 0x49
        _emit 0x00
mode_loop:
        cmp al, 72h
        je read_mode
        cmp al, 77h
        je write_mode
        cmp al, 61h
        je append_mode
        mov al, [ebx+1]
        inc ebx
        test al, al
        jne mode_loop
        jmp epilogue
read_mode:
        mov dword ptr [esi+8], 80000000h
        mov edi, 3
        jmp after_mode
write_mode:
        push ebp
        call dword ptr [dword_4660C0]
        mov edi, 2
        jmp set_access
append_mode:
        mov dword ptr [esp+10h], 1
        mov edi, 4
set_access:
        mov dword ptr [esi+8], 40000000h
after_mode:
        cmp byte ptr [ebx], 0
        je fail
        mov eax, ebp
        lea ecx, [esp+14h]
        call sub_435610
        mov ecx, [esi+8]
        push 0
        push 8000080h
        push edi
        push 0
        push 1
        push ecx
        lea edx, [esp+2Ch]
        push edx
        call dword ptr [dword_4660C4]
        cmp eax, 0FFFFFFFFh
        mov [esi+4], eax
        jne after_create
invalid:
fail:
        xor al, al
        jmp epilogue
after_create:
        mov ecx, [esp+10h]
        test ecx, ecx
        je success
        push 2
        push 0
        push 0
        push eax
        call dword ptr [dword_4660C8]
success:
        mov al, 1
epilogue:
        mov ecx, [esp+118h]
        pop edi
        pop esi
        pop ebp
        pop ebx
        xor ecx, esp
        call security_check_cookie
        add esp, 10Ch
        ret 8
    }
}
#else
BYTE FileHandle::Open(const char* path, const char* mode) {
    DWORD creation_disposition = 0;
    bool append = false;
    Close();

    const char* mode_cursor = mode;
    while (*mode_cursor != 0) {
        if (*mode_cursor == 'r') {
            access = kReadAccess;
            creation_disposition = kOpenExisting;
            break;
        }
        if (*mode_cursor == 'w') {
            DeleteFileA(path);
            access = kWriteAccess;
            creation_disposition = kCreateAlways;
            break;
        }
        if (*mode_cursor == 'a') {
            append = true;
            access = kWriteAccess;
            creation_disposition = kOpenAlways;
            break;
        }
        ++mode_cursor;
    }
    if (*mode_cursor == 0) {
        return 0;
    }

    char resolved_path[260];
    File_ResolvePath(path, resolved_path);
    handle = CreateFileA(
        resolved_path,
        access,
        kShareRead,
        0,
        creation_disposition,
        kSequentialNormalFile,
        0);
    if (handle == (HANDLE)-1) {
        return 0;
    }
    if (append) {
        SetFilePointer(handle, 0, 0, kEndPosition);
    }
    return 1;
}
#endif

// 0x00435460 - Close an open Win32 file handle and reset its state.
void FileHandle::Close() {
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        handle = (HANDLE)-1;
        access = 0;
    }
}

// 0x00435490 - Read bytes when the handle was opened for reading.
DWORD FileHandle::Read(void* destination, DWORD size) {
    DWORD bytes_read = 0;
    if (access != kReadAccess) {
        return 0;
    }
    ReadFile(handle, destination, size, &bytes_read, 0);
    return bytes_read;
}

// 0x004354D0 - Write a complete buffer when opened for writing.
BYTE FileHandle::Write(const void* source, DWORD size) {
    DWORD bytes_written = 0;
    if (access != kWriteAccess) {
        return 0;
    }
    WriteFile(handle, source, size, &bytes_written, 0);
    return (BYTE)(size == bytes_written);
}

// 0x00435510 - Return the current Win32 file pointer.
DWORD FileHandle::Tell() const {
    if (handle == (HANDLE)-1) {
        return 0;
    }
    return SetFilePointer(handle, 0, 0, kCurrentPosition);
}

// 0x00435530 - Return the low 32 bits of the file size.
DWORD FileHandle::GetSize() const {
    if (handle == (HANDLE)-1) {
        return 0;
    }
    return GetFileSize(handle, 0);
}

// 0x00435550 - Move the Win32 file pointer.
BYTE FileHandle::Seek(LONG distance, DWORD origin) {
    if (handle == (HANDLE)-1) {
        return 0;
    }
    SetFilePointer(handle, distance, 0, origin);
    return 1;
}

// 0x00435580 - Read an entire readable file without changing its position.
#ifdef _MSC_VER
__declspec(naked) void* FileHandle::ReadWhole(DWORD capacity) {
    __asm {
        push esi
        mov esi, ecx
        cmp dword ptr [esi+8], 80000000h
        je size_ok
        xor eax, eax
        pop esi
        ret 4
size_ok:
        mov eax, [esi]
        push ebp
        mov ecx, esi
        call dword ptr [eax+14h]
        mov ebp, eax
        cmp ebp, [esp+0Ch]
        jbe allocate
        pop ebp
        xor eax, eax
        pop esi
        ret 4
allocate:
        push edi
        push ebp
        call sub_452706
        mov edi, eax
        add esp, 4
        test edi, edi
        jne continue
        pop edi
        pop ebp
        pop esi
        ret 4
continue:
        mov edx, [esi]
        push ebx
        mov ecx, esi
        call dword ptr [edx+10h]
        mov ebx, eax
        mov eax, [esi]
        push 0
        push ebx
        mov ecx, esi
        call dword ptr [eax+18h]
        test al, al
        je fail
        mov edx, [esi]
        push ebp
        push edi
        mov ecx, esi
        call dword ptr [edx+8]
        test eax, eax
        jne success
        push edi
        call sub_452422
        add esp, 4
fail:
        pop ebx
        pop edi
        pop ebp
        xor eax, eax
        pop esi
        ret 4
success:
        mov eax, [esi]
        push 0
        push ebx
        mov ecx, esi
        call dword ptr [eax+18h]
        pop ebx
        mov eax, edi
        pop edi
        pop ebp
        pop esi
        ret 4
    }
}
#else
void* FileHandle::ReadWhole(DWORD capacity) {
    if (access != kReadAccess) {
        return 0;
    }

    DWORD size = GetSize();
    if (size > capacity) {
        return 0;
    }

    void* data = _malloc(size);
    if (!data) {
        return 0;
    }

    DWORD position = Tell();
    if (Seek(0, 0)) {
        if (Read(data, size) == size) {
            goto succeeded;
        }
        _free(data);
    }
    return 0;

succeeded:
    Seek(position, 0);
    return data;
}
#endif
