// 0x00436970: close the record's handle and reopen it through the import slot,
// passing the record's string storage (inline when the capacity is under 0x10).
extern "C" void (*data_00466030)(void* handle);
extern "C" int (*data_00466034)(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                                int a8, int a9, int a10, int a11, int a12, int a13, const char* a14);
struct Record_00436970 {
    void* field_000;
    int field_004;
    int field_008;
    unsigned char pad_00c[4];
    void* storage_010;
    unsigned char pad_014[0x10];
    unsigned int capacity_024;
    int field_028;
    __declspec(noinline) void Reopen();
};
#pragma code_seg(".text$01accessor")
void Record_00436970::Reopen() {
    if (field_000 != 0) {
        data_00466030(field_000);
        field_000 = 0;
    }
    const char* text;
    if (capacity_024 >= 0x10) {
        text = (const char*)storage_010;
    } else {
        text = (const char*)((unsigned char*)this + 0x10);
    }
    field_000 = (void*)data_00466034(field_008, field_004, 0, 0, field_028, 0, 0, 0,
                                     1, 0, 0, 0, 0x30, text);
}
#pragma code_seg()
