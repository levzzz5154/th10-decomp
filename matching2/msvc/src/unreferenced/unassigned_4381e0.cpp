// 0x004381E0..0x004381EF: reset the small-string record to the empty inline form.
struct Object13 {
    unsigned char pad_000[4];
    char inline_data[0x10];
    unsigned int length;
    unsigned int capacity;
    __declspec(noinline) void Reset();
};

#pragma code_seg(".text$01accessor")
void Object13::Reset() {
    capacity = 0xf;
    length = 0;
    inline_data[0] = 0;
}

#pragma code_seg()
