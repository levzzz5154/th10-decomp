
struct PlatformWorker2 {
    const void* vtable;
    void* thread;
    unsigned int thread_id;
    unsigned int stop_requested;
    unsigned int running;
    unsigned int reserved_14;
    void* entry;
    __declspec(noinline) void Stop();
};
extern "C" PlatformWorker2 g_input_worker;
extern "C" void* g_clip_thread_handle;
extern "C" unsigned int g_clip_thread_id;
extern "C" int g_clip_thread_started;
extern "C" int g_clip_thread_exit;
extern "C" void* g_clip_thread_entry;
extern "C" unsigned int __cdecl crt_beginthreadex(
        void* security, unsigned int stack_size, void* start, void* arglist,
        unsigned int initflag, unsigned int* thread_id);

#pragma code_seg(".text$01start")
__declspec(noinline) void StartWorker2() {
    g_input_worker.Stop();
    g_clip_thread_entry = (void*)0x43BA90;
    g_clip_thread_exit = 1;
    g_clip_thread_started = 0;
    g_clip_thread_handle = (void*)crt_beginthreadex(0, 0, (void*)0x43BA90,
                                                     (void*)0x491C28, 0, &g_clip_thread_id);
}
#pragma code_seg()
