// 0x0044DD40 FUN_0044dd40
// Readable reconstruction of retail helper FUN_0044dd40 (win32
// archive-cursor seek used by the resource loader).  See the header for
// the slot layout and the retail ABI reification.
//
// When the production target is built by `cl.exe` (MSVC under wine via
// build.sh) the Win32 SetFilePointer call resolves against the real
// kernel32 export.  The Linux-side unit tests never enter the
// file-backed branch: they construct cursors whose +0x7c flag is set
// to the in-memory mode and call ArchiveCursor_Seek to exercise the
// memory-buffer branch only.  SetFilePointer is therefore declared
// `extern "C"` with the Win32 __stdcall mangling but is never linked
// into the test binary.

#include "th10/game/archive_cursor.hpp"

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif

#ifdef _MSC_VER
extern "C" void* __imp_SetFilePointer;
#endif

extern "C" {

typedef void* HANDLE;
typedef long* PLONG;

// Win32 kernel32 export; resolved by the linker (Wine's kernel32 on the
// production target, an external stub on the unit-test host).
__stdcall int SetFilePointer(HANDLE hFile, int lDistanceToMove,
                             PLONG lpDistanceToMoveHigh,
                             int dwMoveMethod);

// Global archive header offset declared in retail at 0x004977a4.
extern int32_t DAT_004977a4;

}  // extern "C"


namespace {

struct ArchiveSectionDescriptor {
    int32_t pad_00[4];      // +0x00..+0x0c
    int32_t base_offset;    // +0x10 absolute file offset of the section
    int32_t write_offset;   // +0x18 the write-cursor offset in section
    int32_t section_length; // +0x1c byte length of the section
};

inline ArchiveSectionDescriptor* CursorSection(void* cursor) {
    return *reinterpret_cast<ArchiveSectionDescriptor**>(
        static_cast<uint8_t*>(cursor) + 0x90);
}

}  // namespace


#ifdef _MSC_VER
// 0x0044DD40 - Retail archive-cursor seek. Custom ABI: cursor in ESI,
// write-flag in AL. Advances the in-memory cursor to the section write
// offset, or repositions the file-backed handle through SetFilePointer.
__declspec(naked) uint32_t ArchiveCursor_SeekRetail() {
    __asm {
        push ebx
        mov bl, al
        mov eax, [esi+7Ch]
        test eax, eax
        jz loc_44DD88
        mov edx, [esi+80h]
        mov ecx, [esi+90h]
        mov [esi+84h], edx
        mov eax, [ecx+1Ch]
        test eax, eax
        jle loc_44DD69
        mov [esi+88h], eax
loc_44DD69:
        test bl, bl
        jz loc_44DDFE
        mov ecx, [ecx+18h]
        test ecx, ecx
        jle loc_44DDFE
        add ecx, edx
        mov [esi+84h], ecx
        xor eax, eax
        pop ebx
        ret
loc_44DD88:
        mov edx, [esi+8Ch]
        test edx, edx
        jnz loc_44DD99
        mov eax, 800401F0h
        pop ebx
        ret
loc_44DD99:
        test bl, bl
        jz loc_44DDD6
        mov eax, [esi+90h]
        mov ecx, [eax+18h]
        test ecx, ecx
        jle loc_44DDD6
        mov eax, [eax+10h]
        mov ebx, dword ptr [DAT_004977a4]
        push 0
        add eax, ecx
        push 0
        add eax, ebx
        push eax
        push edx
        call dword ptr [__imp_SetFilePointer]
        mov eax, [esi+90h]
        mov ecx, [eax+1Ch]
        sub ecx, [eax+18h]
        mov [esi+8], ecx
        xor eax, eax
        pop ebx
        ret
loc_44DDD6:
        mov eax, [esi+90h]
        mov ecx, [eax+10h]
        mov eax, dword ptr [DAT_004977a4]
        push 0
        push 0
        add ecx, eax
        push ecx
        push edx
        call dword ptr [__imp_SetFilePointer]
        mov edx, [esi+90h]
        mov eax, [edx+1Ch]
        mov [esi+8], eax
loc_44DDFE:
        xor eax, eax
        pop ebx
        ret
    }
}
#endif

uint32_t ArchiveCursor_Seek(void* cursor, uint8_t offset_write) {
    if (cursor == 0) return 0;
    uint8_t* bytes = static_cast<uint8_t*>(cursor);

    if (*reinterpret_cast<int32_t*>(bytes + 0x7c) == 0) {
        // File-backed branch.
        HANDLE hFile = *reinterpret_cast<HANDLE*>(bytes + 0x8c);
        if (hFile == 0) {
            return 0x800401f0u;
        }
        ArchiveSectionDescriptor* section = CursorSection(cursor);
        if (offset_write != 0) {
            const int32_t write_off = section->write_offset;
            if (write_off > 0) {
                SetFilePointer(
                    hFile,
                    section->base_offset + write_off + DAT_004977a4,
                    0, 0);
                *reinterpret_cast<int32_t*>(bytes + 0x08) =
                    section->section_length - write_off;
                return 0;
            }
        }
        SetFilePointer(
            hFile, section->base_offset + DAT_004977a4, 0, 0);
        *reinterpret_cast<int32_t*>(bytes + 0x08) =
            section->section_length;
        return 0;
    }

    // Memory-backed branch.
    *reinterpret_cast<int32_t*>(bytes + 0x84) =
        *reinterpret_cast<int32_t*>(bytes + 0x80);
    ArchiveSectionDescriptor* section = CursorSection(cursor);
    const int32_t section_length = section->section_length;
    if (section_length > 0) {
        *reinterpret_cast<int32_t*>(bytes + 0x88) = section_length;
    }
    if (offset_write != 0) {
        const int32_t write_off = section->write_offset;
        if (write_off > 0) {
            *reinterpret_cast<int32_t*>(bytes + 0x84) =
                write_off + *reinterpret_cast<int32_t*>(bytes + 0x80);
            return 0;
        }
    }
    return 0;
}
