// 0x00427D30..0x00427D41 (18 bytes): does the pair hold one value twice?
//
// Retail compares both dwords of the pair at +0x00/+0x04 against the incoming
// value and answers 0 when both match, 1 otherwise.  The pair arrives in ECX
// and the value in EAX.

struct Pair_00427d30 {
    int first;                             // +0x00
    int second;                            // +0x04
};

__declspec(noinline) int Pair_00427d30_Matches(Pair_00427d30* pair, int value);

#pragma code_seg(".text$01match")
int Pair_00427d30_Matches(Pair_00427d30* pair, int value) {
    if (pair->first != value || pair->second != value) {
        return 1;
    }
    return 0;
}
#pragma code_seg()
