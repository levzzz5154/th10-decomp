#pragma once

#include "th10/platform/windows_types.hpp"

// Partial Win32-backed file owner used by the archive/file subsystem.
struct FileHandle {
    void* vtable;
    HANDLE handle;
    DWORD access;

    DWORD Read(void* destination, DWORD size);
    BYTE Write(const void* source, DWORD size);
    DWORD Tell() const;
    DWORD GetSize() const;
    bool Seek(LONG distance, DWORD origin);
};

void __fastcall FileHandle_Close(FileHandle* file);
