// 0x0044B360: load a named file either from the packed archive index or from disk.
#include "archive.hpp"

extern "C" DatArchive g_archive;
extern "C" unsigned char g_file_lock_depth;
extern "C" unsigned char g_file_lock[];

extern "C" void (__stdcall *imp_EnterCriticalSection)(void*);
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);
extern "C" void* (__stdcall *imp_CreateFileA)(const char*, unsigned int, unsigned int, void*,
                                            unsigned int, unsigned int, void*);
extern "C" int (__stdcall *imp_CloseHandle)(void*);
extern "C" int (__stdcall *imp_ReadFile)(void*, void*, unsigned int, unsigned int*, void*);
extern "C" unsigned int (__stdcall *imp_GetFileSize)(void*, unsigned int*);

extern "C" char* __cdecl asm_strrchr_00452930(const char*, int);
extern "C" int __cdecl asm_stricmp_0046054e(const char*, const char*);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int);

#ifndef ARCHIVE_LOAD_SECTION
#define ARCHIVE_LOAD_SECTION ".text$a06load"
#endif
#pragma code_seg(ARCHIVE_LOAD_SECTION)
extern "C" __declspec(noinline) char* __stdcall Archive_LoadFile(const char* name, int* outSize,
                                                                 int fromDisk) {
    char* buffer;
    unsigned int size;
    imp_EnterCriticalSection(g_file_lock);
    ++g_file_lock_depth;
    if (!fromDisk) {
        const char* slash = asm_strrchr_00452930(name, '\\');
        const char* base = (slash == 0) ? name : slash + 1;
        const char* forward = asm_strrchr_00452930(base, '/');
        if (forward == 0) forward = name; else ++forward;
        base = forward;

        if (g_archive.entries != 0 && g_archive.entry_count > 0) {
            DatArchiveEntry* entry = g_archive.entries;
            int remaining = g_archive.entry_count;
            do {
                if (asm_stricmp_0046054e(base, entry->name) == 0) {
                    size = entry->uncompressed_size;
                    goto looked_up;
                }
                --remaining;
                entry = (DatArchiveEntry*)((char*)entry + 16);
            } while (remaining > 0);
        }
        size = 0;
looked_up:
        if (outSize)
            *outSize = size;
        if (!size)
            goto failed;
        buffer = (char*)asm_malloc_00452706(size);
        if (!buffer)
            goto failed;
        DatArchiveRead(&g_archive, base, reinterpret_cast<unsigned char*>(buffer));
        goto done;
    }

    {
        void* file = imp_CreateFileA(name, 0x80000000, 1, 0, 3, 0x8000080, 0);
        if (file == (void*)-1)
            goto failed;
        size = imp_GetFileSize(file, 0);
        buffer = (char*)asm_malloc_00452706(size);
        if (!buffer) {
            imp_CloseHandle(file);
            goto failed;
        }
        imp_ReadFile(file, buffer, size, &size, 0);
        if (outSize)
            *outSize = size;
        imp_CloseHandle(file);
    }
done:
    imp_LeaveCriticalSection(g_file_lock);
    --g_file_lock_depth;
    return buffer;
failed:
    imp_LeaveCriticalSection(g_file_lock);
    --g_file_lock_depth;
    return 0;
}
#pragma code_seg()
