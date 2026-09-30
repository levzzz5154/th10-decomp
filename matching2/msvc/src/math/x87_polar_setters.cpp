// Complete retail x87 polar setters. Compiler-generated FSINCOS preserves
// extended intermediates until the two final float stores.

struct ScoreItemPolarVector {
    float x;
    float y;
    __attribute__((thiscall, noinline)) ScoreItemPolarVector *SetItemPolar(float angle, float scale);
};

ScoreItemPolarVector *ScoreItemPolarVector::SetItemPolar(float angle, float scale) {
    ScoreItemPolarVector *volatile storedReceiver = this;
    ScoreItemPolarVector *destination = storedReceiver;
    volatile float &radians = angle;
    long double sine;
    long double cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float &radius = scale;
    destination->x = static_cast<float>(cosine * static_cast<long double>(radius));
    destination->y = static_cast<float>(sine * static_cast<long double>(radius));
    return destination;
}

struct AnimationPolarVector {
    float x;
    float y;
    __attribute__((thiscall, noinline)) AnimationPolarVector *SetAnimationPolar(float angle, float scale);
};

AnimationPolarVector *AnimationPolarVector::SetAnimationPolar(float angle, float scale) {
    AnimationPolarVector *volatile storedReceiver = this;
    AnimationPolarVector *destination = storedReceiver;
    volatile float &radians = angle;
    long double sine;
    long double cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float &radius = scale;
    destination->x = static_cast<float>(cosine * static_cast<long double>(radius));
    destination->y = static_cast<float>(sine * static_cast<long double>(radius));
    return destination;
}

struct ScoreGameplayPolarVector {
    float x;
    float y;
    __attribute__((thiscall, noinline)) ScoreGameplayPolarVector *SetScorePolar(float angle, float scale);
};

ScoreGameplayPolarVector *ScoreGameplayPolarVector::SetScorePolar(float angle, float scale) {
    ScoreGameplayPolarVector *volatile storedReceiver = this;
    ScoreGameplayPolarVector *destination = storedReceiver;
    volatile float &radians = angle;
    long double sine;
    long double cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float &radius = scale;
    destination->x = static_cast<float>(cosine * static_cast<long double>(radius));
    destination->y = static_cast<float>(sine * static_cast<long double>(radius));
    return destination;
}

struct PathPolarVector {
    float x;
    float y;
    __attribute__((thiscall, noinline)) PathPolarVector *SetPathPolar(float angle, float scale);
};

PathPolarVector *PathPolarVector::SetPathPolar(float angle, float scale) {
    PathPolarVector *volatile storedReceiver = this;
    PathPolarVector *destination = storedReceiver;
    volatile float &radians = angle;
    long double sine;
    long double cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float &radius = scale;
    destination->x = static_cast<float>(cosine * static_cast<long double>(radius));
    destination->y = static_cast<float>(sine * static_cast<long double>(radius));
    return destination;
}

struct RecoveryPolarVector {
    float x;
    float y;
};

// The first argument arrives in ECX; the two floats are popped by RET 8.
extern "C" __attribute__((thiscall, noinline, used,
                           section(".text$recovery_polar"), aligned(1)))
RecoveryPolarVector* asm_Recovery_PolarToVectorRetail_0044c5d0(
        RecoveryPolarVector* receiver, float angle, float scale) {
    RecoveryPolarVector* volatile storedReceiver = receiver;
    RecoveryPolarVector* destination = storedReceiver;
    volatile float& radians = angle;
    long double sine;
    long double cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float& radius = scale;
    destination->x = static_cast<float>(cosine * static_cast<long double>(radius));
    destination->y = static_cast<float>(sine * static_cast<long double>(radius));
    return destination;
}

extern "C" __attribute__((thiscall, noinline, used,
                           section(".text$animation_polar_leaf"), aligned(1)))
AnimationPolarVector* asm_Vector2_SetAnimationPolar_00441ef0(
        AnimationPolarVector* receiver, float angle, float scale) {
    AnimationPolarVector* volatile storedReceiver = receiver;
    AnimationPolarVector* destination = storedReceiver;
    volatile float& radians = angle;
    long double sine;
    long double cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float& radius = scale;
    destination->x = static_cast<float>(cosine * static_cast<long double>(radius));
    destination->y = static_cast<float>(sine * static_cast<long double>(radius));
    return destination;
}

struct EllipticPolarVector {
    float x;
    float y;
};

extern "C" __attribute__((thiscall, noinline, used,
                           section(".text$elliptic_polar"), aligned(1)))
EllipticPolarVector* asm_Vector2_SetEllipticPolar_00413270(
        EllipticPolarVector* receiver, float angle,
        float horizontalScale, float verticalScale) {
    EllipticPolarVector* volatile storedReceiver = receiver;
    EllipticPolarVector* destination = storedReceiver;
    volatile float& radians = angle;
    long double sine;
    long double cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float& horizontal = horizontalScale;
    volatile float& vertical = verticalScale;
    destination->x = static_cast<float>(cosine * static_cast<long double>(horizontal));
    destination->y = static_cast<float>(sine * static_cast<long double>(vertical));
    return destination;
}

struct EclPolarVector {
    float x;
    float y;
};

extern "C" __attribute__((thiscall, noinline, used,
                           section(".text$ecl_polar"), aligned(1)))
EclPolarVector* asm_ECL_SetPolarVector_004501b0(
        EclPolarVector* receiver, float angle, float scale) {
    EclPolarVector* volatile storedReceiver = receiver;
    EclPolarVector* destination = storedReceiver;
    volatile float& radians = angle;
    long double sine;
    long double cosine;
    __builtin_sincosl(static_cast<long double>(radians), &sine, &cosine);
    volatile float& radius = scale;
    destination->x = static_cast<float>(cosine * static_cast<long double>(radius));
    destination->y = static_cast<float>(sine * static_cast<long double>(radius));
    return destination;
}
