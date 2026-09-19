// 0x00409E00: read whether the +0x10 field is 1.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_00409e00 {
    unsigned char pad_000[0x10];
    int field_10;                          // +0x10
    __declspec(noinline) int IsOne() const;
};

int Predicate_00409e00::IsOne() const {
    return field_10 == 1;
}
