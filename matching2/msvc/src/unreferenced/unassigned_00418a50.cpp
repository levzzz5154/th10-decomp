// 0x00418A50..0x00418A60: return whether the value at owner+4 equals the stack argument.
// Retail's EDX/ECX allocation is the native-LTCG allocation of this member.
struct FieldComparison_00418a50 {
    unsigned char unknown_0000_0003[0x4];
    int value_0004;

    __declspec(noinline) int IsValueAt0004EqualTo(int value) const;
};

#pragma code_seg(".text$01accessor")
int FieldComparison_00418a50::IsValueAt0004EqualTo(int value) const {
    return value_0004 == value;
}
#pragma code_seg()
