// 0x00427D50..0x00427D67: subtract two integer coordinate pairs.
struct Pair6 {
    int first;
    int second;

    Pair6() {}
    Pair6(int first_value, int second_value)
        : first(first_value), second(second_value) {}
    Pair6(const Pair6& other)
        : first(other.first), second(other.second) {}

    __declspec(noinline) Pair6 operator-(
        const Pair6& other) const;
};

#pragma code_seg(".text$01difference")
__declspec(noinline) Pair6 Pair6::operator-(
    const Pair6& other) const {
    return Pair6(first - other.first, second - other.second);
}
#pragma code_seg()
