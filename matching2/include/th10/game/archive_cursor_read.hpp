// 0x0044DE10 FUN_0044de10
// Readable reconstruction of retail helper FUN_0044de10 (archive-cursor
// read).  The readable body mirrors the retail control flow exactly;
// the Win32 ReadFile call resolves to Wine's kernel32 when the
// production target runs under wine.
//
// Retail ABI uses the preserved-EAX register as the cursor pointer;
// the readable signature reifies it.  The fourth parameter is an
// ``out_size`` destination DWORD pointer.
//
// Cursor layout (offsets relative to ``cursor``):
//   0x08 : bytes remaining (decremented by the read length)
//   0x7c : mode flag (0 = file backed, non-zero = memory backed)
//   0x80 : base pointer of the in-memory mapping
//   0x84 : current read cursor (in-memory branch)
//   0x88 : end-of-section cursor (in-memory branch)
//   0x8c : file HANDLE (file-backed branch)
//
// Return values match the retail:
//   0           success
//   0x800401f0  file handle missing on a file-backed cursor (no file)
//   0x80070057  E_INVALIDARG (3rd or 4th parameter was null)

#ifndef TH10_GAME_ARCHIVE_CURSOR_READ_HPP
#define TH10_GAME_ARCHIVE_CURSOR_READ_HPP

#include <cstdint>

// Read up to ``byte_count`` bytes from ``cursor`` into ``destination``.
// On success the actual transfer size is stored at ``*out_bytes_read``.
// Safe to call with cursor == 0 (returns 0x800401f0).
uint32_t ArchiveCursor_Read(void* cursor, uint32_t byte_count,
                            void* destination,
                            uint32_t* out_bytes_read);

#endif  // TH10_GAME_ARCHIVE_CURSOR_READ_HPP