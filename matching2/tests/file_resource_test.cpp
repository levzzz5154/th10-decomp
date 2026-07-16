#include "th10/platform/file.hpp"
#include "th10/archive/dat.hpp"
#include "th10/archive/resource_manager.hpp"

extern "C" void* malloc(unsigned long size);
extern "C" void free(void* memory);

namespace {

struct MockFile {
    const unsigned char* bytes;
    DWORD size;
    DWORD position;
    bool open;
    bool short_read;
    DWORD close_count;
};

MockFile g_file = {};

void ResetMock(const unsigned char* bytes, DWORD size) {
    g_file.bytes = bytes;
    g_file.size = size;
    g_file.position = 0;
    g_file.open = true;
    g_file.short_read = false;
    g_file.close_count = 0;
}

bool TestReadWholeRestoresPosition() {
    static const unsigned char bytes[] = {1, 2, 3, 4};
    ResetMock(bytes, sizeof(bytes));
    g_file.position = 2;

    FileHandle file;
    file.handle = (HANDLE)&g_file;
    file.access = 0x80000000;
    unsigned char* result = (unsigned char*)file.ReadWhole(sizeof(bytes));
    bool passed = result != 0 && g_file.position == 2;
    for (DWORD index = 0; passed && index < sizeof(bytes); ++index) {
        if (result[index] != bytes[index]) passed = false;
    }
    free(result);
    return passed;
}

bool TestReadWholeFailureLeavesReadPosition() {
    static const unsigned char bytes[] = {5, 6, 7, 8};
    ResetMock(bytes, sizeof(bytes));
    g_file.position = 1;
    g_file.short_read = true;

    FileHandle file;
    file.handle = (HANDLE)&g_file;
    file.access = 0x80000000;
    return file.ReadWhole(sizeof(bytes)) == 0 && g_file.position == sizeof(bytes);
}

bool TestReadWholeRejectsCapacityAndWriteHandle() {
    static const unsigned char bytes[] = {9, 10};
    ResetMock(bytes, sizeof(bytes));
    FileHandle file;
    file.handle = (HANDLE)&g_file;
    file.access = 0x80000000;
    if (file.ReadWhole(sizeof(bytes) - 1) != 0 || g_file.position != 0) {
        return false;
    }
    file.access = 0x40000000;
    return file.ReadWhole(sizeof(bytes)) == 0 && g_file.position == 0;
}

bool TestResourceFallbackOpenFailure() {
    g_file.close_count = 0;
    g_file.open = false;
    return Resource_LoadFile("missing.bin", 0) == 0 &&
        Resource_GetFileSize("missing.bin") == 0 &&
        g_file.close_count == 0;
}

} // namespace

extern "C" BOOL __stdcall CloseHandle(HANDLE handle) {
    MockFile* file = (MockFile*)handle;
    ++file->close_count;
    file->open = false;
    return 1;
}

extern "C" BOOL __stdcall ReadFile(
        HANDLE handle, void* buffer, DWORD size, DWORD* bytes_read, void*) {
    MockFile* file = (MockFile*)handle;
    DWORD available = file->size - file->position;
    DWORD count = size < available ? size : available;
    for (DWORD index = 0; index < count; ++index) {
        ((unsigned char*)buffer)[index] = file->bytes[file->position + index];
    }
    file->position += count;
    *bytes_read = file->short_read && count ? count - 1 : count;
    return 1;
}

extern "C" BOOL __stdcall WriteFile(
        HANDLE, const void*, DWORD, DWORD* bytes_written, void*) {
    *bytes_written = 0;
    return 0;
}

extern "C" DWORD __stdcall SetFilePointer(
        HANDLE handle, LONG distance, LONG*, DWORD origin) {
    MockFile* file = (MockFile*)handle;
    LONG base = origin == 0 ? 0 : origin == 1 ? (LONG)file->position :
        (LONG)file->size;
    file->position = (DWORD)(base + distance);
    return file->position;
}

extern "C" DWORD __stdcall GetFileSize(HANDLE handle, DWORD*) {
    return ((MockFile*)handle)->size;
}

extern "C" HANDLE __stdcall CreateFileA(
        const char*, DWORD, DWORD, void*, DWORD, DWORD, HANDLE) {
    return (HANDLE)-1;
}

extern "C" BOOL __stdcall DeleteFileA(const char*) { return 1; }

extern "C" DWORD __stdcall GetModuleFileNameA(HANDLE, char*, DWORD) {
    return 0;
}

extern "C" void* __cdecl _malloc(DWORD size) { return malloc(size); }
extern "C" void __cdecl _free(void* memory) { free(memory); }

void DatArchive_Initialize(DatArchive*) {}
void DatArchive_Close(DatArchive*) {}
bool DatArchive_OpenFile(DatArchive*, const char*) { return false; }
uint8_t* DatArchive_Read(DatArchive*, const char*, uint8_t*) { return 0; }
uint32_t DatArchive_FindSize(const DatArchiveIndex*, const char*) { return 0; }

int main() {
    if (!TestReadWholeRestoresPosition()) return 1;
    if (!TestReadWholeFailureLeavesReadPosition()) return 2;
    if (!TestReadWholeRejectsCapacityAndWriteHandle()) return 3;
    if (!TestResourceFallbackOpenFailure()) return 4;
    return 0;
}
