// 0x0043A1C0: checksum the executable, excluding its final complete dword.
#include "archive.hpp"
#include "th10/platform/archive_file.hpp"
extern "C" unsigned long (__stdcall *imp_GetModuleFileNameA)(void*, char*, unsigned long);
extern "C" void __cdecl crt_free(void*);
extern "C" int g_executable_checksum;
extern "C" int g_executable_size;
#pragma code_seg(".text$a03checksum")
__declspec(noinline) int __stdcall ComputeExecutableChecksum() {
    int size;
    char filename[264];
    if (imp_GetModuleFileNameA(0, filename, 0x105)) {
        int sum = 0;
        int* cursor = (int*)Archive_LoadFile(filename, &size, 1);
        int* block = cursor;
        if (!cursor)
            return -1;
        int file_size = size;
        int count = file_size / 4 - 1;
        if (count > 0) {
            do {
                sum += *cursor++;
            } while (--count);
        }
        crt_free(block);
        g_executable_size = file_size;
        g_executable_checksum = sum;
        return sum;
    }
    return -1;
}
#pragma code_seg()
