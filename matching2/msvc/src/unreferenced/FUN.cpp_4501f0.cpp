// 0x004501F0..0x004501F6: store through the nested record at +0x4.
// Native LTCG selects the outer object in EAX and value in EDX.
struct NestedRecord {
    int value_000;
    int value_004;
};

struct OuterRecord {
    unsigned char pad_000[4];
    NestedRecord* nested_004;

    __declspec(noinline) void Store(int value);
};

typedef char NestedRecord_004501f0_size_must_fit[
    sizeof(NestedRecord) == 0x8 ? 1 : -1];
typedef char OuterRecord_004501f0_size_must_fit[
    sizeof(OuterRecord) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01store")
void OuterRecord::Store(int value) {
    nested_004->value_004 = value;
}
#pragma code_seg()
