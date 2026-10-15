// 0x00427DA0..0x00427DB6: divide both coordinates by a scalar.
// Native LTCG preserves the retail hidden-result/source/divisor register tuple.
#pragma code_seg(".text$01divide")
struct CellPairDivide {
    int first;
    int second;

    CellPairDivide() {}
    CellPairDivide(int first_value, int second_value)
        : first(first_value), second(second_value) {}

    __declspec(noinline) CellPairDivide operator/(int divisor) const;
};

__declspec(noinline) CellPairDivide CellPairDivide::operator/(int divisor) const {
    return CellPairDivide(first / divisor, second / divisor);
}
#pragma code_seg()
