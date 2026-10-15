// 0x0042C840..0x0042C848: signed-byte table lookup.
// Native LTCG keeps the table in ECX and the index in EAX.
struct ByteTable_0042c840 {
    unsigned char pad_000[0x1D888];
    signed char value_1d888[1];
    __declspec(noinline) int Read(int index);
};

#pragma code_seg(".text$01read")
int ByteTable_0042c840::Read(int index) {
    return value_1d888[index];
}
#pragma code_seg()
