#include "th10/platform/memory_file.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
#ifdef _MSC_VER
extern "C" void* __cdecl memcpy(void* destination, const void* source,
                                DWORD size);
#pragma intrinsic(memcpy)
#endif

__declspec(noinline) BufferFile::~BufferFile() {
    Close();
}

void BufferFile::Close() {
    if (data_) {
        entry_free_00452422(data_);
        data_ = 0;
    }
    data_ = 0;
    size_ = 0;
    position_ = 0;
}

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
