// 0x0043B890..0x0043B8B0: release the record's owned handles and clear its handle slot.
// The native-LTCG cluster supplies the retail private ESI receiver convention.
extern "C" void (*data_00466288)(void* handle);
extern "C" void (*data_00466274)(void* memory);

struct Record_0043b890 {
    unsigned char pad_000[4];
    int handle_004;
    void* memory_008;

    __declspec(noinline) void Release();
};

#pragma code_seg(".text$01release")
void Record_0043b890::Release() {
    if (handle_004 != 0) data_00466288((void*)handle_004);
    data_00466274(memory_008);
    handle_004 = 0;
    __asm { _emit 0C3h }
}
#pragma code_seg()
