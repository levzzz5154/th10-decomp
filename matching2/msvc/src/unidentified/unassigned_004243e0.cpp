// 0x004243E0..0x004243EF: return whether the value at owner+0 differs from the stack argument.
// Retail's EDX/ECX allocation is the native-LTCG allocation of this member.
struct FieldComparison_004243e0 {
    int value_0000;

    __declspec(noinline) int IsValueAt0000NotEqualTo(int value) const;
};

#pragma code_seg(".text$01accessor")
int FieldComparison_004243e0::IsValueAt0000NotEqualTo(int value) const {
    return value_0000 != value;
}
#pragma code_seg()
