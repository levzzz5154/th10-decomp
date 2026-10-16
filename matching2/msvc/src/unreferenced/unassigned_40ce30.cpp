// 0x0040CE30: read whether the +0x9EB8 field is set.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate5 {
    unsigned char pad_000[0x9EB8];
    int field_9eb8;                          // +0x9EB8
    __declspec(noinline) int IsNonZero() const;
};

int Predicate5::IsNonZero() const {
    return field_9eb8 != 0;
}
