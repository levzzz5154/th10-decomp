#include "th10/platform/file.hpp"

extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE handle);

// 0x00435460 - Close an open Win32 file handle and reset its state.
void __fastcall FileHandle_Close(FileHandle* file) {
    if (file->handle != (HANDLE)-1) {
        CloseHandle(file->handle);
        file->handle = (HANDLE)-1;
        file->position = 0;
    }
}
