// Semantic candidate for the helper at 0x00405170.
// The retail helper takes its owner in EAX, its raw 32-bit value on the stack,
// and returns with RET 4.  The ordinary member declaration below does not
// express that private EAX receiver ABI; the candidate is not byte-verified.
struct PlayerLeafFields_00405170 {
    unsigned char unknown_0000_003F[0x40];
    unsigned int unknown_value_0040;
    unsigned char unknown_0044_035B[0x318];
    unsigned int unknown_flags_035C;

    __declspec(noinline) void SetUnknownValueAt0040(unsigned int value);
};

void PlayerLeafFields_00405170::SetUnknownValueAt0040(unsigned int value) {
    unknown_value_0040 = value;
    unknown_flags_035C |= 0x8;
}
