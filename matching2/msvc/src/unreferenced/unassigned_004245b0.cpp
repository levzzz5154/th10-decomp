// 0x004245B0..0x004245BF: return whether the value at owner+0 equals the stack argument.
// Retail's EDX/ECX allocation is the native-LTCG allocation of this member.
struct FieldComparison_004245b0 {
    int value_0000;

    __declspec(noinline) int IsValueAt0000EqualTo(int value) const;
};

#pragma code_seg(".text$01accessor")
int FieldComparison_004245b0::IsValueAt0000EqualTo(int value) const {
    return value_0000 == value;
}
#pragma code_seg()
