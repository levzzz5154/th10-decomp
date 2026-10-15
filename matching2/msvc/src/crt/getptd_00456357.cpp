struct ThreadData {
    unsigned int thread_id;
    unsigned int thread_handle;
    unsigned char padding0[0x0c];
    unsigned int holdrand;
    unsigned char padding1[0x3c];
    void* initaddr;
};
extern "C" unsigned int (__stdcall *imp_GetLastError)();
extern "C" void (__stdcall *imp_SetLastError)(unsigned int);
extern "C" unsigned int (__stdcall *imp_GetCurrentThreadId)();
extern "C" ThreadData* (__stdcall *data_00477378)(unsigned int);
extern "C" int (__stdcall *data_0047737c)(unsigned int, ThreadData*);
extern "C" unsigned int data_00473390;
extern "C" char data_004735d0;
extern "C" ThreadData* __cdecl asm_FUN_0045794d_0045794d(unsigned int, unsigned int);
extern "C" void __cdecl asm_amsg_exit_0045373d(int);

extern "C" ThreadData* __cdecl asm_getptd_00456357() {
    unsigned int saved_error = imp_GetLastError();
    ThreadData* data = data_00477378(data_00473390);
    if (!data) {
        data = asm_FUN_0045794d_0045794d(1, 0x8c);
        if (data && data_0047737c(data_00473390, data)) {
            data->initaddr = &data_004735d0;
            data->holdrand = 1;
            unsigned int id = imp_GetCurrentThreadId();
            data->thread_handle = 0xffffffff;
            data->thread_id = id;
        } else {
            asm_amsg_exit_0045373d(0x10);
        }
    }
    imp_SetLastError(saved_error);
    return data;
}
