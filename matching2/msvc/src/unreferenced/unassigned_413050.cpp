// 0x00413050..0x00413060: return whether the signed value at owner+4 is less than the stack argument.
// Retail's EDX/ECX allocation is the native-LTCG allocation of this member.
struct FieldComparison2 {
    unsigned char unknown_0000_0003[0x4];
    int value_0004;

    __declspec(noinline) int IsValueAt0004LessThan(int value) const;
};

#pragma code_seg(".text$01accessor")
int FieldComparison2::IsValueAt0004LessThan(int value) const {
    return value_0004 < value;
}
#pragma code_seg()
