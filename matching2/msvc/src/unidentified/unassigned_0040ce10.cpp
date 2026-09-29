// 0x0040CE10: store one (float, int) pair in the table at +0x9E94.
struct Pair_0040ce10 { float value; int tag; };
struct PairTable_0040ce10 {
    unsigned char reserved_000[0x9E94];
    Pair_0040ce10 pairs[1];          // +0x9E94
    __declspec(noinline) void Set(int index, int tag, float value);
};

#pragma code_seg(".text$01accessor")
void PairTable_0040ce10::Set(int index, int tag, float value) {
    pairs[index].tag = tag;
    pairs[index].value = value;
}
#pragma code_seg()
