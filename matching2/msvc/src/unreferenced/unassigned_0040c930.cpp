// 0x0040C930: read whether the +0x0 field is positive.
//
// The receiver arrives in ECX - a plain __thiscall member - so the body is
// an ordinary translation unit, not a cluster.
struct Predicate_0040c930 {
    int field_0;                          // +0x0
    __declspec(noinline) int IsPositive() const;
};

int Predicate_0040c930::IsPositive() const {
    return field_0 > 0;
}
