// 0x0044DE10 FUN_0044de10
// Readable reconstruction of retail helper FUN_0044de10 (archive-cursor
// read).  See the header for the cursor slot layout and the retail ABI
// reification.

#include "th10/game/archive_cursor_read.hpp"

#include <cstdint>
#include <cstring>

extern "C" {

typedef void* HANDLE;
typedef uint32_t* LPDWORD;

// Win32 kernel32 export.  Resolved against Wine's kernel32 on the
// production target; declared extern so the Linux-side test fixture can
// override the symbol at link time.
__stdcall int ReadFile(HANDLE hFile, void* lpBuffer, uint32_t nNumberOfBytesToRead,
                       LPDWORD lpNumberOfBytesRead, void* lpOverlapped);

}  // extern "C"


uint32_t ArchiveCursor_Read(void* cursor, uint32_t byte_count,
                            void* destination,
                            uint32_t* out_bytes_read) {
    if (cursor == 0) return 0x800401f0u;
    uint8_t* bytes = static_cast<uint8_t*>(cursor);

    if (*reinterpret_cast<int32_t*>(bytes + 0x7c) == 0) {
        // File-backed branch.
        HANDLE hFile = *reinterpret_cast<HANDLE*>(bytes + 0x8c);
        if (hFile == 0) {
            return 0x800401f0u;
        }
        if (destination == 0 || out_bytes_read == 0) {
            return 0x80070057u;
        }
        const uint32_t remaining = *reinterpret_cast<uint32_t*>(bytes + 0x08);
        if (byte_count > remaining) {
            byte_count = remaining;
        }
        *reinterpret_cast<uint32_t*>(bytes + 0x08) = remaining - byte_count;
        ReadFile(hFile, destination, byte_count,
                 reinterpret_cast<LPDWORD>(&destination),
                 0);
        *out_bytes_read = static_cast<uint32_t>(
            reinterpret_cast<uintptr_t>(destination));
        return 0;
    }

    // Memory-backed branch.
    if (*reinterpret_cast<int32_t*>(bytes + 0x84) == 0) {
        return 0x800401f0u;
    }
    if (out_bytes_read != 0) {
        *out_bytes_read = 0;
    }
    if (destination == 0 || out_bytes_read == 0) {
        return 0x80070057u;
    }
    const uint8_t* cursor_ptr =
        *reinterpret_cast<uint8_t**>(bytes + 0x84);
    const uint8_t* base_ptr =
        *reinterpret_cast<uint8_t**>(bytes + 0x80);
    const int32_t end_offset =
        *reinterpret_cast<int32_t*>(bytes + 0x88);
    // The retail computes the bound as 32-bit integer arithmetic:
    //   limit = (int)base + end_offset
    //   if (limit < (int)cursor + byte_count)
    //       byte_count = (int)base - (int)cursor + end_offset;
    // On a 64-bit host the in-buffer pointer remains valid as long as
    // the cursor+count fits inside the buffer of end_offset bytes
    // starting at base.
    const uintptr_t base_addr =
        reinterpret_cast<uintptr_t>(base_ptr);
    const uintptr_t cursor_addr =
        reinterpret_cast<uintptr_t>(cursor_ptr);
    const uintptr_t limit_addr = base_addr + end_offset;
    if (limit_addr < cursor_addr + byte_count) {
        byte_count = static_cast<uint32_t>(limit_addr - cursor_addr);
    }
    // Word-wise copy then byte tail, exactly as the retail unrolled it.
    uint8_t* out = static_cast<uint8_t*>(destination);
    const uint8_t* in = cursor_ptr;
    // Note: *cursor_ptr is a single malloc'd buffer of at least
    // ``byte_count`` bytes, so the dword pointer cast below is
    // well-aligned (4-byte aligned within a malloc'd region).
    for (uint32_t words = byte_count >> 2; words != 0; --words) {
        std::memcpy(out, in, 4);
        out += 4;
        in += 4;
    }
    for (uint32_t tail = byte_count & 3; tail != 0; --tail) {
        *out++ = *in++;
    }
    *reinterpret_cast<uint8_t**>(bytes + 0x84) =
        const_cast<uint8_t*>(in);
    if (out_bytes_read != 0) {
        *out_bytes_read = byte_count;
    }
    return 0;
}