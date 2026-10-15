#include "../../../build_support/include/asm_encoding.hpp"
#include "../../../build_support/include/asm_symbols.hpp"




// Recovered semantic C++ definitions.
#include "th10/platform/memory_file.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
#ifdef _MSC_VER
extern "C" void* __cdecl memcpy(void* destination, const void* source,
                                DWORD size);
#pragma intrinsic(memcpy)
#endif

#define TH10_BUFFER_DESTRUCTOR_ATTRIBUTES __declspec(noinline)
#include "th10/platform/buffer_file_lifetime.inl"

// This definition makes the virtual lifetime entries available to the compiler.
// The retail constructor uses EAX for this and is still an assembly region;
// this ordinary-thiscall constructor is not selected into the fixed image.
BufferFile::BufferFile() : size_(0), position_(0), data_(0) {}

DWORD BufferFile::Read(void* destination, DWORD requested) {
    DWORD remaining = (DWORD)((data_ + size_) - position_);
    if (remaining >= requested) {
        memcpy(destination, position_, requested);
        position_ += requested;
        return requested;
    }
    if (remaining != 0) {
        memcpy(destination, position_, remaining);
        position_ += remaining;
        return remaining;
    }
    return 0;
}

BYTE BufferFile::Write(const void*, DWORD) {
    return 0;
}

DWORD BufferFile::Tell() const {
    return (DWORD)(position_ - data_);
}

DWORD BufferFile::GetSize() const {
    return size_;
}

// 0x004364F0..0x0043655A: move the read position.  Origin 0 is the start of
// the buffer, 1 the current position and 2 the end (distance <= 0).  A target
// outside the owned bytes fails and leaves the position alone.
//
// Two shapes are load-bearing (recovery_notes/buffer_file_seek_004364f0_wave16.md):
// the start-origin range check is the inline Contains() helper, and the other
// origins leave through one `fail:` label while every origin shares `return 1`.
BYTE BufferFile::Seek(LONG distance, DWORD origin) {
    switch (origin) {
    case 0:
        if (!Contains(distance))
            return 0;
        position_ = data_ + distance;
        break;
    case 1:
        if ((LONG)((data_ + size_) - position_) <= distance)
            goto fail;
        position_ += distance;
        break;
    case 2:
        if (distance > 0)
            goto fail;
        if ((DWORD)(distance < 0 ? -distance : distance) >= size_)
            goto fail;
        position_ = data_ + size_ + distance;
        break;
    default:
        goto fail;
    }
    return 1;
fail:
    return 0;
}
