#pragma once

#include "th10/platform/windows_types.hpp"

// Retail vtable at 0x0046F230. Keeping this typed preserves the polymorphic
// calls used by archive readers while documenting every slot.
class FileInterface {
public:
    FileInterface() {}

    virtual BYTE Open(const char* path, const char* mode) = 0;
    virtual void Close() = 0;
    virtual DWORD Read(void* destination, DWORD size) = 0;
    virtual BYTE Write(const void* source, DWORD size) = 0;
    virtual DWORD Tell() const = 0;
    virtual DWORD GetSize() const = 0;
    virtual BYTE Seek(LONG distance, DWORD origin) = 0;
    virtual ~FileInterface() {}
};

// Win32-backed file owner used by the archive/file subsystem.
class FileHandle : public FileInterface {
public:
    FileHandle();
    ~FileHandle();

    HANDLE handle;
    DWORD access;

    virtual BYTE Open(const char* path, const char* mode);
    virtual void Close();
    virtual DWORD Read(void* destination, DWORD size);
    virtual BYTE Write(const void* source, DWORD size);
    virtual DWORD Tell() const;
    virtual DWORD GetSize() const;
    virtual BYTE Seek(LONG distance, DWORD origin);
    void* ReadWhole(DWORD capacity);
};

void File_ResolvePath(const char* path, char output[260]);
const char* File_AfterFirstSlash(const char* path);
