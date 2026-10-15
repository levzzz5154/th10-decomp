// 0x0043A1C0: checksum the executable, excluding its final complete dword.
#include "../../../build_support/layout/ltcg/native_archive_read/archive.hpp"
#include "th10/platform/archive_file.hpp"
extern "C" unsigned long (__stdcall *data_004660dc)(void*, char*, unsigned long);
extern "C" void __cdecl entry_free_00452422(void*);
extern "C" int data_00492380;
extern "C" int data_00492384;
#pragma code_seg(".text$a03checksum")
__declspec(noinline) int __stdcall ComputeExecutableChecksum() {
    int size;
    char filename[264];
    if (data_004660dc(0, filename, 0x105)) {
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
        entry_free_00452422(block);
        data_00492384 = file_size;
        data_00492380 = sum;
        return sum;
    }
    return -1;
}
#pragma code_seg()
