#pragma once

#include "th10/platform/windows_types.hpp"

// Partial Win32-backed file owner used by the archive/file subsystem.
struct FileHandle {
    void* vtable;
    HANDLE handle;
    DWORD position;
};

void __fastcall FileHandle_Close(FileHandle* file);
