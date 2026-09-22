extern "C" unsigned int data_00473390;
extern "C" void* (__stdcall *data_00477378)(unsigned int);
extern "C" int (__stdcall *data_0047737c)(unsigned int, void*);
extern "C" void __stdcall asm_freefls_4_004563c8(void*);

extern "C" void __cdecl asm_freeptd_0045650f(void* data) {
    if (data_00473390 != 0xffffffff) {
        if (!data) data = data_00477378(data_00473390);
        asm_freefls_4_004563c8(data);
        data_0047737c(data_00473390, 0);
    }
}
