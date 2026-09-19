// 0x004051C0: read whether the +0x390 field is set.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_004051c0 {
    unsigned char pad_000[0x390];
    int field_390;                          // +0x390
    __declspec(noinline) int IsNonZero() const;
};

int Predicate_004051c0::IsNonZero() const {
    return field_390 != 0;
}
