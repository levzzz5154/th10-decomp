// 0x00427D80..0x00427D94: CellPair_Scale
// The native-LTCG context preserves the observed pair-return convention.
#pragma code_seg(".text$01scale")
struct CellPair {
    int first;
    int second;

    CellPair() {}
    CellPair(int first_value, int second_value)
        : first(first_value), second(second_value) {}
    CellPair(const CellPair& other)
        : first(other.first), second(other.second) {}

    __declspec(noinline) CellPair operator*(int scale) const;
};

__declspec(noinline) CellPair CellPair::operator*(int scale) const {
    return CellPair(first * scale, second * scale);
}
#pragma code_seg()
