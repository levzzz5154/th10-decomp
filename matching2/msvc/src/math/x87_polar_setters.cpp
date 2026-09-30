// Retail x87 polar setters. Each sets (x, y) = (cos(angle), sin(angle)) scaled
// by the radius with one FSINCOS, keeping both results in extended precision
// until the float stores, and returns the receiver in EAX. No C++ spelling
// makes MSVC 7.1 fuse sine and cosine into FSINCOS, so the computation is
// the original-style inline block. Referencing `this` from it is what makes
// the compiler home the receiver in a stack slot (`push ecx; mov [esp],ecx`)
// and reload it into EAX, which also serves as the return value.

#define POLAR_VECTOR_SETTER(Type, Method)                                  \
    struct Type {                                                          \
        float x;                                                           \
        float y;                                                           \
        Type* Method(float angle, float radius);                           \
    };                                                                     \
    Type* Type::Method(float angle, float radius) {                        \
        __asm mov eax, this                                                \
        __asm fld angle                                                    \
        __asm fsincos                                                      \
        __asm fmul radius                                                  \
        __asm fstp [eax]Type.x                                             \
        __asm fmul radius                                                  \
        __asm fstp [eax]Type.y                                             \
    }

// Returns through EAX without a C++ return statement.
#pragma warning(disable : 4035)

POLAR_VECTOR_SETTER(ScoreGameplayPolarVector, SetScorePolar)   // 0x00408750
POLAR_VECTOR_SETTER(ScoreItemPolarVector, SetItemPolar)        // 0x0041BEB0
POLAR_VECTOR_SETTER(PathPolarVector, SetPathPolar)             // 0x0041F800
POLAR_VECTOR_SETTER(AnimationLeafPolarVector, SetAnimationPolar) // 0x00441EF0
POLAR_VECTOR_SETTER(AnimationPolarVector, SetAnimationPolar)   // 0x004458B0
POLAR_VECTOR_SETTER(RecoveryPolarVector, SetPolar)             // 0x0044C5D0
POLAR_VECTOR_SETTER(EclPolarVector, SetPolar)                  // 0x004501B0

// 0x00413270: separate horizontal and vertical radii; returns with RET 12.
struct EllipticPolarVector {
    float x;
    float y;
    EllipticPolarVector* SetEllipticPolar(float angle, float horizontal, float vertical);
};

EllipticPolarVector* EllipticPolarVector::SetEllipticPolar(float angle, float horizontal,
                                                           float vertical) {
    __asm mov eax, this
    __asm fld angle
    __asm fsincos
    __asm fmul horizontal
    __asm fstp [eax]EllipticPolarVector.x
    __asm fmul vertical
    __asm fstp [eax]EllipticPolarVector.y
}

#pragma warning(default : 4035)
