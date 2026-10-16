// 0x00428DF0..0x00428E00: report whether the two coordinates differ.
struct PairDifference {
    int first;
    int second;
};

#pragma code_seg(".text$01different")
__declspec(noinline) int PairDifference_00428df0_IsDifferent(PairDifference* pair) {
    return pair->second != pair->first;
}
#pragma code_seg()
