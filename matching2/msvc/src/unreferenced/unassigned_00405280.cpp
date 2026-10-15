// 0x00405280..0x00405290: return whether the signed value at owner+4 is at
// most the stack argument. Retail's EDX/ECX allocation is the native-LTCG
// allocation of this member.
struct PlayerLeafComparison_00405280 {
    unsigned char unknown_0000_0003[0x4];
    int unknown_value_0004;

    __declspec(noinline) int IsUnknownValueAt0004AtMost(int value) const;
};

#pragma code_seg(".text$01accessor")
int PlayerLeafComparison_00405280::IsUnknownValueAt0004AtMost(int value) const {
    return unknown_value_0004 <= value;
}
#pragma code_seg()
