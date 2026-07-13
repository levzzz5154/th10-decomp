#include "th10/platform/memory_file.hpp"
#include "th10/archive/resource_manager.hpp"

extern "C" void* __cdecl _malloc(DWORD size);
extern "C" void __cdecl _free(void* memory);
#ifdef _MSC_VER
extern "C" void* __cdecl memcpy(
    void* destination, const void* source, DWORD size);
#pragma intrinsic(memcpy)
#else
extern "C" void* memcpy(
    void* destination, const void* source, unsigned long size);
#endif

BufferFile::BufferFile() : size_(0), position_(0), data_(0) {
}

// 0x004363C0 - Release the owned byte buffer and restore the base vtable.
__declspec(noinline) BufferFile::~BufferFile() {
    Close();
}

// 0x00436400 - Resolve a path through the registered archive/file manager.
BYTE BufferFile::Open(const char* path, const char*) {
    Close();
    data_ = Resource_LoadFile(path, 0);
    size_ = Resource_GetFileSize(path);
    position_ = data_;
    return (BYTE)(data_ != 0);
}

// 0x00436430 - Release and reset a buffer-backed file.
void BufferFile::Close() {
    if (data_) {
        _free(data_);
        data_ = 0;
    }
    data_ = 0;
    size_ = 0;
    position_ = 0;
}

// 0x00436460 - Read up to the remaining byte count.
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

// 0x00436370 - Buffer files are read-only.
BYTE BufferFile::Write(const void*, DWORD) {
    return 0;
}

// 0x004364D0
DWORD BufferFile::Tell() const {
    return (DWORD)(position_ - data_);
}

// 0x004364E0
DWORD BufferFile::GetSize() const {
    return size_;
}

// 0x004364F0 - Retail seek rules use strict end bounds.
BYTE BufferFile::Seek(LONG distance, DWORD origin) {
    switch (origin) {
    case 0:
        goto from_start;
    case 1: {
        DWORD remaining = (DWORD)((data_ + size_) - position_);
        if ((LONG)remaining <= distance) goto failed;
        position_ += distance;
        return 1;
    }
    case 2: {
        if (distance > 0) goto failed;
        DWORD magnitude = distance < 0 ? (DWORD)-distance : (DWORD)distance;
        if (magnitude >= size_) goto failed;
        position_ = data_ + size_ + distance;
        return 1;
    }
    default:
        goto failed;
    }

failed:
    return 0;

from_start:
    if (distance < 0 || (DWORD)distance >= size_) goto failed;
    position_ = data_ + distance;
    return 1;
}
