// 0x0044B740: write a block to the shared file; on a short write close it and release its lock.
extern "C" int (__stdcall* imp_CloseHandle)(void* handle);
extern "C" int (__stdcall* imp_WriteFile)(void* handle, const void* buffer, unsigned int size, unsigned int* written, void* overlapped);
extern "C" void (__stdcall* imp_LeaveCriticalSection)(void* section);
extern "C" void* g_file_write_handle;
extern "C" unsigned char g_file_lock_depth;

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall WriteShared_0044b740(const void* buffer, unsigned int size) {
    unsigned int written;
    if (g_file_write_handle == (void*)-1) return (int)g_file_write_handle;
    imp_WriteFile(g_file_write_handle, buffer, size, &written, 0);
    if (size != written) {
        imp_CloseHandle(g_file_write_handle);
        imp_LeaveCriticalSection((void*)0x004922A4);
        --g_file_lock_depth;
        return -2;
    }
    return 0;
}
#pragma code_seg()
