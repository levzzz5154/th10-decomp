
struct PlatformWorker_0043bba0 {
    const void* vtable;
    void* thread;
    unsigned int thread_id;
    unsigned int stop_requested;
    unsigned int running;
    unsigned int reserved_14;
    void* entry;
    __declspec(noinline) void Stop();
};
extern "C" PlatformWorker_0043bba0 data_00474dd4;
extern "C" void* data_00474dd8;
extern "C" unsigned int data_00474ddc;
extern "C" int data_00474de0;
extern "C" int data_00474de4;
extern "C" void* data_00474dec;
extern "C" unsigned int __cdecl asm_beginthreadex_00453683(
        void* security, unsigned int stack_size, void* start, void* arglist,
        unsigned int initflag, unsigned int* thread_id);

#pragma code_seg(".text$01start")
__declspec(noinline) void StartWorker_0043bba0() {
    data_00474dd4.Stop();
    data_00474dec = (void*)0x43BA90;
    data_00474de4 = 1;
    data_00474de0 = 0;
    data_00474dd8 = (void*)asm_beginthreadex_00453683(0, 0, (void*)0x43BA90,
                                                     (void*)0x491C28, 0, &data_00474ddc);
}
#pragma code_seg()
