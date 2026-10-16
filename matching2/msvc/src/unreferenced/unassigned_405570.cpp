// 0x00405570: read whether the +0x3738 field is at least 60.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate2 {
    unsigned char pad_000[0x3738];
    int field_3738;                          // +0x3738
    __declspec(noinline) int IsAtLeast60() const;
};

int Predicate2::IsAtLeast60() const {
    return field_3738 >= 0x3C;
}
