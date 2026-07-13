#pragma once

#include "th10/platform/file.hpp"

// Buffer-backed file owner used by the vtable at 0x0046F308.
class BufferFile : public FileInterface {
public:
    BufferFile();
    virtual ~BufferFile();

    virtual BYTE Open(const char* path, const char* mode);
    virtual void Close();
    virtual DWORD Read(void* destination, DWORD size);
    virtual BYTE Write(const void* source, DWORD size);
    virtual DWORD Tell() const;
    virtual DWORD GetSize() const;
    virtual BYTE Seek(LONG distance, DWORD origin);

protected:
    DWORD size_;
    BYTE* position_;
    BYTE* data_;
};

// Embedded Win32 RCDATA backend used by the vtable at 0x0046F328.
class ResourceFile : public BufferFile {
public:
    ResourceFile();
    virtual ~ResourceFile();

    virtual BYTE Open(const char* resource_name, const char* mode);
};
