// 0x0040CE80: read whether the +0x28 field is set.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate6 {
    unsigned char pad_000[0x28];
    int field_28;                          // +0x28
    __declspec(noinline) int IsNonZero() const;
};

int Predicate6::IsNonZero() const {
    return field_28 != 0;
}
