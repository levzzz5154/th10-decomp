// 0x0043D0F0..0x0043D111: start the thread whose body sits at 0x0043D080.
extern "C" __declspec(dllimport) void* __stdcall CreateThread(
    void* attributes, unsigned int stack_size, void* start, void* parameter,
    unsigned int flags, unsigned int* thread_id);

extern "C" int g_sound_manager;
extern "C" void* g_sound_preload_thread;

void SpawnThread_0043d0f0() {
    unsigned int id;
    g_sound_preload_thread = CreateThread(0, 0, (void*)0x43d080, &g_sound_manager, 0, &id);
}
