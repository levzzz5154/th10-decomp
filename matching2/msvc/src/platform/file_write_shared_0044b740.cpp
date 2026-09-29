// 0x0044B740: write a block to the shared file; on a short write close it and release its lock.
extern "C" int (__stdcall* data_004660cc)(void* handle);
extern "C" int (__stdcall* data_004660d4)(void* handle, const void* buffer, unsigned int size, unsigned int* written, void* overlapped);
extern "C" void (__stdcall* data_004660b4)(void* section);
extern "C" void* data_00474c38;
extern "C" unsigned char data_0049231e;

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall WriteShared_0044b740(const void* buffer, unsigned int size) {
    unsigned int written;
    if (data_00474c38 == (void*)-1) return (int)data_00474c38;
    data_004660d4(data_00474c38, buffer, size, &written, 0);
    if (size != written) {
        data_004660cc(data_00474c38);
        data_004660b4((void*)0x004922A4);
        --data_0049231e;
        return -2;
    }
    return 0;
}
#pragma code_seg()
