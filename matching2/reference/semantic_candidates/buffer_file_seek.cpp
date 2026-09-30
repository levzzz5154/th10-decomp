// Behavioral candidate for BufferFile::Seek (0x004364F0, 107 bytes).
// The existing thiscall method expresses the retail entry/RET 8 contract.
// Earlier MSVC attempts differed in branch-tail ownership; this candidate
// also makes the retail 32-bit arithmetic explicit without signed overflow.
#include "th10/platform/memory_file.hpp"

BYTE BufferFile::Seek(LONG distance, DWORD origin) {
    const DWORD offset = static_cast<DWORD>(distance);
    DWORD base;
    switch (origin) {
    case 0:
        if (distance < 0 || offset >= size_)
            return 0;
        base = reinterpret_cast<DWORD>(data_);
        break;
    case 1: {
        base = reinterpret_cast<DWORD>(position_);
        const DWORD remaining = reinterpret_cast<DWORD>(data_) + size_ - base;
        // There is no lower-bound check: negative distances can seek before
        // the buffer, and the remaining count is compared as signed 32-bit.
        if (static_cast<LONG>(remaining) <= distance)
            return 0;
        break;
    }
    case 2:
        // Unsigned negation also preserves the INT_MIN magnitude, 0x80000000.
        if (distance > 0 || DWORD(0) - offset >= size_)
            return 0;
        base = reinterpret_cast<DWORD>(data_) + size_;
        break;
    default:
        return 0;
    }
    position_ = reinterpret_cast<BYTE*>(base + offset);
    return 1;
}
