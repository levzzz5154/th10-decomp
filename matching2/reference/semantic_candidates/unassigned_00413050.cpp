// Semantic candidate for the signed-comparison leaf at 0x00413050.
// The receiver is in ECX; its signed dword at +0x04 is compared with one
// stack argument, and the result is returned as a bool. See the focused
// recovery note for the old C-linkage near-match and unresolved boundary.

struct SignedComparisonReceiver_00413050 {
    int unknown_000;
    int value_004;

    __declspec(noinline) bool IsLessThan(int rhs) const;
};

#pragma code_seg(".text$01comparison")
bool SignedComparisonReceiver_00413050::IsLessThan(int rhs) const {
    return value_004 < rhs;
}
#pragma code_seg()
