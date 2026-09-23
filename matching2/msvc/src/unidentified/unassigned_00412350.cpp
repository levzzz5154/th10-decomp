#include <math.h>

#include "th10/math/rng.hpp"

// The adjacent entry at 0x00412300 selects integer destinations from the
// same ECL object. This dispatcher reads the corresponding scalar values.
struct EclFloatSource_00412350 {
    unsigned char padding_0000[0x3C0];
    float origin_x;                         // +0x3C0
    float origin_y;                         // +0x3C4
    unsigned char padding_03c8[0xCA0];
    float value_1068;
    float value_106c;
    unsigned char padding_1070[4];
    float value_1074;
    float value_1078;
    unsigned char padding_107c[0x18];
    float value_1094;
    float value_1098;
    unsigned char padding_109c[0x10];
    float value_10ac;
    float value_10b0;
    float value_10b4;
    unsigned char padding_10b8[8];
    float value_10c0;
    float value_10c4;
    unsigned char padding_10c8[0x10];
    float value_10d8;
    float value_10dc;
    float value_10e0;
    unsigned char padding_10e4[0x54];
    int value_1138;
    int value_113c;
    int value_1140;
    int value_1144;
    float value_1148;
    float value_114c;
    float value_1150;
    float value_1154;
    unsigned char padding_1158[8];
    float value_1160;
    unsigned char padding_1164[0x1298];
    int value_23fc;
    unsigned char padding_2400[0x82];
    unsigned char flags_2482;

    __declspec(noinline) float ResolveFloatValue(int encoded_selector) const;
};

struct EclFloatManager_00412350 {
    unsigned char padding_0000[0x10];
    EclFloatSource_00412350* current_entity;
};

extern "C" EclFloatSource_00412350* data_00477834;
extern "C" EclFloatManager_00412350* data_00477704;
extern "C" int data_00474c74;
extern "C" int data_00474c98;
extern "C" float data_00470afc;
extern "C" float data_00470b04;
extern "C" float data_00470b08;
extern "C" float data_00470b18;
extern "C" float data_00470b94;
extern "C" float data_00470bd4;

static __forceinline float AngleFromEntityOrigin(
    const EclFloatSource_00412350* origin,
    const float* point) {
    const float dx = origin->origin_x - point[0];
    const float dy = origin->origin_y - point[1];
    if (dy == data_00470b04 && dx == data_00470b04)
        return data_00470b94;
    return (float)atan2((double)dy, (double)dx);
}

static __forceinline bool IsUnordered(float left, float right) {
    return (left != left) || (right != right);
}

#pragma code_seg(".text$01accessor")
float EclFloatSource_00412350::ResolveFloatValue(int encoded_selector) const {
    const unsigned selector = static_cast<unsigned>(encoded_selector) + 0x2710u;
    if (selector > 0x32u)
        return data_00470b04;

    switch (selector) {
    case 0:
        return static_cast<float>(Rng_NextU32((RngState*)0x004918B0));
    case 1:
        return Rng_NextFloat((RngState*)0x004918B0);
    case 2:
        return Rng_NextFloatSigned((RngState*)0x004918B0) * data_00470b18;
    case 3:
    case 23:
        return value_1068;
    case 4:
    case 24:
        return value_106c;
    case 5:
    case 25:
        return value_1094;
    case 6:
    case 26:
        return value_1098;
    case 7:
    case 27:
        return value_10c0;
    case 8:
    case 28:
        return value_10c4;
    case 9:
    case 35:
        return data_00477834->origin_x;
    case 10:
    case 36:
        return data_00477834->origin_y;
    case 11: {
        const float point[2] = { value_1068, value_106c };
        return AngleFromEntityOrigin(data_00477834, point);
    }
    case 12:
        return value_1160;
    case 13:
        return Rng_NextFloatSigned((RngState*)0x004918B0);
    case 14:
        return static_cast<float>(flags_2482 & 1u);
    case 15:
        return static_cast<float>(value_1138);
    case 16:
        return static_cast<float>(value_113c);
    case 17:
        return static_cast<float>(value_1140);
    case 18:
        return static_cast<float>(value_1144);
    case 19:
        return value_1148;
    case 20:
        return value_114c;
    case 21:
        return value_1150;
    case 22:
        return value_1154;
    case 29:
        return value_10b0;
    case 30:
        return value_10dc;
    case 31:
        return value_10ac;
    case 32:
        return value_10d8;
    case 33:
        return value_10b4;
    case 34:
        return value_10e0;
    case 37:
        return data_00477704->current_entity->value_1068;
    case 38:
        return data_00477704->current_entity->value_106c;
    case 39:
        return data_00470b04;
    case 40:
        return static_cast<float>(data_00474c98);
    case 41:
        return static_cast<float>(data_00474c74);
    case 42:
        return (float)atan2((double)value_1078, (double)value_1074);
    case 43:
        return data_00470afc;
    case 44: {
        const float point[2] = { value_1094, value_1098 };
        return AngleFromEntityOrigin(data_00477834, point);
    }
    case 45: {
        const float point[2] = { value_10c0, value_10c4 };
        return AngleFromEntityOrigin(data_00477834, point);
    }
    case 46:
        return static_cast<float>(value_23fc);
    case 47:
        return IsUnordered(static_cast<float>(data_00474c74), data_00470b04)
            ? 1.0f : 0.0f;
    case 48:
        return IsUnordered(static_cast<float>(data_00474c74), data_00470afc)
            ? 1.0f : 0.0f;
    case 49:
        return IsUnordered(static_cast<float>(data_00474c74), data_00470b08)
            ? 1.0f : 0.0f;
    case 50:
        return IsUnordered(static_cast<float>(data_00474c74), data_00470bd4)
            ? 1.0f : 0.0f;
    default:
        return data_00470b04;
    }
}
#pragma code_seg()
