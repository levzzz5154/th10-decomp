// 0x004051F0..0x00405218 scales a three-float vector by the reciprocal of a
// divisor. The retail entry has a private ABI: the receiver is in ECX, the
// divisor is on the stack, and the destination pointer arrives in EAX. The
// ordinary C++ model below spells the destination out as an explicit output
// parameter because that register arrangement is not expressible by a normal
// MSVC member declaration.
struct Vec3_004051F0 {
    float x;
    float y;
    float z;

    __declspec(noinline) void ScaleByReciprocalTo(
        float divisor,
        Vec3_004051F0* output) const;
};

extern "C" float data_00470afc; // 1.0f at 0x00470AFC

void Vec3_004051F0::ScaleByReciprocalTo(
    float divisor,
    Vec3_004051F0* output) const {
    const float reciprocal = data_00470afc / divisor;
    output->x = reciprocal * x;
    output->y = reciprocal * y;
    output->z = reciprocal * z;
}
