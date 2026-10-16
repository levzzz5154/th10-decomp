// 0x004243B0..0x004243BF: return whether the value at owner+0 is less than the stack argument.
struct FieldComparison4 {
    int value_0000;

    __declspec(noinline) int IsValueAt0000LessThan(int value) const;
};

#pragma code_seg(".text$01accessor")
int FieldComparison4::IsValueAt0000LessThan(int value) const {
    return value_0000 < value;
}
#pragma code_seg()
