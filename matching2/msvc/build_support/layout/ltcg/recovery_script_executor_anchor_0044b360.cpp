// 0x0044B360: load a named file either from the packed archive index or from disk.
#include "th10/platform/archive_file.hpp"

struct ArchiveEntry {
    const char* name;       // +0x00
    unsigned int unknown;   // +0x04
    unsigned int size;      // +0x08
    unsigned int unknown2;  // +0x0C
};

struct ArchiveReader {
    char* Read(const void* table, char* block);
};

extern "C" ArchiveEntry* g_archive;
extern "C" int data_00497994;
extern "C" unsigned char data_0049231e;
extern "C" unsigned char data_004922a4[];

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

#pragma code_seg(".text$0044b360_fn")
extern "C" __declspec(noinline) char* __stdcall Archive_LoadFile(const char* name, int* outSize,
                                                                 int fromDisk) {
    char* buffer;
    unsigned int size;
    imp_EnterCriticalSection(data_004922a4);
    ++data_0049231e;
    if (!fromDisk) {
        const char* slash = asm_strrchr_00452930(name, '\\');
        const char* base = (slash == 0) ? name : slash + 1;
        const char* forward = asm_strrchr_00452930(base, '/');
        if (forward == 0) forward = name; else ++forward;
        base = forward;

        if (g_archive != 0 && data_00497994 > 0) {
            ArchiveEntry* entry = g_archive;
            int remaining = data_00497994;
            do {
                if (asm_stricmp_0046054e(base, entry->name) == 0) {
                    size = entry->size;
                    goto looked_up;
                }
                --remaining;
                entry = (ArchiveEntry*)((char*)entry + 16);
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
        ((ArchiveReader*)base)->Read(&g_archive, buffer);
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
    imp_LeaveCriticalSection(data_004922a4);
    --data_0049231e;
    return buffer;
failed:
    imp_LeaveCriticalSection(data_004922a4);
    --data_0049231e;
    return 0;
}
#pragma code_seg()
