// 0x0043B840: release the record's two owned handles and recreate the first one
// through the platform callbacks held in the global slots.
extern "C" void (*imp_timeKillEvent)(void* handle);
extern "C" void (*imp_timeEndPeriod)(void* memory);
extern "C" void (*imp_timeBeginPeriod)(void* memory);
extern "C" int (*imp_timeSetEvent)(int size, void* memory, void* entry, void* owner, int flag);
struct Record5 {
    unsigned char pad_000[4];
    int handle_004;
    void* memory_008;
    __declspec(noinline) void Renew();
};
#pragma code_seg(".text$01accessor")
void Record5::Renew() {
    if (handle_004 != 0) imp_timeKillEvent((void*)handle_004);
    imp_timeEndPeriod(memory_008);
    handle_004 = 0;
    imp_timeBeginPeriod(memory_008);
    handle_004 = imp_timeSetEvent(0x10, memory_008, (void*)0x43A6E0, this, 1);
}
#pragma code_seg()
