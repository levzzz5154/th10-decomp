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

#include <cstdint>

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