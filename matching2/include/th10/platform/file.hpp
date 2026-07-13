#pragma once

#include "th10/platform/windows_types.hpp"

// Partial Win32-backed file owner used by the archive/file subsystem.
struct FileHandle {
    void* vtable;
    HANDLE handle;
    DWORD access;
};

void __fastcall FileHandle_Close(FileHandle* file);
DWORD FileHandle_Read(FileHandle* file, void* destination, DWORD size);
bool FileHandle_Write(FileHandle* file, const void* source, DWORD size);
DWORD FileHandle_Tell(const FileHandle* file);
DWORD FileHandle_GetSize(const FileHandle* file);
bool FileHandle_Seek(FileHandle* file, LONG distance, DWORD origin);
