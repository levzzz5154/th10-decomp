
struct Options_0040ce50 {
    unsigned char pad_000[0x9EC0];
    int max_value;
    __declspec(noinline) void SetMax(int value);
};

#pragma code_seg(".text$01setmax")
void Options_0040ce50::SetMax(int value) {
    if (value > 99) value = 99;
    max_value = value;
}
#pragma code_seg()
