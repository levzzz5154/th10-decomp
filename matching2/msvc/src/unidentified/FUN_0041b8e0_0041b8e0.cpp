#include "asm_symbols.hpp"
#include "th10/render/quad_batch.hpp"

// This definition matches the class definition in
// FUN_0041ba30_0041ba30.cpp. The recovered callback and its private update
// routine now use one ordinary __thiscall receiver instead of the retail
// callback-to-update EAX tail-jump convention.
struct SceneCallbackContext_0041BA30 {
    __declspec(noinline) int UpdateSceneSecondaryCallback();
    __declspec(noinline) int UpdateSceneSecondaryRecords();
};

static float ReadSceneUpdateFloat(const unsigned char* address) {
    return *reinterpret_cast<const float*>(address);
}

static void SetSceneUpdateMatrixIdentity(float* matrix) {
    for (int element = 0; element < 16; ++element)
        matrix[element] = (element % 5 == 0) ? 1.0f : 0.0f;
}

// Semantic equivalent of the private-register 0x0043E5A0 call used here.
// Ghidra's body shows the resource/object/index effects directly; spelling
// those writes here avoids passing its retail ECX/EAX/EDX tuple to a normal
// C++ function declaration.
static void ConfigureSceneAnimationObjectFromResource(
    unsigned char* object, unsigned int recordIndex) {
    void* gameState = *reinterpret_cast<void**>(&data_004776f0);
    void* resource = *reinterpret_cast<void**>(
        reinterpret_cast<unsigned char*>(gameState) + 0x3e0b50);
    unsigned char* resourceBytes = reinterpret_cast<unsigned char*>(resource);
    if (*reinterpret_cast<unsigned int*>(resourceBytes + 0x108) == 0 ||
        *reinterpret_cast<unsigned int*>(resourceBytes + 0x124) != 0)
        return;

    *reinterpret_cast<unsigned short*>(object + 0x384) =
        static_cast<unsigned short>(recordIndex);
    *reinterpret_cast<void**>(object + 0x308) = resource;

    unsigned int recordOffset = recordIndex * 0x44u;
    unsigned char* record =
        *reinterpret_cast<unsigned char**>(resourceBytes + 0x118) + recordOffset;
    *reinterpret_cast<unsigned char**>(object + 0x394) = record;

    float width = *reinterpret_cast<float*>(record + 0x34);
    float height = *reinterpret_cast<float*>(record + 0x30);
    *reinterpret_cast<float*>(object + 0x4c) = width;
    *reinterpret_cast<float*>(object + 0x50) = height;

    float* blockA = reinterpret_cast<float*>(object + 0x23c);
    float* blockCopy = reinterpret_cast<float*>(object + 0x27c);
    float* blockB = reinterpret_cast<float*>(object + 0x2bc);
    SetSceneUpdateMatrixIdentity(blockA);
    SetSceneUpdateMatrixIdentity(blockB);

    float scale = ReadSceneUpdateFloat(&data_00470b7c);
    blockA[0] = width * scale;
    blockA[5] = height * scale;
    blockB[0] =
        (*reinterpret_cast<float*>(record + 0x38) /
         *reinterpret_cast<float*>(record + 0x1c)) * width;
    blockB[5] =
        (*reinterpret_cast<float*>(record + 0x3c) /
         *reinterpret_cast<float*>(record + 0x18)) * height;

    for (int element = 0; element < 16; ++element)
        blockCopy[element] = blockA[element];
}

// 0x00463B2C consumes an x87 value and returns a signed 64-bit conversion in
// EDX:EAX. Its body rounds with FISTP, then adjusts the result to truncate
// toward zero. This callback uses only AL. The ordinary conversion below
// preserves that low-byte result for finite values in the signed-64-bit range;
// the guard also maps x87's invalid-conversion result to its observed low byte
// of zero.
static unsigned char TruncateSceneUpdateValueToByte(double value) {
    const double minSigned64 = -9223372036854775808.0;
    const double pastMaxSigned64 = 9223372036854775808.0;
    if (!(value >= minSigned64 && value < pastMaxSigned64))
        return 0;
    return static_cast<unsigned char>(static_cast<long long>(value));
}

// 0x0041B8E0 was entered with this context in EAX and tail-returned to its
// caller. Its sole caller is 0x0041BA30, so the semantic model uses the same
// context as an ordinary __thiscall receiver in ECX.
int SceneCallbackContext_0041BA30::UpdateSceneSecondaryRecords() {
    unsigned char* firstObject =
        reinterpret_cast<unsigned char*>(this) + 0x14;
    const float offsetX = ReadSceneUpdateFloat(&data_00470b4c);
    const float offsetY = ReadSceneUpdateFloat(&data_00470b48);
    const float verticalLimit = ReadSceneUpdateFloat(&data_00470bd0);
    const float transitionRange = ReadSceneUpdateFloat(&data_00470bcc);
    const float transitionFraction = ReadSceneUpdateFloat(&data_00470d20);
    const float transitionByteScale = ReadSceneUpdateFloat(&data_00470bf8);

    for (unsigned int index = 0; index < 0x896; ++index) {
        unsigned char* object = firstObject + index * 0x3f0u;
        if (*reinterpret_cast<unsigned int*>(object + 0x3dc) == 0)
            continue;

        float* basePosition = reinterpret_cast<float*>(object + 0x334);
        basePosition[0] =
            *reinterpret_cast<float*>(object + 0x3ac) + offsetX;
        volatile float* basePositionY =
            reinterpret_cast<volatile float*>(object + 0x338);
        *basePositionY = *reinterpret_cast<float*>(object + 0x3b0) + offsetY;
        float previousY = *basePositionY;
        basePosition[2] = *reinterpret_cast<float*>(object + 0x3b4);

        unsigned int animationIndex =
            *reinterpret_cast<unsigned int*>(object + 0x3e4);
        unsigned int currentRecordIndex = static_cast<unsigned int>(
            static_cast<int>(*reinterpret_cast<short*>(object + 0x384)));
        unsigned char* alpha = object + 0x2ff;

        // The x87 TEST/J(P) branch treats unordered comparisons like the
        // non-below path, so spell the predicate as not-less-than.
        if (!(previousY < verticalLimit)) {
            unsigned int expectedRecord = animationIndex + 0x158u;
            if (currentRecordIndex != expectedRecord) {
                ConfigureSceneAnimationObjectFromResource(
                    object, animationIndex + 0x157u);
                *alpha = 0xff;
            }
        } else {
            *basePositionY = 24.0f;
            double distanceBelowLimit =
                static_cast<double>(previousY) - verticalLimit;
            if (!(distanceBelowLimit >= transitionRange)) {
                double scaledValue = distanceBelowLimit * transitionFraction;
                scaledValue *= transitionByteScale;
                *alpha = TruncateSceneUpdateValueToByte(scaledValue);
            } else {
                *alpha = 0xff;
            }

            unsigned int expectedRecord = animationIndex + 0x161u;
            if (currentRecordIndex != expectedRecord) {
                ConfigureSceneAnimationObjectFromResource(
                    object, animationIndex + 0x160u);
            }
        }

        // This dispatcher already has a semantic C++ implementation with an
        // explicit manager/entity interface. Its own case-target ABI recovery
        // remains tracked with that function and is outside this callback pair.
        AnimationManager_00442F50* manager =
            *reinterpret_cast<AnimationManager_00442F50**>(&data_00491c10);
        asm_FUN_004451c0_004451c0(
            manager, reinterpret_cast<RenderEntity*>(object));
    }

    return 1;
}
