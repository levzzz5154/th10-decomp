// Test for the FUN_0044dd40 reconstruction (ArchiveCursor_Seek).
//
// The test exercises the in-memory branch (cursor +0x7c != 0) which is
// the only one reachable on a Linux-host g++ build: the file-backed
// branch invokes the Win32 kernel32 `SetFilePointer` symbol, which is
// not present on the Linux unit-test host.  The stub below catches any
// accidental invocation of that symbol during a unit-test run by
// asserting.

#include "th10/game/archive_cursor.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>


// Stub for the Win32 SetFilePointer reference.  The production build
// (cl.exe under wine via build.sh) overrides this with the real
// kernel32 export.
extern "C" {

typedef void* HANDLE;
typedef long* PLONG;

int SetFilePointer(HANDLE, int, PLONG, int) {
    assert(false && "SetFilePointer must not run in the unit test");
    return 0;
}

int32_t DAT_004977a4 = 0;

}  // extern "C"


namespace {

struct ArchiveSectionDescriptor {
    int32_t pad_00[4];      // +0x00..+0x0c
    int32_t base_offset;    // +0x10
    int32_t write_offset;   // +0x18
    int32_t section_length; // +0x1c
};

static ArchiveSectionDescriptor MakeSection() {
    ArchiveSectionDescriptor s;
    std::memset(&s, 0, sizeof(s));
    return s;
}

// The cursor fixture mirrors the retail byte layout.  On a 64-bit host
// the test only exercises the in-memory branch; the bytes_remaining
// slot is mis-aligned because the test's pad bytes target the retail
// 32-bit ABI.  Insert explicit offsets via a union so the field
// accesses stay byte-accurate.
struct ArchiveCursor {
    uint8_t bytes[0x98];

    int32_t& bytes_remaining() {
        return *reinterpret_cast<int32_t*>(bytes + 0x08);
    }
    int32_t& mode_flag() {
        return *reinterpret_cast<int32_t*>(bytes + 0x7c);
    }
    int32_t& mem_base() {
        return *reinterpret_cast<int32_t*>(bytes + 0x80);
    }
    int32_t& mem_cursor() {
        return *reinterpret_cast<int32_t*>(bytes + 0x84);
    }
    int32_t& mem_end() {
        return *reinterpret_cast<int32_t*>(bytes + 0x88);
    }
    void*& file_handle() {
        return *reinterpret_cast<void**>(bytes + 0x8c);
    }
    ArchiveSectionDescriptor*& section() {
        return *reinterpret_cast<ArchiveSectionDescriptor**>(bytes + 0x90);
    }
};

}  // namespace


static void TestNullCursorIsNoOp() {
    assert(ArchiveCursor_Seek(0, 0) == 0);
    assert(ArchiveCursor_Seek(0, 1) == 0);
}

static void TestMemModeSetCurrentCursorFromBase() {
    ArchiveCursor cursor;
    std::memset(&cursor, 0, sizeof(cursor));
    ArchiveSectionDescriptor section = MakeSection();

    cursor.mode_flag() = 1;       // memory backed
    cursor.mem_base() = 1000;
    cursor.mem_cursor() = 0;
    cursor.mem_end() = 0;
    cursor.section() = &section;
    section.section_length = 200;

    assert(ArchiveCursor_Seek(&cursor, 0) == 0);
    // mem_cursor <- mem_base; mem_end <- section_length (because > 0).
    assert(cursor.mem_cursor() == 1000);
    assert(cursor.mem_end() == 200);
}

static void TestMemModeOffsetWriteAdvancesCursorPastBase() {
    ArchiveCursor cursor;
    std::memset(&cursor, 0, sizeof(cursor));
    ArchiveSectionDescriptor section = MakeSection();

    cursor.mode_flag() = 1;
    cursor.mem_base() = 1000;
    cursor.section() = &section;
    section.write_offset = 150;
    section.section_length = 1000;  // > 0: sets mem_end

    assert(ArchiveCursor_Seek(&cursor, /*offset_write=*/1) == 0);
    // mem_cursor <- write_offset + mem_base (= 1150)
    // mem_end <- section_length (= 1000) because length > 0
    assert(cursor.mem_cursor() == 1150);
    assert(cursor.mem_end() == 1000);
}

static void TestMemModeZeroWriteOffsetFallsThroughPlainSet() {
    ArchiveCursor cursor;
    std::memset(&cursor, 0, sizeof(cursor));
    ArchiveSectionDescriptor section = MakeSection();

    cursor.mode_flag() = 1;
    cursor.mem_base() = 50;
    cursor.section() = &section;
    section.write_offset = 0;          // not > 0
    section.section_length = 0;

    assert(ArchiveCursor_Seek(&cursor, /*offset_write=*/1) == 0);
    assert(cursor.mem_cursor() == 50);     // plain set from mem_base
    assert(cursor.mem_end() == 0);         // not updated because section_length <= 0
}

static void TestFileModeNullHandleReturnsNotFound() {
    // File-backed branch with a missing file handle.  The retail layout
    // is 32-bit: file_handle is 4 bytes at +0x8c, section is 4 bytes at
    // +0x90.  On a 64-bit host the 8-byte void* file_handle slot would
    // alias with the 8-byte section-pointer slot, so we do not write
    // both — only set the mode flag and leave the handle at zero (the
    // fixture is zero-initialised).  This matches the retail semantics
    // where the function returns 0x800401f0 before dereferencing the
    // section pointer.
    ArchiveCursor cursor;
    std::memset(&cursor, 0, sizeof(cursor));
    cursor.mode_flag() = 0;
    assert(ArchiveCursor_Seek(&cursor, 0) == 0x800401f0u);
}

int main() {
    TestNullCursorIsNoOp();
    TestMemModeSetCurrentCursorFromBase();
    TestMemModeOffsetWriteAdvancesCursorPastBase();
    TestMemModeZeroWriteOffsetFallsThroughPlainSet();
    TestFileModeNullHandleReturnsNotFound();
    return 0;
}