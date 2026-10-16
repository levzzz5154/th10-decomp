// 0x0044B790: read the next block of the shared file into a new allocation.
#include <stdlib.h>
extern "C" int (__stdcall* imp_CloseHandle)(void* handle);
extern "C" int (__stdcall* imp_ReadFile)(void* handle, void* buffer, unsigned int size, unsigned int* read, void* overlapped);
extern "C" void* g_file_write_handle;

#pragma code_seg(".text$01accessor")
__declspec(noinline) void* __stdcall ReadShared2(unsigned int size) {
    unsigned int read;
    if (g_file_write_handle == (void*)-1) return 0;
    void* buffer = malloc(size);
    if (!buffer) {
        imp_CloseHandle(g_file_write_handle);
        return 0;
    }
    imp_ReadFile(g_file_write_handle, buffer, size, &read, 0);
    return buffer;
}
#pragma code_seg()
