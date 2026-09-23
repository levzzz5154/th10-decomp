// Semantic candidate for the helper at 0x00405280.
// Retail reads the signed value at owner+4, compares it with a signed stack
// argument, returns the <= predicate in EAX, and pops the argument with RET 4.
// The ordinary member declaration below does not express retail's EDX/ECX
// register allocation; exact ABI and output remain unverified.
struct PlayerLeafComparison_00405280 {
    unsigned char unknown_0000_0003[0x4];
    int unknown_value_0004;

    __declspec(noinline) bool IsUnknownValueAt0004LessThanOrEqualTo(int value) const;
};

bool PlayerLeafComparison_00405280::IsUnknownValueAt0004LessThanOrEqualTo(int value) const {
    return unknown_value_0004 <= value;
}
