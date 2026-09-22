// 0x00427D50..0x00427D67: subtract two integer coordinate pairs.
struct Pair_00427d50 {
    int first;
    int second;

    Pair_00427d50() {}
    Pair_00427d50(int first_value, int second_value)
        : first(first_value), second(second_value) {}
    Pair_00427d50(const Pair_00427d50& other)
        : first(other.first), second(other.second) {}

    __declspec(noinline) Pair_00427d50 operator-(
        const Pair_00427d50& other) const;
};

#pragma code_seg(".text$01difference")
__declspec(noinline) Pair_00427d50 Pair_00427d50::operator-(
    const Pair_00427d50& other) const {
    return Pair_00427d50(first - other.first, second - other.second);
}
#pragma code_seg()
