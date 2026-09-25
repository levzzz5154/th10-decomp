// Semantic candidate for the 17-byte equality leaf at 0x00418A50.
// Retail compares the receiver's dword at +0x04 with one stack argument and
// returns the equality result as a bool. The exact field meaning is unknown.

struct EqualityReceiver_00418A50 {
    unsigned int unknown_000;
    unsigned int value_004;

    __declspec(noinline) bool MatchesValue(unsigned int candidate) const;
};

#pragma code_seg(".text$01equality")
bool EqualityReceiver_00418A50::MatchesValue(unsigned int candidate) const {
    return value_004 == candidate;
}
#pragma code_seg()
