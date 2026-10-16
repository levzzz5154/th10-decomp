// 0x00417660..0x0041766F: compare the first integer stored in an unidentified
// receiver with the one stack argument and return whether they differ.
// Retail's EDX/ECX allocation is the native-LTCG allocation of this member.
struct UnidentifiedIntField {
    int value;

    __declspec(noinline) int IsNotEqualTo(int other) const;
};

#pragma code_seg(".text$01accessor")
int UnidentifiedIntField::IsNotEqualTo(int other) const {
    return value != other;
}
#pragma code_seg()
