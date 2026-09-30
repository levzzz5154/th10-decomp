// Semantic candidates for resource Load (0x00435800, 214 bytes) and GetFileSize
// (0x004358E0, 190 bytes). Retail takes the path itself in ECX. Load also takes
// one output-buffer stack argument. These ordinary stdcall interfaces expose
// those inputs while native MSVC entry/frame matching remains outstanding.
#include "dat_archive_types.hpp"

extern "C" DatArchive* __fastcall Resource_FindArchive_004356f0(const char* path);
extern "C" char* __cdecl FirstByteSearch_00452730(const char* text, int character);
extern "C" unsigned char* __stdcall DatArchive_Read_00434dd0(
    DatArchive* archive, const char* name, unsigned char* output);
extern "C" unsigned int __stdcall DatArchive_FindSize_00434ef0(DatArchive* archive, const char* name);
extern "C" const char* g_dat_archive_read_mode;
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE handle);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileSize(HANDLE handle, LPDWORD high_size);

// Standalone compiler context, matching the maintained definitions in
// platform/file.cpp. The stack owner supplies normal and exceptional cleanup.
FileHandle::FileHandle() : handle((HANDLE)-1), access(0) {}
FileHandle::~FileHandle() { Close(); }
void FileHandle::Close() {
    if (handle != (HANDLE)-1) {
        CloseHandle(handle);
        handle = (HANDLE)-1;
        access = 0;
    }
}
DWORD FileHandle::GetSize() const {
    if (handle == (HANDLE)-1)
        return 0;
    return GetFileSize(handle, 0);
}

extern "C" unsigned char* __stdcall Resource_LoadFile_00435800(
        const char* path, unsigned char* output) {
    DatArchive* archive = Resource_FindArchive_004356f0(path);
    if (archive) {
        const char* slash = FirstByteSearch_00452730(path, '/');
        return DatArchive_Read_00434dd0(archive, slash ? slash + 1 : path, output);
    }

    FileHandle file;
    file.Open(path, g_dat_archive_read_mode);
    // Open's result is ignored. The current handle controls size/cleanup,
    // and the disk path always asks ReadWhole for a new allocation.
    return static_cast<unsigned char*>(file.ReadWhole(file.GetSize()));
}

extern "C" unsigned int __stdcall Resource_GetFileSize_004358e0(const char* path) {
    DatArchive* archive = Resource_FindArchive_004356f0(path);
    if (archive) {
        const char* slash = FirstByteSearch_00452730(path, '/');
        return DatArchive_FindSize_00434ef0(archive, slash ? slash + 1 : path);
    }

    FileHandle file;
    file.Open(path, g_dat_archive_read_mode);
    return file.GetSize();
}
