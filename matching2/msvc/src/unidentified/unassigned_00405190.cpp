// Semantic candidate for the helper at 0x00405190.
// The retail helper takes its owner in EAX, its raw 32-bit value on the stack,
// and returns with RET 4.  The ordinary member declaration below does not
// express that private EAX receiver ABI; the candidate is not byte-verified.
struct PlayerLeafFields_00405190 {
    unsigned char unknown_0000_003B[0x3C];
    unsigned int unknown_value_003C;
    unsigned char unknown_0040_035B[0x31C];
    unsigned int unknown_flags_035C;

    __declspec(noinline) void SetUnknownValueAt003C(unsigned int value);
};

void PlayerLeafFields_00405190::SetUnknownValueAt003C(unsigned int value) {
    unknown_value_003C = value;
    unknown_flags_035C |= 0x8;
}
