// 0x00404E90..0x00404EA0: return whether the signed value at owner+4 is at least the stack argument.
// Retail's EDX/ECX allocation is the native-LTCG allocation of this member.
struct FieldComparison_00404e90 {
    unsigned char unknown_0000_0003[0x4];
    int value_0004;

    __declspec(noinline) int IsValueAt0004AtLeast(int value) const;
};

#pragma code_seg(".text$01accessor")
int FieldComparison_00404e90::IsValueAt0004AtLeast(int value) const {
    return value_0004 >= value;
}
#pragma code_seg()
