struct ThreadData {
    unsigned int thread_id;
    unsigned int thread_handle;
    unsigned char padding0[0x0c];
    unsigned int holdrand;
    unsigned char padding1[0x3c];
    void* initaddr;
};
extern "C" int __cdecl asm_mtinitlocks_00453aa1();
extern "C" void __cdecl asm_mtterm_00456327();
extern "C" void __stdcall asm_freefls_4_004563c8(void*);
extern "C" unsigned int __stdcall asm_FUN_0045631e_0045631e(void*);
extern "C" ThreadData* __cdecl asm_FUN_0045794d_0045794d(unsigned int, unsigned int);
extern "C" void* (__stdcall *data_00466198)(const char*);
extern "C" void* (__stdcall *data_00466158)(void*, const char*);
extern "C" unsigned int (__stdcall *data_0046619c)();
extern "C" void* data_0046615c;
extern "C" void* data_00466160;
extern "C" void* data_00466164;
extern "C" void* data_00477374;
extern "C" void* data_00477378;
extern "C" void* data_0047737c;
extern "C" void* data_00477380;
extern "C" unsigned int data_00473390;
extern "C" char data_004735d0;

extern "C" int __cdecl asm_mtinit_0045654a() {
    if (!asm_mtinitlocks_00453aa1()) {
        asm_mtterm_00456327();
        return 0;
    }
    void* module = data_00466198(reinterpret_cast<const char*>(0x46aa5c));
    if (module) {
        void* (__stdcall *get_proc)(void*, const char*) = data_00466158;
        data_00477374 = get_proc(module, reinterpret_cast<const char*>(0x46aa50));
        data_00477378 = get_proc(module, reinterpret_cast<const char*>(0x46aa44));
        data_0047737c = get_proc(module, reinterpret_cast<const char*>(0x46aa38));
        data_00477380 = get_proc(module, reinterpret_cast<const char*>(0x46aa30));
        if (!data_00477378) {
            data_00477378 = data_0046615c;
            data_0047737c = data_00466160;
            data_00477374 = reinterpret_cast<void*>(&asm_FUN_0045631e_0045631e);
            data_00477380 = data_00466164;
        }
    }
    data_00473390 = reinterpret_cast<unsigned int (__stdcall*)(void*)>(data_00477374)(reinterpret_cast<void*>(&asm_freefls_4_004563c8));
    if (data_00473390 != 0xffffffff) {
        ThreadData* data = asm_FUN_0045794d_0045794d(1, 0x8c);
        if (data && reinterpret_cast<int (__stdcall*)(unsigned int, ThreadData*)>(data_0047737c)(data_00473390, data)) {
            data->initaddr = &data_004735d0;
            data->holdrand = 1;
            unsigned int id = data_0046619c();
            data->thread_handle = 0xffffffff;
            data->thread_id = id;
            return 1;
        }
    }
    asm_mtterm_00456327();
    return 0;
}
