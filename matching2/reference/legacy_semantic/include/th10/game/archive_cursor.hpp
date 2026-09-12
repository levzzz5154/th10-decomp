// 0x0044DD40 FUN_0044dd40
// Readable reconstruction of retail helper FUN_0044dd40 (a win32
// archive-cursor seek used by the resource loader).  The readable body
// mirrors the retail control flow exactly; the Win32 SetFilePointer
// call is the only OS-dependent edge and resolves to Wine's kernel32
// when the production target runs under wine.
//
// Retail ABI uses two compiler-reserved registers:
//   ESI : the archive context pointer (``cursor`` below)
//   AL  : a boolean flag ("is offset write") carried across the call
// The readable signature reifies both.
//
// Archive context layout (offsets relative to ``cursor``):
//   0x08 : bytes remaining in the current archive section (in/out)
//   0x7c : mode flag (0 = file backed, non-zero = memory backed)
//   0x80 : base pointer of the in-memory mapping
//   0x84 : current read cursor (in-memory branch)
//   0x88 : end-of-section cursor (in-memory branch)
//   0x8c : file HANDLE (file-backed branch)
//   0x90 : pointer to the section descriptor
//        - +0x10 : absolute file offset (base)
//        - +0x18 : data offset within the section (>=0 means "use the
//                  write cursor's current value")
//        - +0x1c : length of the section
//
// Return values match the retail:
//   0           success
//   0x800401f0  file handle missing on a file-backed cursor
//
// The shared archive offset register DAT_004977a4 is declared extern.

#ifndef TH10_GAME_ARCHIVE_CURSOR_SEEK_HPP
#define TH10_GAME_ARCHIVE_CURSOR_SEEK_HPP

#include <cstdint>

// Reposition ``cursor`` so the next read starts at the requested
// offset inside the section descriptor stored at cursor+0x90.  When
// ``offset_write`` is non-zero the request operates on the write
// cursor's offset (section+0x18) instead of the read cursor's start
// (section+0x10).  No-op when cursor == 0.
uint32_t ArchiveCursor_Seek(void* cursor, uint8_t offset_write);

#endif  // TH10_GAME_ARCHIVE_CURSOR_SEEK_HPP
