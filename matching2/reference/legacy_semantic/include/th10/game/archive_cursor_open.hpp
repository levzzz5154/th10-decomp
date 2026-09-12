// 0x0044DBF0 FUN_0044dbf0
// Readable reconstruction of retail helper FUN_0044dbf0 (win32
// archive-cursor open). The helper stores the requested access mode,
// forces the cursor into file-backed operation, opens the archive file
// for sequential read, attaches the section descriptor, and performs
// the initial seek to the section's base offset.
//
// Retail ABI uses two compiler-reserved registers:
//   EAX : the access mode (1 = open for reading)
//   ESI : the archive cursor pointer (``cursor`` below)
// The readable signature reifies both.
//
// Cursor slot layout (offsets relative to ``cursor``, shared with
// ArchiveCursor_Seek and ArchiveCursor_Read):
//   0x08 : bytes remaining in the current archive section (out)
//   0x2c : cached copy of the initial bytes-remaining value (out)
//   0x78 : stored access mode (out)
//   0x7c : mode flag (0 = file backed, non-zero = memory backed); the
//          open path always clears it
//   0x8c : file HANDLE (out, file-backed branch)
//   0x90 : pointer to the section descriptor
//        - +0x10 : absolute file offset (base)
//        - +0x1c : length of the section
//
// Return values match the retail:
//   0           success (also returned for modes other than 1, which
//               only record the mode)
//   0x80070057  null path on an open-for-read request
//   0x80004005  CreateFileA returned INVALID_HANDLE_VALUE
//
// The shared archive offset register DAT_004977a4 is declared extern.

#ifndef TH10_GAME_ARCHIVE_CURSOR_OPEN_HPP
#define TH10_GAME_ARCHIVE_CURSOR_OPEN_HPP

#include <cstdint>

// Open ``path`` on ``cursor`` for the requested ``mode`` and seek to the
// base of ``section``. Only mode 1 (read) performs any file work; other
// modes are recorded and succeed immediately.
uint32_t ArchiveCursor_Open(void* cursor, int32_t mode, const char* path,
                            void* section);

#endif  // TH10_GAME_ARCHIVE_CURSOR_OPEN_HPP
