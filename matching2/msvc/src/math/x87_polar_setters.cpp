// Retail polar setters use one x87 FSINCOS and keep both products in extended
// precision until the float stores. GCC's sincosl intrinsic expresses that
// computation directly. The pinned word-home pass reserves the receiver's
// volatile stack slot with its incoming value; it never rewrites emitted code.

#define POLAR_VECTOR_SETTER(Type, Method)                                  \
    struct Type {                                                          \
        float x;                                                           \
        float y;                                                           \
        __attribute__((thiscall, noinline)) Type* Method(float angle, float radius); \
    };                                                                     \
    Type* Type::Method(float angle, float radius) {                          \
        Type* volatile storedReceiver = this;                              \
        Type* destination = storedReceiver;                                \
        volatile float& radians = angle;                                   \
        long double sine, cosine;                                          \
        __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine); \
        volatile float& scale = radius;                                    \
        destination->x = static_cast<float>(cosine * static_cast<long double>(scale)); \
        destination->y = static_cast<float>(sine * static_cast<long double>(scale)); \
        return destination;                                                \
    }

POLAR_VECTOR_SETTER(ScoreGameplayPolarVector, SetScorePolar)      // 0x00408750
POLAR_VECTOR_SETTER(ScoreItemPolarVector, SetItemPolar)           // 0x0041BEB0
POLAR_VECTOR_SETTER(PathPolarVector, SetPathPolar)                // 0x0041F800
POLAR_VECTOR_SETTER(AnimationLeafPolarVector, SetAnimationPolar) // 0x00441EF0
POLAR_VECTOR_SETTER(AnimationPolarVector, SetAnimationPolar)     // 0x004458B0
POLAR_VECTOR_SETTER(RecoveryPolarVector, SetPolar)               // 0x0044C5D0
POLAR_VECTOR_SETTER(EclPolarVector, SetPolar)                    // 0x004501B0

#undef POLAR_VECTOR_SETTER

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
