// 0x0043AF00..0x0043AF26: clear the record's control words and store the
// incoming value.
struct Object_0043af00 {
    unsigned char pad_000[0x2c8];
    unsigned int field_2c8;
    unsigned char pad_2cc[0x10];
    unsigned int field_2dc;
    unsigned int field_2e0;
    unsigned int field_2e4;
    unsigned int field_2e8;
    __declspec(noinline) int Reset(void* value);
};

#pragma code_seg(".text$01accessor")
int Object_0043af00::Reset(void* value) {
    field_2c8 = 0;
    field_2e4 = (unsigned int)value;
    field_2e8 = 0;
    field_2dc = 0;
    field_2e0 = 1;
    return 0;
}

#pragma code_seg()
