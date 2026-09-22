// 0x00427DA0..0x00427DB6: divide both coordinates by a scalar.
// Native LTCG preserves the retail hidden-result/source/divisor register tuple.
#pragma code_seg(".text$01divide")
struct CellPairDivide_00427da0 {
    int first;
    int second;

    CellPairDivide_00427da0() {}
    CellPairDivide_00427da0(int first_value, int second_value)
        : first(first_value), second(second_value) {}

    __declspec(noinline) CellPairDivide_00427da0 operator/(int divisor) const;
};

__declspec(noinline) CellPairDivide_00427da0 CellPairDivide_00427da0::operator/(int divisor) const {
    return CellPairDivide_00427da0(first / divisor, second / divisor);
}
#pragma code_seg()
