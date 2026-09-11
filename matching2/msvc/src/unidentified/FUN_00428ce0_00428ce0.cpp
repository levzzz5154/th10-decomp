// 0x00428CE0..0x00428D2F: FUN_00428ce0
// Signed difference of two angles, wrapped into [-pi, pi] by one full turn.
// Returns the extended-precision result the x87 comparison used, so the value
// stays in ST(0).
double __stdcall FUN_00428ce0(float first, float second) {
    const float pi = 3.14159265358979323846f;
    const float tau = 6.28318530717958647692f;
    float difference = first - second;
    if (difference > pi)
        return first - (tau + second);
    if (second - first > pi)
        return first - (second - tau);
    return difference;
}
