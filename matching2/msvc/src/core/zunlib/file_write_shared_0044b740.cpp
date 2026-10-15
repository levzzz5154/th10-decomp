// 0x0044B740: write a block to the shared file; on a short write close it and release its lock.
extern "C" int (__stdcall* imp_CloseHandle)(void* handle);
extern "C" int (__stdcall* imp_WriteFile)(void* handle, const void* buffer, unsigned int size, unsigned int* written, void* overlapped);
extern "C" void (__stdcall* imp_LeaveCriticalSection)(void* section);
extern "C" void* data_00474c38;
extern "C" unsigned char data_0049231e;

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall WriteShared_0044b740(const void* buffer, unsigned int size) {
    unsigned int written;
    if (data_00474c38 == (void*)-1) return (int)data_00474c38;
    imp_WriteFile(data_00474c38, buffer, size, &written, 0);
    if (size != written) {
        imp_CloseHandle(data_00474c38);
        imp_LeaveCriticalSection((void*)0x004922A4);
        --data_0049231e;
        return -2;
    }
    return 0;
}
#pragma code_seg()
