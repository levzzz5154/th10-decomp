// 0x0043CBF0..0x0043CC28: clear the record and start its worker thread.
#include <string.h>

extern "C" __declspec(dllimport) void* __stdcall CreateThread(
    void* attributes, unsigned int stack_size, void* start, void* parameter,
    unsigned int flags, unsigned int* thread_id);

struct Object32 {
    unsigned char pad_000[0x5218];
    void* thread;                    // +0x5218
    unsigned char pad_521c[4];
    unsigned int thread_id;          // +0x5220
    unsigned int field_5224;         // +0x5224
    unsigned int field_5228;         // +0x5228
    __declspec(noinline) int Start(unsigned int value);
};

#pragma code_seg(".text$01accessor")
int Object32::Start(unsigned int value) {
    memset(this, 0, 0x14b4 * 4);
    field_5228 = value;
    thread = CreateThread(0, 0, (void*)0x43ccf0, this, 0, &thread_id);
    return 0;
}
#pragma code_seg()
