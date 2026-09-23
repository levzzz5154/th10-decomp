// Two Vec2 operators recovered from the 0x00441DD0 assembly span.
//
// The difference entry uses the EAX hidden result buffer, with this in ECX and
// the explicit operand in EDX. Its body computes operand - this, matching the
// values observed at [EDX] and [ECX]. The scale operator returns its Vec2 via
// EAX, receives this in ECX, and takes its float scale from the stack.
// The private register choices require the native-LTCG context in
// layout/ltcg/vector_ops_00441dd0.json; byte-exact output is not yet verified.

struct Vec2_00441dd0 {
    float x;
    float y;

    Vec2_00441dd0() {}
    Vec2_00441dd0(float x_value, float y_value)
        : x(x_value), y(y_value) {}
    Vec2_00441dd0(const Vec2_00441dd0& other)
        : x(other.x), y(other.y) {}

    __declspec(noinline) Vec2_00441dd0 operator-(
        const Vec2_00441dd0& operand) const;
    __declspec(noinline) Vec2_00441dd0 operator*(float scale) const;
};

#pragma code_seg(".text$01difference")
Vec2_00441dd0 Vec2_00441dd0::operator-(
        const Vec2_00441dd0& operand) const {
    return Vec2_00441dd0(operand.x - x, operand.y - y);
}
#pragma code_seg()

#pragma code_seg(".text$02scale")
Vec2_00441dd0 Vec2_00441dd0::operator*(float scale) const {
    return Vec2_00441dd0(x * scale, y * scale);
}
#pragma code_seg()
