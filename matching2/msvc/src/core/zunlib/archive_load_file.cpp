// 0x0044B360: load a named file either from the packed archive index or from disk.
#include "../../../build_support/layout/ltcg/native_archive_read/archive.hpp"

extern "C" DatArchive data_00497990;
extern "C" unsigned char data_0049231e;
extern "C" unsigned char data_004922a4[];

extern "C" void (__stdcall *data_004660b0)(void*);
extern "C" void (__stdcall *data_004660b4)(void*);
extern "C" void* (__stdcall *data_004660c4)(const char*, unsigned int, unsigned int, void*,
                                            unsigned int, unsigned int, void*);
extern "C" int (__stdcall *data_004660cc)(void*);
extern "C" int (__stdcall *data_004660d0)(void*, void*, unsigned int, unsigned int*, void*);
extern "C" unsigned int (__stdcall *data_004660d8)(void*, unsigned int*);

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
    data_004660b0(data_004922a4);
    ++data_0049231e;
    if (!fromDisk) {
        const char* slash = asm_strrchr_00452930(name, '\\');
        const char* base = (slash == 0) ? name : slash + 1;
        const char* forward = asm_strrchr_00452930(base, '/');
        if (forward == 0) forward = name; else ++forward;
        base = forward;

        if (data_00497990.entries != 0 && data_00497990.entry_count > 0) {
            DatArchiveEntry* entry = data_00497990.entries;
            int remaining = data_00497990.entry_count;
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
        DatArchiveRead(&data_00497990, base, reinterpret_cast<unsigned char*>(buffer));
        goto done;
    }

    {
        void* file = data_004660c4(name, 0x80000000, 1, 0, 3, 0x8000080, 0);
        if (file == (void*)-1)
            goto failed;
        size = data_004660d8(file, 0);
        buffer = (char*)asm_malloc_00452706(size);
        if (!buffer) {
            data_004660cc(file);
            goto failed;
        }
        data_004660d0(file, buffer, size, &size, 0);
        if (outSize)
            *outSize = size;
        data_004660cc(file);
    }
done:
    data_004660b4(data_004922a4);
    --data_0049231e;
    return buffer;
failed:
    data_004660b4(data_004922a4);
    --data_0049231e;
    return 0;
}
#pragma code_seg()
