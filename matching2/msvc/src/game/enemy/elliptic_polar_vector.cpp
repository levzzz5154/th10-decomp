// 0x00413270: independent horizontal and vertical scales; callee pops 12 bytes.
struct EllipticPolarVector {
    float x;
    float y;
    __attribute__((thiscall, noinline))
    EllipticPolarVector* SetEllipticPolar(float angle, float horizontal, float vertical);
};

EllipticPolarVector* EllipticPolarVector::SetEllipticPolar(float angle, float horizontal,
                                                        float vertical) {
    EllipticPolarVector* volatile storedReceiver = this;
    EllipticPolarVector* destination = storedReceiver;
    volatile float& radians = angle;
    long double sine, cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float& horizontalScale = horizontal;
    volatile float& verticalScale = vertical;
    destination->x = static_cast<float>(cosine * static_cast<long double>(horizontalScale));
    destination->y = static_cast<float>(sine * static_cast<long double>(verticalScale));
    return destination;
}
