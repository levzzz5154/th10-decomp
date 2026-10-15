// 0x0044B790: read the next block of the shared file into a new allocation.
#include <stdlib.h>
extern "C" int (__stdcall* imp_CloseHandle)(void* handle);
extern "C" int (__stdcall* imp_ReadFile)(void* handle, void* buffer, unsigned int size, unsigned int* read, void* overlapped);
extern "C" void* data_00474c38;

#pragma code_seg(".text$01accessor")
__declspec(noinline) void* __stdcall ReadShared_0044b790(unsigned int size) {
    unsigned int read;
    if (data_00474c38 == (void*)-1) return 0;
    void* buffer = malloc(size);
    if (!buffer) {
        imp_CloseHandle(data_00474c38);
        return 0;
    }
    imp_ReadFile(data_00474c38, buffer, size, &read, 0);
    return buffer;
}
#pragma code_seg()
