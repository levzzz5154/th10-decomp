// 0x0040CE10: store one (float, int) pair in the table at +0x9E94.
struct Pair3 { float value; int tag; };
struct PairTable {
    unsigned char reserved_000[0x9E94];
    Pair3 pairs[1];          // +0x9E94
    __declspec(noinline) void Set(int index, int tag, float value);
};

#pragma code_seg(".text$01accessor")
void PairTable::Set(int index, int tag, float value) {
    pairs[index].tag = tag;
    pairs[index].value = value;
}
#pragma code_seg()
