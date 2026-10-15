// 0x0043B890..0x0043B8AF: release the record's owned handles and clear its handle slot.
// The adjacent RET at 0x0043B8B0 is a separate empty C++ function so native
// LTCG can keep both retail bytes without embedding an instruction in this body.
// The cluster supplies the retail private ESI receiver convention.
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
    return;
}
#pragma code_seg()

#pragma code_seg(".text$02adjacentret")
__declspec(noinline) void __stdcall Empty_0043b8b0() {
    return;
}
#pragma code_seg()
