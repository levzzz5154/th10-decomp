// 0x0043B840: release the record's two owned handles and recreate the first one
// through the platform callbacks held in the global slots.
extern "C" void (*data_00466288)(void* handle);
extern "C" void (*data_00466274)(void* memory);
extern "C" void (*data_00466278)(void* memory);
extern "C" int (*data_0046628c)(int size, void* memory, void* entry, void* owner, int flag);
struct Record_0043b840 {
    unsigned char pad_000[4];
    int handle_004;
    void* memory_008;
    __declspec(noinline) void Renew();
};
#pragma code_seg(".text$01accessor")
void Record_0043b840::Renew() {
    if (handle_004 != 0) data_00466288((void*)handle_004);
    data_00466274(memory_008);
    handle_004 = 0;
    data_00466278(memory_008);
    handle_004 = data_0046628c(0x10, memory_008, (void*)0x43A6E0, this, 1);
}
#pragma code_seg()
