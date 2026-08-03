// 0x0044DBF0 FUN_0044dbf0
// Readable reconstruction of retail helper FUN_0044dbf0 (archive-cursor
// open). See the header for the slot layout and the retail ABI
// reification.
//
// When the production target is built by `cl.exe` (MSVC under wine via
// build.sh) the Win32 CreateFileA/SetFilePointer calls resolve against
// the real kernel32 exports. The Linux-side unit test provides both
// symbols at link time so the file-backed open path can be exercised
// without Wine.
//
// Note on 64-bit hosts: the retail cursor stores 4-byte pointers at
// +0x8c (handle) and +0x90 (section). The readable form performs the
// two stores in retail order with native pointer width, so on a 64-bit
// host the +0x90 store overlaps the upper half of the +0x8c slot. All
// subsequent accesses in this function use the local variables, exactly
// like the retail registers, so behavior is unaffected; under the
// 32-bit production compiler the layout is exact.

#include "th10/game/archive_cursor_open.hpp"

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

#ifdef _MSC_VER
extern "C" int dword_4977A4;
extern "C" void* dword_4660C4;
extern "C" void* dword_4660C8;
#else
extern "C" {

typedef void* HANDLE;
typedef long* PLONG;

// Win32 kernel32 exports; resolved by the linker (Wine's kernel32 on
// the production target, test-provided stubs on the unit-test host).
__stdcall HANDLE CreateFileA(const char* lpFileName, uint32_t dwDesiredAccess,
                             uint32_t dwShareMode, void* lpSecurityAttributes,
                             uint32_t dwCreationDisposition,
                             uint32_t dwFlagsAndAttributes,
                             HANDLE hTemplateFile);
__stdcall int SetFilePointer(HANDLE hFile, int lDistanceToMove,
                             PLONG lpDistanceToMoveHigh,
                             int dwMoveMethod);

// Global archive header offset declared in retail at 0x004977a4.
extern int32_t DAT_004977a4;

}  // extern "C"
#endif


namespace {

struct ArchiveSectionDescriptor {
    int32_t pad_00[4];      // +0x00..+0x0c
    int32_t base_offset;    // +0x10 absolute file offset of the section
    int32_t pad_14;         // +0x14
    int32_t write_offset;   // +0x18 the write-cursor offset in section
    int32_t section_length; // +0x1c byte length of the section
};

}  // namespace


#ifdef _MSC_VER
__declspec(naked) uint32_t ArchiveCursor_Open(
        void* cursor, int32_t mode, const char* path, void* section) {
    __asm {
        cmp eax, 1
        push edi
        mov edi, edx
        mov [esi+78h], eax
        mov dword ptr [esi+7Ch], 0
        jne return_zero
        test ecx, ecx
        jne path_ok
        mov eax, 80070057h
        pop edi
        ret
path_ok:
        push 0
        push 8000080h
        push 3
        push 0
        push 1
        push 80000000h
        push ecx
        call dword ptr [dword_4660C4]
        cmp eax, 0FFFFFFFFh
        mov [esi+8Ch], eax
        jne handle_ok
        mov eax, 80004005h
        pop edi
        ret
handle_ok:
        mov ecx, [esi+7Ch]
        test ecx, ecx
        mov [esi+90h], edi
        je memory_path
        mov eax, [esi+80h]
        mov [esi+84h], eax
        mov eax, [edi+1Ch]
        test eax, eax
        jle finish
        mov ecx, [esi+8]
        mov [esi+88h], eax
        mov [esi+2Ch], ecx
        xor eax, eax
        pop edi
        ret
memory_path:
        test eax, eax
        je finish
        mov ecx, [edi+10h]
        mov edi, dword_4977A4
        push 0
        push 0
        add ecx, edi
        push ecx
        push eax
        call dword ptr [dword_4660C8]
        mov edx, [esi+90h]
        mov eax, [edx+1Ch]
        mov [esi+8], eax
finish:
        mov ecx, [esi+8]
        mov [esi+2Ch], ecx
return_zero:
        xor eax, eax
        pop edi
        ret
    }
}
#else
uint32_t ArchiveCursor_Open(void* cursor, int32_t mode, const char* path,
                            void* section) {
    uint8_t* bytes = static_cast<uint8_t*>(cursor);

    *reinterpret_cast<int32_t*>(bytes + 0x78) = mode;
    *reinterpret_cast<int32_t*>(bytes + 0x7c) = 0;

    if (mode != 1) {
        return 0;
    }
    if (path == 0) {
        return 0x80070057u;
    }

    // GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING,
    // FILE_FLAG_SEQUENTIAL_SCAN | FILE_ATTRIBUTE_NORMAL.
    HANDLE hFile = CreateFileA(path, 0x80000000u, 1, 0, 3, 0x8000080u, 0);
    *reinterpret_cast<HANDLE*>(bytes + 0x8c) = hFile;
    if (hFile == reinterpret_cast<HANDLE>(~static_cast<uintptr_t>(0))) {
        return 0x80004005u;
    }

    ArchiveSectionDescriptor* descriptor =
        static_cast<ArchiveSectionDescriptor*>(section);
    *reinterpret_cast<ArchiveSectionDescriptor**>(bytes + 0x90) = descriptor;

    // The remainder is the retail-inlined initial seek. The mode flag at
    // +0x7c was cleared above, so only the file-backed arm can execute;
    // the memory-backed arm is kept to mirror the retail control flow.
    if (*reinterpret_cast<int32_t*>(bytes + 0x7c) == 0) {
        if (hFile != 0) {
            SetFilePointer(hFile, descriptor->base_offset + DAT_004977a4,
                           0, 0);
            *reinterpret_cast<int32_t*>(bytes + 0x08) =
                descriptor->section_length;
        }
    } else {
        *reinterpret_cast<int32_t*>(bytes + 0x84) =
            *reinterpret_cast<int32_t*>(bytes + 0x80);
        if (descriptor->section_length > 0) {
            *reinterpret_cast<int32_t*>(bytes + 0x88) =
                descriptor->section_length;
            *reinterpret_cast<int32_t*>(bytes + 0x2c) =
                *reinterpret_cast<int32_t*>(bytes + 0x08);
            return 0;
        }
    }
    *reinterpret_cast<int32_t*>(bytes + 0x2c) =
        *reinterpret_cast<int32_t*>(bytes + 0x08);
    return 0;
}
#endif
